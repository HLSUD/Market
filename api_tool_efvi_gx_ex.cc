#define FMT_HEADER_ONLY
#include "KsHSInterfaceEx.h"
#include "XMLConfigEx.h"
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
#include "DataFeed.h"
#include "ksGoods.h"

#include "rwqueue/readerwriterqueue.h"
#include "rwqueue/DataFileManager.h"
#include <thread>
#ifdef __LINUX__
#include <signal.h>
#endif

//辅助检查配置文件相关，可忽略
namespace
{
    void* CHECK_PTR_IMPLEMENT(const char* file_name, int line_num, void* ptr)
    {
        if (!ptr)
        {
            cerr << "\nInvalid value at:" << file_name << ":" << line_num << ".";
            abort();
        }
        return ptr;
    }

    char* CHECK_VALUE_IMPLEMENT(const char* file_name, int line_num, char* val, int abortIfNull)
    {
        if (val && strlen(val) > 0)
        {
            return val;
        }
        cerr << "\nInvalid value at:" << file_name << ":" << line_num << ".";
        if (abortIfNull)
        {
            abort();
        }
        else
        {
            cerr << "\npossible value at:" << file_name << ":" << line_num << ".";
        }
        return  (char*)"";
    }
#define CHECK_PTR(ptr)                  CHECK_PTR_IMPLEMENT(__FILE__,__LINE__, ptr)
#define CHECK_VALUE_NOABORT(val)        CHECK_VALUE_IMPLEMENT(__FILE__,__LINE__, val, false)
#define CHECK_VALUE_ABORT(val)          CHECK_VALUE_IMPLEMENT(__FILE__,__LINE__, val, true) 
}
namespace
{
    IDataInterface* pNotify;

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
    sigset_t signal_mask;
    sigemptyset(&signal_mask);
    sigaddset(&signal_mask, SIGPIPE);
    if (pthread_sigmask(SIG_BLOCK, &signal_mask, NULL) == -1)
    {
        perror("thread install SIG_PIPE error");
        return -1;
    }

    /////////////////
    //pNotify = new IDataInterface;
	//memset(pNotify, 0, sizeof(IDataInterface));

    //pNotify->pfnFeed_SseIndex = Feed_SseIndex;
    //pNotify->pfnFeed_SseDepth = Feed_SseDepth;
    //pNotify->pfnFeed_SseDepthFifty = Feed_SseDepthFifty;
    //pNotify->pfnFeed_SseEntrust = Feed_SseEntrust;
    //pNotify->pfnFeed_SseTrade = Feed_SseTrade;

    //pNotify->pfnFeed_SzseTradeStatics = Feed_SzseTradeStatics;
    //pNotify->pfnFeed_SzseIndex = Feed_SzseIndex;
    //pNotify->pfnFeed_SzseDepth = Feed_SzseDepth;
    //pNotify->pfnFeed_SzseDepthFifty = Feed_SzseDepthFifty;
    //pNotify->pfnFeed_SzseEntrust = Feed_SzseEntrust;
    //pNotify->pfnFeed_SzseTrade = Feed_SzseTrade;
    /////////////////

    using namespace istone_hs;

    MetaInfo metaInfo{0};
    AuthInfo authParam{0};

    CacheAdvanceNicItem nicList[8]{0};
    uint8_t nNicList = 0;

    CacheAdvanceQueueItem queueList[16]{0};
    uint8_t nQueueList = 0;

    const char *xmlPath = NULL;
    if (argc != 2)
    {
        xmlPath = "./demo/config/ApiConfigEx.xml";
    }
    else
    {
        xmlPath = argv[1];
    }

    if (!XMLConfigEx::instance()->LoadXML(xmlPath))
    {
        std::cerr << "\nfailed to LoadXML.";
        return -1;
    }

    std::cerr << "\nsucced to LoadXML.";
    auto meta_node = XMLConfigEx::instance()->meta_node_;
    CHECK_PTR(meta_node);
    {
        metaInfo.version = CHECK_VALUE_ABORT((char*)(meta_node->Attribute("version")));

        CHECK_PTR(meta_node->FirstChildElement("Auth"));
        metaInfo.authMetaInfo = CHECK_VALUE_ABORT((char*)(meta_node->FirstChildElement("Auth")->GetText()));

        //如果IHQ配置了组播信息，此处可以不传参，成功登陆会自动获取组播信息。
        //如果传参，将优先使用本地组播参数。
        auto multicast_node = meta_node->FirstChildElement("Multicast");
        if (multicast_node)
        {
            auto txt = meta_node->FirstChildElement("Multicast")->GetText();
            if (txt && strlen(txt) > 4)
            {
                metaInfo.multiMetaInfo = (char*)txt;
                cerr << "\nfind local multi info in config file. and will use local multicast info";
            }
        }
        
    }

    auto auth_node = XMLConfigEx::instance()->auth_node_;
    CHECK_PTR(auth_node);
    {
        authParam.user = CHECK_VALUE_ABORT((char*)(auth_node->Attribute("user")));
        authParam.passwd = CHECK_VALUE_ABORT((char*)(auth_node->Attribute("passwd")));
        authParam.nic = CHECK_VALUE_ABORT((char*)(auth_node->Attribute("nic")));
    }

    auto nic_node = XMLConfigEx::instance()->nic_node_;
    CHECK_PTR(nic_node);
    {
        nNicList = 0;
        auto item = nic_node->FirstChildElement();
        while (item)
        {

            nicList[nNicList].nicName = CHECK_VALUE_ABORT((char*)(item->Attribute("onNic")));
            nicList[nNicList].cpuId = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("cpuId")));
            nicList[nNicList].msgTypes = CHECK_VALUE_NOABORT((char*)(item->Attribute("types")));

            item = item->NextSiblingElement();
            nNicList++;
        }
    }
    auto queue_node = XMLConfigEx::instance()->queue_node_;
    CHECK_PTR(queue_node);
    {
        nQueueList = 0;
        auto item = queue_node->FirstChildElement();
        while (item)
        {
            queueList[nQueueList].queueId = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("id")));
            queueList[nQueueList].msgTypes = CHECK_VALUE_ABORT((char*)(item->Attribute("types")));
            queueList[nQueueList].cpuId = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("cpuId")));
            queueList[nQueueList].blockSize = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("blockSize")));
            queueList[nQueueList].dataCallback = recvData2;

            item = item->NextSiblingElement();
            nQueueList++;
        }
    }

    auto option_node = XMLConfigEx::instance()->option_node_;
    CHECK_PTR(option_node);
    {
        auto item = option_node->FirstChildElement(); 
        while (item)
        {
            const char* name = item->Name();
            const char* val = item->GetText();
            istone_set_option_ex(name, std::atoi(val));

            item = item->NextSiblingElement();
        }
    }

    auto user_node = XMLConfigEx::instance()->user_node_;
    CHECK_PTR(user_node);
    std::vector<std::string> v;
    {
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
