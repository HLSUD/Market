#include <stdio.h>
#include <string.h>
#include "TORATstpLev2MdApi.h"

using namespace TORALEV2API;

#ifdef  WINDOWS
#pragma comment(lib,"lev2mdapi.lib")
#endif 


class Lev2MdSpi : public CTORATstpLev2MdSpi
{
	public:
		Lev2MdSpi(CTORATstpLev2MdApi* api)
		{
			m_api = api;
		}

		~Lev2MdSpi(void)
		{
		}

	public:
		///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
		virtual void OnFrontConnected()
		{
			printf("OnFrontConnected!\n");
			CTORATstpReqUserLoginField acc;
			memset(&acc, 0, sizeof(acc));
			strcpy(acc.LogInAccount, "lev2tester");
			acc.LogInAccountType = TORA_TSTP_LACT_UserID;
			strcpy(acc.Password, "123456");

			int ret = m_api->ReqUserLogin(&acc, ++m_req_id);
			printf("ReqUserLogin[%d]\n", ret);
		};

		virtual void OnFrontDisconnected(int nReason)
		{
			printf("OnFrontDisconnected! nReason[%d]\n", nReason);

		};

		///错误应答
		virtual void OnRspError(CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			printf("OnRspError!\n");
		};

		///登录请求响应
		virtual void OnRspUserLogin(CTORATstpRspUserLoginField* pRspUserLogin, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0)
			{
				printf("OnRspUserLogin Success!\n");

	#if 1		//上海
				int eid = TORA_TSTP_EXD_SSE;
				char* Securities[1];
				Securities[0] = (char*)"00000000";//订阅所有合约
				//Securities[0] = (char*) "600621";
				//Securities[0] = (char*) "000905";//中证500指数,订阅指数时使用
				//Securities[0] = (char*) "000852";//中证1000指数,订阅指数时使用
				//Securities[0] = (char*) "000001";//订阅上证指数,，全部指数用"00000000"
				//Securities[0] = (char*) "113537";//可转债

	#elif 0 	//深圳
				int eid = TORA_TSTP_EXD_SZSE;
				char* Securities[1];
				//char* Securities[3];
				Securities[0] = (char*)"000001";
				//Securities[1] = (char*) "002213";
				//Securities[2] = (char*) "000650";
				//Securities[0] = (char*) "123013";//可转债
				//Securities[0] = (char*) "00000000";//8个0查全部
				//Securities[0] = (char*) "399001";//订阅指数使用SubscribeIndex，全部指数用"00000000"	

	#else		//跨市场订阅
				int eid = TORA_TSTP_EXD_COMM;
				char* Securities[1];
				//char* Securities[3];
				//Securities[0] = (char*) "000001";
				//Securities[1] = (char*) "002213";
				//Securities[2] = (char*) "000650";
				Securities[0] = (char*)"00000000";//8个0查全部
				//Securities[0] = (char*) "399001";//订阅指数使用SubscribeIndex，全部指数用"00000000"	
	#endif


	#if 0	//快照行情订阅
				int ret_md = m_api->SubscribeMarketData(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_md == 0)
				{
					printf("SubscribeMarketData:::Success,ret=%d\n", ret_md);
				}
				else
				{
					printf("SubscribeMarketData:::Failed, ret=%d)\n", ret_md);
				}
	#endif
	#if 0	//逐笔成交订阅（仅深圳有效，且不含深圳普通债券）
				int ret_t = m_api->SubscribeTransaction(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_t == 0)
				{
					printf("SubscribeTransaction:::Success,ret=%d\n", ret_t);
				}
				else
				{
					printf("SubscribeTransaction:::Failed,ret=%d)\n", ret_t);
				}
	#endif
	#if 0	//逐笔委托订阅（仅深圳有效，且不含深圳普通债券）
				int ret_od = m_api->SubscribeOrderDetail(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_od == 0)
				{
					printf("SubscribeOrderDetail:::Success,ret=%d\n", ret_od);
				}
				else
				{
					printf("SubscribeOrderDetail:::Failed, ret=%d)\n", ret_od);
				}
	#endif
	#if 0	//指数行情订阅
				int ret_i = m_api->SubscribeIndex(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_i == 0)
				{
					printf("SubscribeIndex:::Success,ret=%d", ret_i);
				}
				else
				{
					printf("SubscribeIndex:::Failed, ret=%d)", ret_i);
				}
	#endif
	#if 0	//上海XTS新债快照订阅
				int ret_xtx_md = m_api->SubscribeXTSMarketData(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_xtx_md == 0)
				{
					printf("SubscribeXTSMarketData:::Success,ret=%d\n", ret_xtx_md);
				}
				else
				{
					printf("SubscribeIndex:::Failed, ret=%d\n)", ret_xtx_md);
				}
	#endif
	#if 0	//上海XTS新债逐笔（逐笔委托+逐笔成交）
				int ret_xtx_t = m_api->SubscribeXTSTick(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_xtx_t == 0)
				{
					printf("SubscribeIndex:::Success,ret=%d\n", ret_xtx_t);
				}
				else
				{
					printf("SubscribeIndex:::Failed, ret=%d\n)", ret_xtx_t);
				}
	#endif
	#if 1	//上海合并逐笔NGTS订阅
				int ret_ngs_t = m_api->SubscribeNGTSTick(Securities, sizeof(Securities) / sizeof(char*), eid);
				if (ret_ngs_t == 0)
				{
					printf("SubscribeNGTSTick:::Success,ret=%d\n", ret_ngs_t);
				}
				else
				{
					printf("SubscribeNGTSTick:::Failed, ret=%d\n)", ret_ngs_t);
				}
	#endif
			}
			else
			{
				printf("OnRspUserLogin fail!\n");

			}
		};

		/***********************************响应应答函数***********************************/
			///登出请求响应
		virtual void OnRspUserLogout(CTORATstpUserLogoutField* pUserLogout, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			printf("OnRspUserLogout!\n");

		};

		///订阅快照行情应答
		virtual void OnRspSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspSubMarketData SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		///取消订阅行情应答
		virtual void OnRspUnSubMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			printf("OnRspUnSubMarketData SecurityID[%s] ExchangeID[%c]!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

		};

		// 订阅指数行情应答
		virtual void OnRspSubIndex(TORALEV2API::CTORATstpSpecificSecurityField* pSpecificSecurity, TORALEV2API::CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspSubIndex SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		// 订阅逐笔成交行情应答
		virtual void OnRspSubTransaction(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspSubTransaction SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		///订阅逐笔委托行情应答
		virtual void OnRspSubOrderDetail(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspSubOrderDetail SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		//订阅新债逐笔行情应答
		virtual void OnRspSubXTSTick(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspSubXTSTick SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		//订阅上海合并流逐笔响应
		virtual void OnRspUnSubNGTSTick(CTORATstpSpecificSecurityField* pSpecificSecurity, CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (pRspInfo && pRspInfo->ErrorID == 0 && pSpecificSecurity)
			{
				printf("OnRspUnSubNGTSTick SecurityID[%s] ExchangeID[%c] Success!\n", pSpecificSecurity->SecurityID, pSpecificSecurity->ExchangeID);

			}
		};

		///订阅上海XTS债券行情应答
		virtual void OnRspSubXTSMarketData(CTORATstpSpecificSecurityField* pSpecificSecurity,
			CTORATstpRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
		{
			if (bIsLast)
			{
				printf("OnRspSubXTSMarketData::nRequestID[%d]\n", nRequestID);
			}
		};


		/***********************************回报函数***********************************/

		///快照行情通知
		virtual void OnRtnMarketData(CTORATstpLev2MarketDataField* pDepthMarketData, const int FirstLevelBuyNum, const int FirstLevelBuyOrderVolumes[], const int FirstLevelSellNum, const int FirstLevelSellOrderVolumes[])
		{
			printf("OnRtnMarketData TimeStamp[%d]  SecurityID[%s] ExchangeID[%c]  PreClosePrice[%f] LowestPrice[%f] HighestPrice[%f] OpenPrice[%f] LastPrice[%f]"
				"BidPrice{[%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f]}"
				"AskPrice{[%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f] [%f]}"
				"BidVolume{[%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld]}"
				"AskVolume{[%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld] [%lld]}",
				pDepthMarketData->DataTimeStamp,
				pDepthMarketData->SecurityID,
				pDepthMarketData->ExchangeID, pDepthMarketData->PreClosePrice, pDepthMarketData->LowestPrice,
				pDepthMarketData->HighestPrice, pDepthMarketData->OpenPrice,
				pDepthMarketData->LastPrice,
				pDepthMarketData->BidPrice1, pDepthMarketData->BidPrice2, pDepthMarketData->BidPrice3,
				pDepthMarketData->BidPrice4, pDepthMarketData->BidPrice5, pDepthMarketData->BidPrice6,
				pDepthMarketData->BidPrice7, pDepthMarketData->BidPrice8, pDepthMarketData->BidPrice9, pDepthMarketData->BidPrice10,
				pDepthMarketData->AskPrice1, pDepthMarketData->AskPrice2, pDepthMarketData->AskPrice3,
				pDepthMarketData->AskPrice4, pDepthMarketData->AskPrice5, pDepthMarketData->AskPrice6,
				pDepthMarketData->AskPrice7, pDepthMarketData->AskPrice8, pDepthMarketData->AskPrice9, pDepthMarketData->AskPrice10,
				pDepthMarketData->BidVolume1, pDepthMarketData->BidVolume2, pDepthMarketData->BidVolume3,
				pDepthMarketData->BidVolume4, pDepthMarketData->BidVolume5, pDepthMarketData->BidVolume6,
				pDepthMarketData->BidVolume7, pDepthMarketData->BidVolume8, pDepthMarketData->BidVolume9, pDepthMarketData->BidVolume10,
				pDepthMarketData->AskVolume1, pDepthMarketData->AskVolume2, pDepthMarketData->AskVolume3,
				pDepthMarketData->AskVolume4, pDepthMarketData->AskVolume5, pDepthMarketData->AskVolume6,
				pDepthMarketData->AskVolume7, pDepthMarketData->AskVolume8, pDepthMarketData->AskVolume9, pDepthMarketData->AskVolume10
			);

			printf("BuyVolumes %d{", FirstLevelBuyNum);

			for (int index = 0; index < FirstLevelBuyNum; index++)
			{
				printf("%d ", FirstLevelBuyOrderVolumes[index]);
			}
			printf("}");

			printf("SellVolumes %d{", FirstLevelSellNum);

			for (int index = 0; index < FirstLevelSellNum; index++)
			{
				printf("%d ", FirstLevelSellOrderVolumes[index]);
			}
			printf("}\n");
		};

		// 指数快照行情通知
		virtual void OnRtnIndex(CTORATstpLev2IndexField* pIndex)
		{
			printf("OnRtnIndex SecurityID[%s] ", pIndex->SecurityID);
			printf("ExchangeID[%d] ", pIndex->ExchangeID);
			printf("DataTimeStamp[%d] ", pIndex->DataTimeStamp);//精确到秒，上海指数5秒一笔，深圳3秒一笔
			printf("LastIndex[%.2f] ", pIndex->LastIndex);
			printf("PreCloseIndex[%.2f] ", pIndex->PreCloseIndex);
			printf("OpenIndex[%.2f] ", pIndex->OpenIndex);
			printf("LowIndex[%.2f] ", pIndex->LowIndex);
			printf("HighIndex[%.2f] ", pIndex->HighIndex);
			printf("CloseIndex[%.2f] ", pIndex->CloseIndex);
			printf("Turnover[%.2f] ", pIndex->Turnover);
			printf("TotalVolumeTraded[%lld]\n", pIndex->TotalVolumeTraded);
		};

		///逐笔成交通知
		virtual void OnRtnTransaction(CTORATstpLev2TransactionField* pTransaction)
		{
			printf("OnRtnTransaction SecurityID[%s] ", pTransaction->SecurityID);
			printf("ExchangeID[%c] ", pTransaction->ExchangeID);
			//深圳逐笔成交，TradeTime的格式为【时分秒毫秒】例如例如100221530，表示10:02:21.530;
			//上海逐笔成交，TradeTime的格式为【时分秒百分之秒】例如10022153，表示10:02:21.53;
			printf("TradeTime[%d] ", pTransaction->TradeTime);
			printf("TradePrice[%.4f] ", pTransaction->TradePrice);
			printf("TradeVolume[%lld] ", pTransaction->TradeVolume);
			printf("ExecType[%c] ", pTransaction->ExecType);//上海逐笔成交没有这个字段，只有深圳有。值2表示撤单成交，BuyNo和SellNo只有一个是非0值，以该非0序号去查找到的逐笔委托即为被撤单的委托。
			printf("MainSeq[%d] ", pTransaction->MainSeq);
			printf("SubSeq[%lld] ", pTransaction->SubSeq);
			printf("BuyNo[%lld] ", pTransaction->BuyNo);
			printf("SellNo[%lld] ", pTransaction->SellNo);
			printf("TradeBSFlag[%c] ", pTransaction->TradeBSFlag);
			printf("Info1[%d] ", pTransaction->Info1);
			printf("Info2[%d] ", pTransaction->Info2);
			printf("Info3[%d] \n", pTransaction->Info3);
		};


		///逐笔委托通知
		virtual void OnRtnOrderDetail(CTORATstpLev2OrderDetailField* pOrderDetail)
		{

			printf("OnRtnOrderDetail SecurityID[%s] ", pOrderDetail->SecurityID);
			printf("ExchangeID[%d] ", pOrderDetail->ExchangeID);
			printf("OrderTime[%d] ", pOrderDetail->OrderTime);
			printf("Price[%.4f] ", pOrderDetail->Price);
			printf("Volume[%lld] ", pOrderDetail->Volume);
			printf("OrderType[%c] ", pOrderDetail->OrderType);
			printf("MainSeq[%d] ", pOrderDetail->MainSeq);
			printf("SubSeq[%d] ", pOrderDetail->SubSeq);
			printf("Side[%c] ", pOrderDetail->Side);
			printf("Info1[%d] ", pOrderDetail->Info1);
			printf("Info2[%d] ", pOrderDetail->Info2);
			printf("Info3[%d] \n", pOrderDetail->Info3);

		};

		///上海XTS债券快照行情通知
		virtual void OnRtnXTSMarketData(CTORATstpLev2XTSMarketDataField* pMarketData,
			const int FirstLevelBuyNum, const int FirstLevelBuyOrderVolumes[],
			const int FirstLevelSellNum, const int FirstLevelSellOrderVolumes[])
		{
			printf("OnRtnXTSMarketData SecurityID[%s] ", pMarketData->SecurityID);
			printf("ExchangeID[%c] ", pMarketData->ExchangeID);
			printf("DataTimeStamp[%d] ", pMarketData->DataTimeStamp);
			//printf("PreClosePrice[%.3f] ", pMarketData->PreClosePrice);
			//printf("OpenPrice[%.3f] ", pMarketData->OpenPrice);
			//printf("NumTrades[%lld] ", pMarketData->NumTrades);
			//printf("TotalVolumeTrade[%lld] ", pMarketData->TotalVolumeTrade);
			//printf("HighestPrice[%.3f] ", pMarketData->HighestPrice);
			//printf("LowestPrice[%.3f] ", pMarketData->LowestPrice);
			printf("LastPrice[%.3f] ", pMarketData->LastPrice);
			printf("BidPrice1[%.3f] ", pMarketData->BidPrice1);
			printf("BidVolume1[%lld] ", pMarketData->BidVolume1);
			printf("AskPrice1[%.3f] ", pMarketData->AskPrice1);
			printf("AskVolume1[%.lld] ", pMarketData->AskVolume1);
			printf("MDSecurityStat[%c] \n", pMarketData->MDSecurityStat);
		};

		///上海XTS债券逐笔数据通知
		virtual void OnRtnXTSTick(CTORATstpLev2XTSTickField* pTick)
		{
			printf("OnRtnXTSTick SecurityID[%s] ", pTick->SecurityID);
			printf("ExchangeID[%c] ", pTick->ExchangeID);
			printf("MainSeq[%d] ", pTick->MainSeq);
			printf("SubSeq[%lld] ", pTick->SubSeq);
			printf("TickTime[%d] ", pTick->TickTime);
			printf("TickType[%c] ", pTick->TickType);
			printf("BuyNo[%lld] ", pTick->BuyNo);
			printf("SellNo[%lld] ", pTick->SellNo);
			printf("Price[%.2f] ", pTick->Price);
			printf("Volume[%lld] ", pTick->Volume);
			printf("TradeMoney[%.2f] ", pTick->TradeMoney);
			printf("Side[%c] ", pTick->Side);
			printf("TradeBSFlag[%d] ", pTick->TradeBSFlag);
			printf("MDSecurityStat[%c] ", pTick->MDSecurityStat);
			printf("Info1[%d] ", pTick->Info1);
			printf("Info2[%d] ", pTick->Info2);
			printf("Info3[%d] \n", pTick->Info3);
		};

		virtual void OnRtnNGTSTick(CTORATstpLev2NGTSTickField* pTick)
		{
			printf("OnRtnNGTSTick SecurityID[%s] ", pTick->SecurityID);
			printf("ExchangeID[%c] ", pTick->ExchangeID);
			printf("MainSeq[%d] ", pTick->MainSeq);
			printf("SubSeq[%lld] ", pTick->SubSeq);
			printf("TickTime[%d] ", pTick->TickTime);
			printf("TickType[%c] ", pTick->TickType);
			printf("BuyNo[%lld] ", pTick->BuyNo);
			printf("SellNo[%lld] ", pTick->SellNo);
			printf("Price[%.2f] ", pTick->Price);
			printf("Volume[%lld] ", pTick->Volume);
			printf("TradeMoney[%.2f] ", pTick->TradeMoney);
			printf("Side[%c] ", pTick->Side);
			printf("TradeBSFlag[%d] ", pTick->TradeBSFlag);
			printf("Info1[%d] ", pTick->Info1);
			printf("Info2[%d] ", pTick->Info2);
			printf("Info3[%d] \n", pTick->Info3);
		};

	private:
		CTORATstpLev2MdApi* m_api;
		int m_req_id;
};