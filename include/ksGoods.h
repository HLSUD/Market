#pragma once
# include <iostream>
#include <cstring>
// #include "BseExanicStruct.h"
// #include "SseExanicStruct.h"
// #include "SzseExanicStruct.h"
#include <memory>
#include "Lev2Struct_Extension.h"
#include "stock.h"
#include "goodsbase.h"

// using namespace istone::base;

class iGoods {
public:
    virtual ~iGoods() = default;

    virtual void Init() = 0;

    virtual void onSseEntrust(TORALEV2API_V2::SHSseNGTS* data) = 0;
    virtual void onSseTrade(TORALEV2API_V2::SHSseNGTS* data) = 0;
    // virtual void onSseDepth(TORALEV2API_V2::SeSnapshot* data, istone::base::DataType hasPrice) = 0;
    virtual void onSseSnapshot(TORALEV2API_V2::SeSnapshot* data) = 0;
    // virtual void onSseDepthFifty(SseDepthFifty* data) = 0;

    virtual void onSzseEntrust(TORALEV2API_V2::SzseEntrust* data) = 0;
    virtual void onSzseTrade(TORALEV2API_V2::SzseTrade* data) = 0;
    // virtual void onSzseDepth(TORALEV2API_V2::SeSnapshot* data) = 0;
    virtual void onSzseSnapshot(TORALEV2API_V2::SeSnapshot* data) = 0;
    // virtual void onSzseDepthFifty(SzseDepthFifty* data) = 0;
};

/**

 */
class goods : public iGoods {
public:
    // goods(const std::string& code):code_(code){
    // }

    goods(Stock& stock, TradeSpi *trade_spi){
        code_ = stock.get_stock_id();
        market_cap = stock.get_cap();
        price_limit = stock.get_price_limit();
        good_trade = new goodsbase(code_, 0, trade_spi);
    }

    virtual void Init() {
        //std::cout << "Init" << std::endl;
    }

    virtual void onSseEntrust(TORALEV2API_V2::SHSseNGTS* data) { 
        // std::cout << "onSseEntrust" << std::endl;
        // if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
        //         std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        // } else {
        //     if (std::string(lastSecurityID) != "")
        //         std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     else
        //     {
        //         std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     }
        //     // 更新最近的股票代码
        //     std::strncpy(lastSecurityID, data->SecurityID, 8);
        // }
        // printf("Shanghai Entrust SecurityID[%s] ", data->field->SecurityID);
		// printf("ExchangeID[%c] ", data->field->ExchangeID);
		// printf("MainSeq[%d] ", data->field->MainSeq);
		// printf("SubSeq[%lld] ", data->field->SubSeq);
		// printf("TickTime[%d] ", data->field->TickTime);
		// printf("TickType[%c] ", data->field->TickType);
		// printf("BuyNo[%lld] ", data->field->BuyNo);
		// printf("SellNo[%lld] ", data->field->SellNo);
		// printf("Price[%.2f] ", data->field->Price);
		// printf("Volume[%lld] ", data->field->Volume);
		// printf("TradeMoney[%.2f] ", data->field->TradeMoney);
		// printf("Side[%c] ", data->field->Side);
		// printf("TradeBSFlag[%d] ", data->field->TradeBSFlag);
		// printf("Info1[%d] ", data->field->Info1);
		// printf("Info2[%d] ", data->field->Info2);
		// printf("Info3[%d] \n", data->field->Info3);
    }
    
