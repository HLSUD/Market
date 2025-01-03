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
#include "Lev2MdSpi.h"
#include "ksGoods.h"
#include "rwqueue/readerwriterqueue.h"
#include "rwqueue/DataFileManager.h"

#include <signal.h>
// #ifdef __LINUX__
// #include <signal.h>
// #endif

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
    
    // void authCallback(istone::comm::STATUS type, const char* msg)
    // {
    //     std::cerr << "\ttcp status:[code:" << type << "], msg:" << msg << std::endl;
    // }

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
        // auto queueNum = std::atoi(user_node->FirstChildElement("queueNum")->GetText()); 
        // auto codes = user_node->FirstChildElement("codes")->GetText();
        auto queueNum = 2;
        auto codes = "600001,600002,600003,600004,600005,600006,600007,600008,600009";
        //std::cerr << codes;

        v = splitString(codes, ",", true);
        
        for(auto _ : v)
        {
            std::cerr << _ << " ";
        }
        
        if(!startMyTasksThread(v, queueNum))
        {
            std::cerr << "failed to start task thread";
        }
        
    }

    

    //调用初始化函数
    std::cerr << "\nstart to into istone_start";

    // 打印接口版本号
	printf("Level2MdApiVersion::[%s]\n", CTORATstpLev2MdApi::GetApiVersion());

	// 创建接口对象
	////TCP订阅lv2行情，前置Front和FENS方式都用默认构造
	CTORATstpLev2MdApi* demo_md_api = CTORATstpLev2MdApi::CreateTstpLev2MdApi();
	//组播订阅lv2行情
	//CTORATstpLev2MdApi *demo_md_api = CTORATstpLev2MdApi::CreateTstpLev2MdApi(TORA_TSTP_MST_MCAST);
	//组播+缓存模式
	//CTORATstpLev2MdApi* demo_md_api = CTORATstpLev2MdApi::CreateTstpLev2MdApi(TORA_TSTP_MST_MCAST, true);


	// 创建回调对象
	Lev2MdSpi md_spi(demo_md_api);

	// 注册回调接口
	demo_md_api->RegisterSpi(&md_spi);

    
#if 0  //实盘组播环境
	//注册组播地址，实例构造时必须 CreateTstpLev2MdApi(TORA_TSTP_MST_MCAST)
	const char* LEV2MD_MCAST_FrontAddress = "udp://224.224.224.15:7889";//行情A
	//本机接收组播数据地址
	const char* Interface_Address = "10.168.9.46";	//实盘时请指定相应的接收地址
	demo_md_api->RegisterMulticast((char*)LEV2MD_MCAST_FrontAddress, (char*)Interface_Address, NULL);
	printf("LEV2MD_MCAST_FrontAddress::%s\n", LEV2MD_MCAST_FrontAddress);
#endif
#if 0	//实盘TCP环境，在金桥综合区等部分区域使用
	const char* Level2MD_TCP_FrontAddress = "tcp://10.1.1.1:6900";
	demo_md_api->RegisterFront((char*)Level2MD_TCP_FrontAddress);
	printf("Level2MD_TCP_FrontAddress[Real]::%s\n", Level2MD_TCP_FrontAddress);
#endif
	///*************************************************************
	//上述地址为金桥机房16号节点的地址信息示例，客户实际地址信息请以邮件或对接群中提供的，托管服务器实际所在节点地址信息为准！
	//*************************************************************

	/*******************************互联网Level2测试桩说明*****************************
	// * 7*24小时测试桩只做技术调试用途，无法验证业务完整性，历史某日行情轮播
	// * Level2测试桩，上海和深圳分为两个独立环境，且仅支持TCP方式在互联网上测试
	// * 需使用两个不同的实例进行处理或分别测试上海和深圳
	// * *************************************************************************/
#if 1	//7*24环境测试桩，仅支持TCP方式
	const char* Level2MD_TCP_FrontAddress = "tcp://210.14.72.17:16900";//上海 
	// const char* Level2MD_TCP_FrontAddress = "tcp://210.14.72.17:6900";//深圳
	demo_md_api->RegisterFront((char*)Level2MD_TCP_FrontAddress);//上海
	printf("Level2MD_TCP_FrontAddress[24H]::%s\n", Level2MD_TCP_FrontAddress);
#endif

    // 启动
	demo_md_api->Init();
	///Init(cpuCores) 绑核参数说明
	///@param cpuCores：API内部线程绑核参数，默认不绑核运行
	//                  "0"表示API内部线程绑定到第0核上运行
	//					"0,5,18"表示API内部线程绑定到第0,第5，第18号核上运行                 
	///@remark 初始化运行环境,只有调用后,接口才开始工作

	// 等待结束
	getchar();
	//demo_md_api->join();

	// 释放，注意不允许在回调函数内调用Release接口，否则会导致线程死锁
	demo_md_api->Release();

    // auto queue_node = XMLConfigEx::instance()->queue_node_;
    // // CHECK_PTR(queue_node);
    // {
    //     nQueueList = 0;
    //     auto item = queue_node->FirstChildElement();
    //     while (item)
    //     {
    //         queueList[nQueueList].queueId = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("id")));
    //         queueList[nQueueList].msgTypes = CHECK_VALUE_ABORT((char*)(item->Attribute("types")));
    //         queueList[nQueueList].cpuId = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("cpuId")));
    //         queueList[nQueueList].blockSize = std::stoi(CHECK_VALUE_ABORT((char*)item->Attribute("blockSize")));
    //         queueList[nQueueList].dataCallback = recvData2;

    //         item = item->NextSiblingElement();
    //         nQueueList++;
    //     }
    // }


    
    /*
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
    */
    std::cout << std::endl << "\nPress Ctrl+C to terminate program." << std::endl;
    while (1)
    {
        sleep(500);
    }
    
    return 0;
}