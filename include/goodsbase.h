#ifndef GOODSBASE_H
#define GOODSBASE_H

// #include "atp_quant_api.h"
#include <utility>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <limits>
#include <stdint.h>
#include <sstream>
#include "trade.h"
//#include "define.h"

// using namespace atp::quant_api;

class ITrader {
public:
	virtual ~ITrader() = default;
	/**
	 * 下单接口
	 * @param eType 委托单类型
	 * @param mkt 市场代码 深圳 SZ 上海 SH
	 * @param symbol 证券代码 如 600000
	 * @param orderQty 下单数量
	 * @param orderPrice 下单价格
	 * @param errMsg 错误信息，接口报错时填写此值
	 * @return 成功返回0， 其它错误
	 */
	// virtual int OrderTicket(
    //     ATPSideType side,
    //     ATPOrdTypeType orderType,
	// 	std::string mkt,
    //     std::string symbol,
	// 	uint32_t orderQty,
    //     double orderPrice,
    //     std::string& errMsg) = 0;
};

class goodsbase {
public:
    goodsbase(std::string code, int request_count, TradeSpi* trade_api)
        :  code_(code), request_count(request_count), _tradeApi(trade_api) {
    }

protected:
	TradeSpi* _tradeApi = nullptr;
    std::string code_;
	// 买入次数统计, 如果 >0 则表示下过单
	int request_count = 0; // mutex?


public:
	void print_code(){
		printf("code %s\n", code_.c_str());
	}
	/**
	 * 买入
	 * @param qty 下单数量
	 * @param price 
	 */
	void Buy(int qty, double price = 0);
	/**
	 * 卖出
	 * @param qty 下单数量
	 * @param price 下单价格
	 */
	void Sell(int qty, double price = 0);

	/**
	 * 卖出
	 * @param qty 下单数量
	 * @param price 下单价格
	 */
	void Sell(double price = 0);

    /**
     * query stock
    */
    void Query();

    // void QueryReq();
    void QueryReq(int type);

    void Cancel(char direction);
};

#endif //GOODSBASE_H