    virtual void onSseTrade(TORALEV2API_V2::SHSseNGTS* data){ 

        // std::cout << "onSseTrade" << std::endl;
        // if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
        //         std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        // } else {
        //     if (std::string(lastSecurityID) != "")
        //         std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     else
        //     {
        //         std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     }
        //     // 更新最近的股票代码
        //     std::strncpy(lastSecurityID, data->SecurityID, 8);
        // }
        // printf("Shanghai Trade SecurityID[%s] ", data->field->SecurityID);
		// printf("ExchangeID[%c] ", data->field->ExchangeID);
		// printf("MainSeq[%d] ", data->field->MainSeq);
		// printf("SubSeq[%lld] ", data->field->SubSeq);
		// printf("TickTime[%d] ", data->field->TickTime);
		// printf("TickType[%c] ", data->field->TickType);
		// printf("BuyNo[%lld] ", data->field->BuyNo);
		// printf("SellNo[%lld] ", data->field->SellNo);
		// printf("Price[%.2f] ", data->field->Price);
		// printf("Volume[%lld] ", data->field->Volume);
		// printf("TradeMoney[%.2f] ", data->field->TradeMoney);
		// printf("Side[%c] ", data->field->Side);
		// printf("TradeBSFlag[%d] ", data->field->TradeBSFlag);
		// printf("Info1[%d] ", data->field->Info1);
		// printf("Info2[%d] ", data->field->Info2);
		// printf("Info3[%d] \n", data->field->Info3);
        // // 打印结构体内容
        // std::cout << "SseTrade Structure Details:" << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
        // // 格式化输出设置
        // std::cout << "TradeIndex: " << data->TradeIndex << std::endl;
        // std::cout << "TradeChannel: " << data->TradeChannel << std::endl;
        // std::cout << "SecurityID: " << std::string(data->SecurityID, 8) << std::endl;
        // std::cout << "TradeTime: " << data->TradeTime << std::endl;
        // std::cout << "TradePrice: " << data->TradePrice / 1000.0 << std::endl; // 转换为实际价格
        // std::cout << "TradeQty: " << data->TradeQty / 1000.0 << std::endl;   // 转换为实际数量
        // std::cout << "TradeMoney: " << data->TradeMoney / 100000.0 << std::endl; // 转换为实际金额
        // std::cout << "-----------------------------------------" << std::endl;
    }
    
    virtual void onSseSnapshot(TORALEV2API_V2::SeSnapshot* data){
        // std::cout << "onSseSnapshot" << std::endl;
        // if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
        //         std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        // } else {
        //     if (std::string(lastSecurityID) != "")
        //         std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     else
        //     {
        //         std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     }
        //     // 更新最近的股票代码
        //     std::strncpy(lastSecurityID, data->SecurityID, 8);
        // }
    }
    // virtual void onSseDepth(SseDepth* data, istone::base::DataType hasPrice){ 
        // std::cout << "onSseDepth" << std::endl; 
        // std::cerr << code_ << ":" << mystr2(data->SecurityID) << std::endl;
        // std::cout << "SseDepth Structure Details:" << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
        // std::cout << "MsgType: " << data->MsgType << std::endl;
        // std::cout << "UpdateTime: " << data->UpdateTime << std::endl;
        // std::cout << "SecurityID: " << std::string(data->SecurityID, 6) << std::endl;
        // std::cout << "PreClosePx: " << data->PreClosePx / 1000.0 << std::endl;
        // std::cout << "OpenPx: " << data->OpenPx / 1000.0 << std::endl;
        // std::cout << "HighPx: " << data->HighPx / 1000.0 << std::endl;
        // std::cout << "LowPx: " << data->LowPx / 1000.0 << std::endl;
        // std::cout << "LastPx: " << data->LastPx / 1000.0 << std::endl;
        // std::cout << "Bid Prices: ";
        // for (int i = 0; i < 10; ++i) {
        //     std::cout << data->BidPrice[i] / 1000.0 << " ";
        // }
        // std::cout << std::endl;
        // if (hasPrice == istone::base::DataType::HAS_PRICE)
        // {
        //     std::cout << "Bid Quantities: ";
        //     for (int i = 0; i < 10; ++i) {
        //         std::cout << data->BidQty[i] / 1000.0 << " ";
        //     }
        // }
        // std::cout << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
    // }
    // virtual void onSseDepthFifty(SseDepthFifty* data){ 
    //     // std::cout << "onDepthFifty" << std::endl; 
    // }

