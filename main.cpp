#define FMT_HEADER_ONLY
// #include "KsHSInterfaceEx.h"
// #include "XMLConfigEx.h"
#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <string.h>
#include <thread>

// #include "DataFeed.h"
#include "ksGoods.h"
#include "rwqueue/readerwriterqueue.h"
#include "rwqueue/DataFileManager.h"

#ifdef __LINUX__
#include <signal.h>
#endif

namespace
{
    // IDataInterface* pNotify;

    std::vector<std::string> splitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored)
    {
        std::vector<std::string> resultStringVector;
        std::replace_if(srcStr.begin(), srcStr.end(), [&](const char& c) {if (delimStr.find(c) != std::string::npos) { return true; } else { return false; }}/*pred*/, delimStr.at(0));//将出现的所有分隔符都替换成为一个相同的字符（分隔符字符串的第一个）
        size_t pos = srcStr.find(delimStr.at(0));
        std::string addedString = "";
        while (pos != std::string::npos) {
            addedString = srcStr.substr(0, pos);
            if (!addedString.empty() || !repeatedCharIgnored) {
                resultStringVector.push_back(addedString);
            }
            srcStr.erase(srcStr.begin(), srcStr.begin() + pos + 1);
            pos = srcStr.find(delimStr.at(0));
        }
        addedString = srcStr;
        if (!addedString.empty() || !repeatedCharIgnored) {
            resultStringVector.push_back(addedString);
        }
        return resultStringVector;
    }
    
    void authCallback(istone::comm::STATUS type, const char* msg)
    {
        std::cerr << "\ttcp status:[code:" << type << "], msg:" << msg << std::endl;
    }

    bool startMyTasksThread(std::vector<std::string>& v, size_t numThreads = 2)
    {    

        static std::unordered_map <std::string, size_t> code2idx1;
        for(int i= 0;i < v.size(); i++)
        {
            code2idx1[v.at(i)] = i % numThreads;

            iGoods* g = new goods(v.at(i));
            DataFileManager::getInstance().insertCode(v.at(i), g);
        }
       
        auto myHash = [&](std::string& code) {
            
            
           auto iter = code2idx1.find(code);
           
           if(iter == code2idx1.end())
           {
               //直接过滤掉
               //std::cerr << "code:" << code << "  queue: -1" << std::endl;
               return (size_t)-1;
           }
           else
           {
                //std::cerr << "code:" << code << "  queue:" << iter->second << std::endl;
                return iter->second;
           }
        };

        // 启动numThreads个线程
        return DataFileManager::getInstance().init(numThreads, myHash);
    }
    
    void recvData2(void* data, uint32_t queue_id)
    {
        char type = *(char*)data;
        //printf("\n%c", type);
        
        switch (type)
        {
            //sh
        case 'a':
           
        case 'b':
            
        case 'd':
            
        case 'e':
            
        case 'f':
            

            //sz
        case 'C':
            
        case 'D':
            
        case 'E':
            
        case 'F':
            DataFileManager::getInstance().push(data,-1);
            break;
        }
        
    }
}

int main(int argc, char* argv[])
{
    // BLOCK the SIG_PIPE SIGNAL
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGPIPE);
    if (pthread_sigmask(SIG_BLOCK, &signal_mask, NULL) == -1)
    {
        perror("thread install SIG_PIPE error");
        return -1;
    }

    std::vector<std::string> v;
    {
        // get num of threads and stock codes
        auto queueNum = std::atoi(user_node->FirstChildElement("queueNum")->GetText()); 
        auto codes = user_node->FirstChildElement("codes")->GetText();
        //std::cerr << codes;

        v = splitString(codes, ",", true);
        /*
        for(auto _ : v)
        {
            std::cerr << _ << " ";
        }
        */
        if(!startMyTasksThread(v, queueNum))
        {
            std::cerr << "failed to start task thread";
        }
        
    }

    

    //调用初始化函数
    std::cerr << "\nstart to into istone_start";

    

    bool ret = istone_start_ex(&metaInfo,
                               &authParam,
                               authCallback,
                               nicList,
                               nNicList,
                               queueList,
                               nQueueList);
    if (!ret)
    {
        std::cerr << std::endl
                  << "failed to start,you can view .log file to find more details" << endl;
        return -1;
    }

    std::cout << std::endl << "\nPress Ctrl+C to terminate program." << std::endl;
    while (1)
    {
        sleep(500);
    }
    
    return 0;
}