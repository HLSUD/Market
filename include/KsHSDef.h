#pragma once
/** 修改记录:
    20211015 "初始版本"
*/
#include "stdint.h"

namespace istone
{ 
    namespace comm
    {
        static const int DEFAULT_MEM_BLOCK = 10; //缺省内存块大小
        static const int  DEFAULT_CPU_ID = -1;   //默认cpu核心id
        static const uint16_t DEFAULT_PORT = 0;  //默认socket端口

        enum MARKET
        {
            UNKNOWN_MARKET = 0,     //未知
            SH = 1,                 //上交所
            SZ = 2,                 //深交所
        };


        enum STATUS
        {
            STATUS_OK = 0,             //正常      
            STATUS_DO_REQUEST,         //请求执行错误
            STATUS_RETRY_CONNECTING,   //连接重试中
            STATUS_CONNECTED,          //连接成功
            STATUS_DISCONNECTED,       //连接失败
            STATUS_LOGINING,           //登陆中
            STATUS_LOGIN_SUCC,         //登录成功
            STATUS_LOGOUT_SUCC,        //登出失败
            STATUS_LOGIN_FAIL,         //登录失败
            STATUS_LOGOUT_FAIL,        //登出失败
			STATUS_CFG_AUTH,           //未配置鉴权信息
            STATUS_NAMEORPWD_IS_NULL,  //用户名/密码为空    
            STATUS_OTHER,              //其他错误
        };

        enum FilterMode
        {
            All = 0,        //全部通过
            None = 1,       //全部不通过
            Part = 2,       //部分通过
        };

        enum SubType
        {
            TICK = 1,       //逐笔（逐笔委托、逐笔成交）
            DEPTH           //快照
        };

        enum CacheMode
        {
            DEFAULT = 1,    //默认缓冲
            ADVANCED,       //高级缓冲（未实现，敬请期待）
        };

        //数据回调函数原型
        using DATACALLBACK = void(*)(void*);
        //鉴权回调函数原型
        using STATUSCALLBACK = void(*)(STATUS, const char*);
    }
};
