#pragma once
# include <iostream>
#include <cstring>
#include "BseExanicStruct.h"
#include "SseExanicStruct.h"
#include "SzseExanicStruct.h"
#include <memory>

using namespace istone::base;

class iGoods {
public:
    virtual ~iGoods() = default;

    virtual void Init() = 0;

    virtual void onSseEntrust(SseEntrust* data) = 0;
    virtual void onSseTrade(istone::base::SseTrade* data) = 0;
    virtual void onSseDepth(istone::base::SseDepth* data, istone::base::DataType hasPrice) = 0;
    virtual void onSseDepthFifty(SseDepthFifty* data) = 0;

    virtual void onSzseEntrust(SzseEntrust* data) = 0;
    virtual void onSzseTrade(SzseTrade* data) = 0;
    virtual void onSzseDepth(SzseDepth* data) = 0;
    virtual void onSzseDepthFifty(SzseDepthFifty* data) = 0;
};

/**

 */
class goods : public iGoods {
public:
    goods(const std::string& code):code_(code){
    }


    virtual void Init() {
        //std::cout << "Init" << std::endl;
    }

    virtual void onSseEntrust(SseEntrust* data) { 
        //std::cout << "onSseEntrust" << std::endl;
     }

    virtual void onSseTrade(SseTrade* data){ 
        // std::cout << "onSseTrade" << std::endl;
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
    virtual void onSseDepth(SseDepth* data, istone::base::DataType hasPrice){ 
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
    }
    virtual void onSseDepthFifty(SseDepthFifty* data){ 
        // std::cout << "onDepthFifty" << std::endl; 
    }

    virtual void onSzseEntrust(SzseEntrust* data){ 
        std::cout << "onSzseEntrust" << std::endl; 
        //std::cerr << code_ << ":" << mystr2(data->SecurityID) << std::endl;
        if (std::strncmp(lastSecurityID, data->SecurityID, 8) == 0) {
                std::cout << "推送的是同一只股票: " << std::string(data->SecurityID, 8) << std::endl;
        } else {
            if (std::string(lastSecurityID) != "")
                std::cout << "推送的是不同的股票: " << std::string(data->SecurityID, 8) << std::endl;
            else
            {
                std::cout << "首次推送股票: " << std::string(data->SecurityID, 8) << std::endl;
            }
            // 更新最近的股票代码
            std::strncpy(lastSecurityID, data->SecurityID, 8);
        }
    }
    virtual void onSzseTrade(SzseTrade* data){ 
        std::cout << "onSzseTrade" << std::endl;
        // 打印各字段内容
        std::cout << "MsgType: " << data->MsgType << std::endl;
        std::cout << "MDStreamID: " << std::string(data->MDStreamID, 3) << std::endl;
        std::cout << "Applseqnum: " << data->Applseqnum << std::endl;
        std::cout << "BidApplSeqNum: " << data->BidApplSeqNum << std::endl;
        std::cout << "OfferApplSeqNum: " << data->OfferApplSeqNum << std::endl;
        std::cout << "SecurityID: " << std::string(data->SecurityID, 8) << std::endl;
        std::cout << "ChannelNo: " << data->ChannelNo << std::endl;
        std::cout << "ExecType: " << data->ExecType << std::endl;
        std::cout << "TradePrice: " << data->TradePrice / 10000.0 << std::endl; // 转换为实际价格
        std::cout << "TradeQty: " << data->TradeQty / 100.0 << std::endl;       // 转换为实际数量
        std::cout << "TransactTime: " << data->TransactTime << std::endl;
        std::cout << "Rsv1: " << std::string(data->Rsv1, 8) << std::endl;
        std::cout << "-----------------------------------------" << std::endl;
    }
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
    

protected:
    int recvCnt_ = 0;
    std::string code_;
    char lastSecurityID[8] = {0};
};

