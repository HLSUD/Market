#include "goodsbase.h"
#include <chrono>
#include "TORATstpTraderApi.h"
#include "TraderConfig.h"

// #include "buylimit.h"
using namespace std;
void goodsbase::Buy(int qty, double price) {
	if (_tradeApi) {

		// std::string errMsg;
		request_count++;
		// auto ret = 0;
		auto ret = _tradeApi->reqLimitTrade(code_, price, qty, '0');

        // OrderTicket(price > 0 ? BuyLimit : BuyMarket, "", code_, qty, price, errMsg);
		if (ret != 0) {
			printf("---\n请求下单失败, %s \n", code_.c_str());
		}
		else
		{
			printf("---\n请求下单成功, %s \n", code_.c_str());
		}
	}
}

void goodsbase::Sell(int qty, double price) {
	if (_tradeApi) {
        request_count++;

		// std::string errMsg;
		auto ret = _tradeApi->reqLimitTrade(code_, price, qty, '1');
        // _tradeApi->OrderTicket(price > 0 ? BuyLimit : BuyMarket, "", code_, qty, price, errMsg);
		if (ret != 0) {
			printf("---\n请求下单失败, %s \n", code_.c_str());
		}
		else
		{
			printf("---\n请求下单成功, %s \n", code_.c_str());
		}
	}
}

