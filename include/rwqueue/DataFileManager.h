#pragma once
#include <iostream>
#include "readerwriterqueue.h"
#include "atomicops.h"
#include "KsTool.h"
#include "ksGoods.h"
#include <functional>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <map>
#include <thread>


using namespace moodycamel;

class DataFileManager 
{
private:
    std::vector<std::thread> threads_; // threads
    std::map<size_t, ReaderWriterQueue<std::string>*> queues_;
    std::unordered_map<std::string, iGoods*> map_goods_; // code 2 good 

    using FuncHash = std::function<size_t(std::string& code)>;
    FuncHash func_hash_; // code 2 thread id

    DataFileManager()
    {		
	}

    ~DataFileManager()
	{ 
    }
private:
    // thread function
    void threadTask(ReaderWriterQueue<std::string>* q)
    {
        std::string buff;
        while (true)
        {
            if (q->try_dequeue(buff))
            {
                // printf("Got data...\n");
                //threadFunction(buff.c_str());
                auto code = KsTool::getCode(buff.c_str());
                char type = buff.at(0);
                auto g = map_goods_[code];
                const char* data=buff.c_str();
                switch (type)
                {
                    //sh
                    case sseEntrustType:
                        g->onSseEntrust((SseEntrust*)data);
                        break;
                    case sseTradeType:
                        g->onSseTrade((SseTrade*)data);
                        break;
                    case sseDepthType1:
                        g->onSseDepth((SseDepth*)data, NO_PRICE);
                        break;
                    case sseDepthType0:
                        g->onSseDepth((SseDepth*)data, HAS_PRICE);
                        break;
                    case sseDepthFiftyType:
                        g->onSseDepthFifty((SseDepthFifty*)data);
                        break;
                    //todo
                    //sz
                    case szseEntrustType:
                        g->onSzseEntrust((SzseEntrust*)data);
                        break;
                    case szseTradeType:
                        g->onSzseTrade((SzseTrade*)data);
                        break;
                    case szseDepthFiftyType:
                        g->onSzseDepthFifty((SzseDepthFifty*)data);
                        break;
                    case szseDepthOrOptionType:
                        g->onSzseDepth((SzseDepth*)data);
                        break;
                    // default:
                    //     std::cout << "New option.\n";
                    //     g->onSseEntrust((TORALEV2API::CTORATstpLev2NGTSTickField*)data);
                }
               
            }
            
        }
    }

    
public:
    // get an object of Datafilemanager
    static DataFileManager& getInstance() {
        static DataFileManager instance;
        return instance;
    }
    // insert a good for a code
    void insertCode(std::string& code, iGoods* ptr)
    {
        //std::cerr << "11" << code ;
        map_goods_[code] = ptr;
        ptr->Init();
    }
    bool init(size_t N, FuncHash funcHash = nullptr)
    {
        if (!funcHash)
        {
            func_hash_ = [N](std::string& code){                
                size_t hashValue = std::hash<std::string>()(code);
                size_t queueIndex = hashValue % N;
                return queueIndex;
            };
        }
        else
        {
            func_hash_ = funcHash;
        }
        for (size_t i = 0; i < N; ++i)
        {
            ReaderWriterQueue<std::string>* q = new ReaderWriterQueue<std::string>(40000 * 64);
            if (q == NULL)
            {
                std::cerr << "\nFailed to create queue for thread (" << i << ")." << std::endl;
                return false;
            }
            queues_[i] = q;
            threads_.emplace_back(&DataFileManager::threadTask, this, q);
            threads_.back().detach();
        }

        return true;
    }

    void push(void* buff, uint32_t queue_id) 
	{
        std::string data((char*)buff, KsTool::getTypeSize(((char*)buff)[0]));
        std::string&& code = KsTool::getCode((const char*)buff);
        size_t index = func_hash_(code);
        if(index == (size_t)-1)
        {
            //没有匹配到对应的queue
            //std::cout << "code:" << code << "has been filter." << std::endl;
            return;
        }
        auto q = queues_[index];
        if (q)
        {            
            if (!q->enqueue(std::move(data)))
            {
                std::cerr << "failed to enque.(id:" << index << ")" << std::endl;
            }
            else
            {
                //std::cout << "success to enque.(id:" << index << ")" << "code=" << code << std::endl;
            }
        }   
        else
        {
            //std::cerr
            std::cerr << "failed to find enque.(id:" << index << ")" << " index=" << index << " code=" << code << std::endl; 
        }
    }
};


