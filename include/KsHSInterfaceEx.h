#ifndef  _KS_HS_INTERFACE_EX_H_
#define  _KS_HS_INTERFACE_EX_H_
/** 修改记录:
    20220623 "初始版本"
*/
#include "KsHSDef.h"
#include "stdint.h"
#include "memory.h"
#include <vector>
#include <iostream>

#pragma pack(push, 4)

namespace istone_hs
{
    //字符串包装函数
    #define mystr2(x)  std::string(x, sizeof(x)).c_str()
   
    struct MetaInfo
    {
        char* version;              //版本号
        char* authMetaInfo;         //鉴权服务信息
        char* multiMetaInfo;        //组播服务信息
    };

    struct AuthInfo
    {
        char* user;               //用户名
        char* passwd;             //密码
        char* nic;                //本地建联网口/此网口对应的ip（两者都支持）
    };

    //在特定的网卡nicName上接收msgTypes包含的所有数据
    struct CacheAdvanceNicItem
    {
        char*     nicName;          //网口名称（！一些情况下，对应的网卡需要配置ip）
        int32_t   cpuId;            //从网口接收数据线程的cpu id
        char*     msgTypes;         //希望串行的数据类型
    };

    //数据回调原型.参数（业务数据）
	using DATACALLBACK_WITHID = void(*)(void*, uint32_t);

    //msgTypes中的数据共用一个缓冲队列
    struct CacheAdvanceQueueItem
    {
        int32_t  queueId;           //唯一标志，须不同
        char*    msgTypes;          //希望串行的数据类型
        int32_t  cpuId;             //从网口接收数据线程的cpu id
        int32_t  blockSize;         //缓冲块大小（2MB/per）
        DATACALLBACK_WITHID dataCallback;  //数据回调函数
    };
    
    //启动。如果失败，返回false，详细错误信息请查看日志
    bool istone_start_ex(
                      MetaInfo*  metaInfo,

                      AuthInfo* authParam,
                      istone::comm::STATUSCALLBACK authCallback, 

                      CacheAdvanceNicItem* pNicList,
                      uint8_t nNicList,

                      CacheAdvanceQueueItem* pDataQueueList,
                      uint8_t nDataQueue
                      );

    //停止
    bool istone_stop_ex();

    //设置可选项
    /**
        key:
            AUTO_DEDUPLICATE_MSGTYPE --是否自动去重      （1--自动去重，2--不去重） 。默认为1。
            NIC_RECV_MODE            --网卡获取数据模式  （1--SFC_EFVI, 2--EXANIC_PCIE）。默认为1
    */
    bool istone_set_option_ex(const char* key, int val);

};

#pragma pack(pop)

#endif