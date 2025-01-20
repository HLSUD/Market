#if !defined(_LEV2MDSPI_H)
#define _LEV2MDSPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpLev2MdApi.h"

using namespace TORALEV2API;

#define SHANGHAI 0
#define SHENZHEN 1
#define ENTRUSHTSZ 1
#define TRANSACTIONSZ 1
#define SNAPSHOT 1
#define NGTSSH 0

class Lev2MdSpi : public CTORATstpLev2MdSpi
{
	public:
		Lev2MdSpi(CTORATstpLev2MdApi* api);

		~Lev2MdSpi(void);

	public:
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected();

		virtual void OnFrontDisconnected(int nReason);

		///错误应答
		virtual void OnRspError(CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

		///登录请求响应
		virtual void OnRspUserLogin(CTORATstpRspUserLoginField* pRspUserLogin, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        ///登出请求响应
		virtual void OnRspUserLogout(CTORATstpUserLogoutField* pUserLogout, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        ///订阅快照行情应答
		virtual void OnRspSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        ///取消订阅行情应答
		virtual void OnRspUnSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        // 订阅指数行情应答
		virtual void OnRspSubIndex(TORALEV2API::CTORATstpSpecificSecurityField* pSpecificSecurity, TORALEV2API::CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        // 订阅逐笔成交行情应答
		virtual void OnRspSubTransaction(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        // 订阅逐笔委托行情应答
		virtual void OnRspSubOrderDetail(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);
		
		//订阅新债逐笔行情应答
		virtual void OnRspSubXTSTick(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        //订阅上海合并流逐笔响应
		virtual void OnRspUnSubNGTSTick(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        ///订阅上海XTS债券行情应答
		virtual void OnRspSubXTSMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity,
			CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast);

        ///快照行情通知
		virtual void OnRtnMarketData(CTORATstpLev2MarketDataField* pDepthMarketData, const int FirstLevelBuyNum, const int FirstLevelBuyOrderVolumes[], const int FirstLevelSellNum, const int FirstLevelSellOrderVolumes[]);

        // 指数快照行情通知
		virtual void OnRtnIndex(CTORATstpLev2IndexField* pIndex);

        ///逐笔成交通知
		virtual void OnRtnTransaction(CTORATstpLev2TransactionField* pTransaction);

        ///逐笔委托通知
		virtual void OnRtnOrderDetail(CTORATstpLev2OrderDetailField* pOrderDetail);

        ///上海XTS债券快照行情通知
		virtual void OnRtnXTSMarketData(CTORATstpLev2XTSMarketDataField* pMarketData,
			const int FirstLevelBuyNum, const int FirstLevelBuyOrderVolumes[],
			const int FirstLevelSellNum, const int FirstLevelSellOrderVolumes[]);
        
        ///上海XTS债券逐笔数据通知
		virtual void OnRtnXTSTick(CTORATstpLev2XTSTickField* pTick);

        virtual void OnRtnNGTSTick(CTORATstpLev2NGTSTickField* pTick);
    
    private:
		CTORATstpLev2MdApi* m_api;
		int m_req_id;

};

#endif