    virtual void onSzseEntrust(TORALEV2API_V2::SzseEntrust* data){ 
        // std::cout << "onSzseEntrust" << std::endl; 
        // //std::cerr << code_ << ":" << mystr2(data->SecurityID) << std::endl;
        // if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
        //         std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        // } else {
        //     if (std::string(lastSecurityID) != "")
        //         std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     else
        //     {
        //         std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     }
        //     // 更新最近的股票代码
        //     std::strncpy(lastSecurityID, data->SecurityID, 8);
        // }
    }
    virtual void onSzseTrade(TORALEV2API_V2::SzseTrade* data){
        // std::cout << "onSzseEntrust" << std::endl; 
        
        //std::cerr << code_ << ":" << mystr2(data->SecurityID) << std::endl;
        if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
            if (data->field->TradePrice>1){
                // good_trade->print_code();
                // good_trade->Query(); //查询持仓
                // printf("end\n");
                // good_trade->Buy(100, data->field->TradePrice); //买入
                // good_trade->Sell(data->field->TradePrice); //卖出
                good_trade->QueryReq(2); //撤单
            }
                // std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
                // printf("Market cap: %lf, price limit: %lf\n", market_cap,price_limit);
        } else {
            if (std::string(lastSecurityID) != "")
                std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
            else
            {
                std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
                printf("price %lf\n", data->field->TradePrice);
                if (data->field->TradePrice>1){
                    // good_trade->print_code();
                    // good_trade->Query(); //查询持仓
                    // printf("end\n");
                    // good_trade->Buy(100, data->field->TradePrice); //买入
                    // good_trade->Sell(data->field->TradePrice); //卖出
                    good_trade->QueryReq(2); //撤单
                }
                
                    
                    
            }
            // 更新最近的股票代码
            std::strncpy(lastSecurityID, data->SecurityID, 8);
        } 
        // std::cout << "onSzseTrade" << std::endl;
        // // 打印各字段内容
        // std::cout << "MsgType: " << data->MsgType << std::endl;
        // std::cout << "MDStreamID: " << std::string(data->MDStreamID, 3) << std::endl;
        // std::cout << "Applseqnum: " << data->Applseqnum << std::endl;
        // std::cout << "BidApplSeqNum: " << data->BidApplSeqNum << std::endl;
        // std::cout << "OfferApplSeqNum: " << data->OfferApplSeqNum << std::endl;
        // std::cout << "SecurityID: " << std::string(data->SecurityID, 8) << std::endl;
        // std::cout << "ChannelNo: " << data->ChannelNo << std::endl;
        // std::cout << "ExecType: " << data->ExecType << std::endl;
        // std::cout << "TradePrice: " << data->TradePrice / 10000.0 << std::endl; // 转换为实际价格
        // std::cout << "TradeQty: " << data->TradeQty / 100.0 << std::endl;       // 转换为实际数量
        // std::cout << "TransactTime: " << data->TransactTime << std::endl;
        // std::cout << "Rsv1: " << std::string(data->Rsv1, 8) << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
    }
    virtual void onSzseSnapshot(TORALEV2API_V2::SeSnapshot* data){
        // std::cout << "onSzseSnapshot" << std::endl;
        // if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
        //         std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        // } else {
        //     if (std::string(lastSecurityID) != "")
        //         std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     else
        //     {
        //         std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
        //     }
        //     // 更新最近的股票代码
        //     std::strncpy(lastSecurityID, data->SecurityID, 8);
        // }
    }
    /*
    virtual void onSzseDepth(SzseDepth* data){ 
        //std::cout << "onSzseDepth" << std::endl; 
        // std::cout << "SzseDepth Structure Details:" << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
        // std::cout << "MsgType: " << data->MsgType << std::endl;
        // std::cout << "MDStreamID: " << std::string(data->MDStreamID, 3) << std::endl;
        // std::cout << "TradingPhaseCode: " << std::string(data->TradingPhaseCode, 2) << std::endl;
        // std::cout << "SecurityID: " << std::string(data->SecurityID, 6) << std::endl;
        // std::cout << "OrigTime: " << data->OrigTime << std::endl;
        // std::cout << "PrevClosePx: " << data->PrevClosePx / 10000.0 << std::endl;
        // std::cout << "LastPrice: " << data->LastPrice / 1000000.0 << std::endl;
        // std::cout << "-----------------------------------------" << std::endl;
    }
    virtual void onSzseDepthFifty(SzseDepthFifty* data){ 
        //std::cout << "onSzseDepth" << std::endl; 
    }
    */

protected:
    int recvCnt_ = 0;
    std::string code_;
    double market_cap;
    double price_limit;
    char lastSecurityID[8] = {0};
    goodsbase *good_trade;
    
};