void goodsbase::Sell(double price) {
	if (_tradeApi) {
        request_count++;
        int request_id = request_count+2;

		// std::string errMsg;
        auto ret = _tradeApi->queryByID(code_);
		// auto ret = _tradeApi->
        // OrderTicket(price > 0 ? BuyLimit : BuyMarket, "", code_, 0, price, errMsg);
		if (ret != 0) {
			printf("---\n查阅请求失败, %s \n", code_.c_str());
            return;
		}
		else
		{
			printf("---\n查阅请求成功, %s \n", code_.c_str());
		}
        TORASTOCKAPI::CTORATstpPositionField* position_p;
        auto start = std::chrono::high_resolution_clock::now();
        bool query_ret = true;
        while(_tradeApi->get_position_info_by_id(code_)!=0){
            // Record the end time
            
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // printf("%d T: %d\n",_tradeApi->get_position_info_by_id(code_, position_p),elapsed.count());
            if (elapsed.count() > 1000){
                query_ret = false;
                printf("Fail to query, high latency issue.");
                ret = 0;
                break;
            }
            // printf("RECEIVED INFO: OnRspQryPosition: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        }
        if (query_ret){
            position_p = _tradeApi->postion_map_[code_];
            printf("RECEIVED INFO: OnRspQryPosition[%d]: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", request_id, position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
            printf("Got the postion of %s: %d\n", position_p->SecurityID,  position_p->AvailablePosition);
            ret = _tradeApi->reqLimitTrade(code_, price, position_p->AvailablePosition, '1');
        }
        // fprintf(fp,"OnRspQryPosition[%d]: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", nRequestID, position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        if (ret != 0) {
			printf("请求下单失败, %s \n", code_.c_str());
		}
		else
		{
			printf("请求下单成功, %s \n", code_.c_str());
		}
	}
}

void goodsbase::QueryReq(int type){
	// type: 1. query, 2. cancel buy 3.cancel sell
    if (_tradeApi) {
        
        request_count++;
        int request_id = request_count+2;
		// std::string errMsg;
		// set type
		_tradeApi->query_trade_option_map_[code_] = type;
        auto ret = _tradeApi->queryReqByID(code_);
		// auto ret = _tradeApi->
        // OrderTicket(price > 0 ? BuyLimit : BuyMarket, "", code_, 0, price, errMsg);
		if (ret != 0) {
			printf("---\n查阅请求失败, %s \n", code_.c_str());
		}
		else
		{
			printf("---\n查阅请求成功, %s \n", code_.c_str());
		}
        // TORASTOCKAPI::CTORATstpPositionField* position_p;
        // auto start = std::chrono::high_resolution_clock::now();
        // bool query_ret = true;
        // while(_tradeApi->get_position_info_by_id(code_)!=0){
        //     // Record the end time
            
        //     auto end = std::chrono::high_resolution_clock::now();

        //     // Calculate the elapsed time in milliseconds
        //     auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        //     // printf("%d T: %d\n",_tradeApi->get_position_info_by_id(code_, position_p),elapsed.count());
        //     if (elapsed.count() > 1000){
        //         query_ret = false;
        //         printf("Fail to query, high latency issue.");
        //         break;
        //     }
        //     // printf("RECEIVED INFO: OnRspQryPosition: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        // }
        // if (query_ret){
        //     std::string ref = _tradeApi->get_ref_system_id(code_);
		// 	printf("ref id %s\n", ref.c_str());
        //     // printf("RECEIVED INFO: OnRspQryPosition[%d]: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", request_id, position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        // }
        
	}
}

void goodsbase::Cancel(char direction){
    return;
}

void goodsbase::Query(){
    if (_tradeApi) {
        
        request_count++;
        int request_id = request_count+2;
		// std::string errMsg;
        auto ret = _tradeApi->queryByID(code_);
		ret = 0;
        // OrderTicket(price > 0 ? BuyLimit : BuyMarket, "", code_, 0, price, errMsg);
		if (ret != 0) {
			printf("---\n查阅请求失败, %s \n", code_.c_str());
		}
		else
		{
			printf("---\n查阅请求成功, %s \n", code_.c_str());
		}
        TORASTOCKAPI::CTORATstpPositionField* position_p;
        auto start = std::chrono::high_resolution_clock::now();
        bool query_ret = true;
        while(_tradeApi->get_position_info_by_id(code_)!=0){
            // Record the end time
            
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // printf("%d T: %d\n",_tradeApi->get_position_info_by_id(code_, position_p),elapsed.count());
            if (elapsed.count() > 2000){
                query_ret = false;
                printf("Fail to query, high latency issue.\n");
                break;
            }
            // printf("RECEIVED INFO: OnRspQryPosition: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        }
		// printf("query 112\n");

        if (query_ret){
            position_p = _tradeApi->postion_map_[code_];
            printf("RECEIVED INFO: OnRspQryPosition[%d]: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", request_id, position_p->InvestorID, position_p->SecurityID, position_p->HistoryPos, position_p->TodayBSPos, position_p->TodayPRPos,position_p->AvailablePosition, position_p->CurrentPosition);
        }
		// printf("query 113\n");

        
	}
}

// 撤单

// int main(int argc, char *argv[])
// {
// 	// 打印接口版本号
// 	printf("TradeApiVersion:[%s]\n", TORASTOCKAPI::CTORATstpTraderApi::GetApiVersion());

// 	// 创建接口对象
// 	// pszFlowPath为私有流和公有流文件存储路径，若订阅私有流和公有流且创建多个接口实例，每个接口实例应配置不同的路径
// 	// bEncrypt为网络数据是否加密传输，考虑数据安全性，建议以互联网方式接入的终端设置为加密传输
// 	TORASTOCKAPI::CTORATstpTraderApi *demo_trade_api = TORASTOCKAPI::CTORATstpTraderApi::CreateTstpTraderApi("./flow", false);

// 	// 创建回调对象
    
// 	TradeSpi trade_spi(demo_trade_api, TraderConfig::instance());

// 	// 注册回调接口
// 	demo_trade_api->RegisterSpi(&trade_spi);


// #if 1	//模拟环境，TCP 直连Front方式
// 	// 注册单个交易前置服务地址
// 	const char* TD_TCP_FrontAddress="tcp://210.14.72.21:4400";//仿真交易环境
// 	//const char* TD_TCP_FrontAddress="tcp://210.14.72.15:4400";//24小时环境A套
// 	//const char* TD_TCP_FrontAddress="tcp://210.14.72.16:9500";////24小时环境B套
// 	demo_trade_api->RegisterFront((char*)TD_TCP_FrontAddress);
// 	// 注册多个交易前置服务地址，用逗号隔开
// 	//demo_trade_api->RegisterFront("tcp://10.0.1.101:6500,tcp://10.0.1.101:26500");
// 	printf("TD_TCP_FensAddress[sim or 24H]::%s\n", TD_TCP_FrontAddress);

// #else	//模拟环境，FENS名字服务器方式
// 	const char* TD_TCP_FensAddress ="tcp://210.14.72.21:42370";//模拟环境通用fens地址
// 	/********************************************************************************
// 	 * 注册 fens 地址前还需注册 fens 用户信息，包括环境编号、节点编号、Fens 用户代码等信息
// 	 * 使用名字服务器的好处是当券商系统部署方式发生调整时外围终端无需做任何前置地址修改
// 	 * *****************************************************************************/
// 	TORASTOCKAPI::CTORATstpFensUserInfoField fens_user_info_field;
// 	memset(&fens_user_info_field, 0, sizeof(fens_user_info_field));
// 	strcpy(fens_user_info_field.FensEnvID,"stock");//必填项，暂时固定为“stock”表示普通现货柜台
// 	strcpy(fens_user_info_field.FensNodeID, "sim");//必填项，生产环境需按实际填写,仿真环境为sim
// 	//strcpy(fens_user_info_field.FensNodeID, "24a");//必填项，生产环境需按实际填写,24小时A套环境为24a
// 	//strcpy(fens_user_info_field.FensNodeID, "24b");//必填项，生产环境需按实际填写,24小时B套环境为24b
// 	demo_trade_api->RegisterFensUserInfo(&fens_user_info_field);
// 	demo_trade_api->RegisterNameServer((char*)TD_TCP_FensAddress);
// 	printf("TD_TCP_FensAddress[%s]::%s\n", fens_user_info_field.FensNodeID,TD_TCP_FensAddress);

// #endif




// 	// 订阅公有流和私有流
// 	demo_trade_api->SubscribePrivateTopic(TORASTOCKAPI::TORA_TERT_QUICK);
// 	demo_trade_api->SubscribePublicTopic(TORASTOCKAPI::TORA_TERT_QUICK);
// 	/*	************************************
// 	*	TORA_TERT_RESTART，从日初开始
// 	*	TORA_TERT_RESUME,  从断开时候开始
// 	*	TORA_TERT_QUICK ，从最新时刻开始
// 	****************************************/

// 	// 启动
//     std::string code = "000027";
//     goodsbase good = goodsbase(code, 0, &trade_spi);
// 	demo_trade_api->Init();
//     while(1){
//         if (trade_spi.get_login_status()){
//             break;
//         }
//     };
// 	good.Query();
//     // good.Buy(100, 6.15);
//     // good.Sell(6.12);
//     good.QueryReq(2);
// 	// 等待结束
// 	getchar();
//     printf("End...\n");
// 	//demo_trade_api->Join();

// 	// 释放，注意不允许在回调函数内调用Release接口，否则会导致线程死锁
// 	demo_trade_api->Release();

// 	return 0;
// }