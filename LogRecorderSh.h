#pragma once
#include "SseExanicStruct.h"
#include "fmt/format.h"
#include <stdio.h>

using namespace istone::base;
using namespace std;
#pragma pack(push, 1)
class MyStructShTbtEntrust
{
public:
    MyStructShTbtEntrust() {}

    static void printHeader(FILE *fp)
    {
        string title = "MsgType,OrderType,OrderBSFlag,TickBSFlag,\
OrderIndex,OrderChannel,SecurityID,OrderTime,\
OrderNO,OrderPrice,Balance,BizIndex,\
Rsv\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SseEntrust *data, FILE *fp)
    {
        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{}\n",
                                      data->MsgType,
                                      data->OrderType,
                                      data->OrderBSFlag,
                                      data->TickBSFlag,

                                      data->OrderIndex,
                                      data->OrderChannel,
                                      mystr2(data->SecurityID),
                                      data->OrderTime,

                                      data->OrderNO,
                                      data->OrderPrice,
                                      data->Balance,
                                      data->BizIndex,

                                      "");
        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShTbtTrade
{
public:
    MyStructShTbtTrade() {}

    static void printHeader(FILE *fp)
    {
        string title = "\
MsgType,TradeIndex,TradeChannel,SecurityID,\
TradeTime,TradePrice,TradeQty,TradeMoney,\
TradeBuyNo,TradeSellNo,BizIndex,TradeBSFlag,\
Rsv\n";
        fwrite(title.c_str(), 1, title.size(), fp);

        fflush(fp);
    }

    static void print(SseTrade *data, FILE *fp)
    {
        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{}\n",

                                      data->MsgType,
                                      data->TradeIndex,
                                      data->TradeChannel,
                                      mystr2(data->SecurityID),

                                      data->TradeTime,
                                      data->TradePrice,
                                      data->TradeQty,
                                      data->TradeMoney,

                                      data->TradeBuyNo,
                                      data->TradeSellNo,
                                      data->BizIndex,
                                      data->TradeBSFlag,

                                      "");

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShIndexMarket
{
public:
    MyStructShIndexMarket() {}

    static void printHeader(FILE *fp)
    {
        char sz[1024] = {0};
  
        sprintf(sz, "MsgType,UpdateTime,SecurityID,PreCloseIndex,\
OpenIndex,Turnover,HighIndex,LowIndex,\
LastIndex,TradeTime,TotalVolumeTrade,CloseIndex,\
Rsv\n");

        fwrite(sz, 1, strlen(sz), fp);
        fflush(fp);
    }

    static void print(SseIndex *data, FILE *fp)
    {
        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},{}\n",

                                      data->MsgType,
                                      data->UpdateTime,
                                      data->SecurityID,
                                      data->PreCloseIndex,

                                      data->OpenIndex,
                                      data->Turnover,
                                      data->HighIndex,
                                      data->LowIndex,

                                      data->LastIndex,
                                      data->TradeTime,
                                      data->TotalVolumeTrade,
                                      data->CloseIndex,

                                      "");

        auto ret = fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShDepthMarketOrBond
{
public:
    MyStructShDepthMarketOrBond() {}

    static void printHeader(FILE *fp)
    {
        string bid_title = "";
        string bidqty_title = "";
        string ask_title = "";
        string askqty_title = "";

        for (auto i = 1; i < 11; i++)
        {
            bid_title += ("bid" + to_string(i) + ",");
            bidqty_title += ("bidqty" + to_string(i) + ",");
            ask_title += ("ask" + to_string(i) + ",");
            askqty_title += ("askqty" + to_string(i) + ",");
        }
        bid_title.pop_back();
        bidqty_title.pop_back();
        ask_title.pop_back();
        askqty_title.pop_back();

        std::string str = fmt::format("\
MsgType,UpdateTime,SecurityID,PreClosePx,\
OpenPx,HighPx,LowPx,LastPx,\
ClosePx,InstruStatus,TradingPhaseCode,UpperLimitPrice,\
LowerLimitPrice,NumTrades,TotalVolumeTrade,TotalValueTrade,\
TotalBidQty,WeightedAvgBidPx,TotalOfferQty,WeightedAvgOfferPx,\
WeightedAvgPx,TotalBidNumber,TotalOfferNumber,\
{},{},{},{}\n",

                                      bid_title.c_str(),
                                      bidqty_title.c_str(),
                                      ask_title.c_str(),
                                      askqty_title.c_str());

        auto ret = fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }

    static void print(SseDepth *data, FILE *fp, DataType hasPrice)
    {
        string bid = "";
        string bidqty = "";
        string ask = "";
        string askqty = "";

        ////
        std::string strFormat =
            "\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},";

        std::string str = fmt::format(strFormat,

                                      data->MsgType,            
                                      data->UpdateTime,         
                                      mystr2(data->SecurityID), 
                                      data->PreClosePx,         

                                      data->OpenPx,
                                      data->HighPx, 
                                      data->LowPx,  
                                      data->LastPx, 

                                      data->ClosePx,                  
                                      mystr2(data->InstruStatus),     
                                      mystr2(data->TradingPhaseCode), 
                                      data->UpperLimitPrice,          

                                      data->LowerLimitPrice,  
                                      data->NumTrades,        
                                      data->TotalVolumeTrade, 
                                      data->TotalValueTrade,  

                                      data->TotalBidQty,        
                                      data->WeightedAvgBidPx,   
                                      data->TotalOfferQty,      
                                      data->WeightedAvgOfferPx, 

                                      data->WeightedAvgPx,  
                                      data->TotalBidNumber, 
                                      data->TotalOfferNumber);

        {
            if (HAS_PRICE == hasPrice)
            {
                for (auto i = 0; i < 10; i++)
                {
                    bid += to_string((data->BidPrice[i]));  //transformSsePrice
                    bidqty += to_string((data->BidQty[i])); //transformSseQty
                    ask += to_string((data->AskPrice[i]));  //transformSsePrice
                    askqty += to_string((data->AskQty[i])); //transformSseQty
                    bid += ",";
                    bidqty += ",";
                    ask += ",";
                    askqty += ",";
                }
                str += bid;
                str += bidqty;
                str += ask;
                str += askqty;
            }
        }
        str.append("\n");
        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShDepthFifty
{
public:
    MyStructShDepthFifty() {}

    static void printHeader(FILE *fp)
    {
        string bidorder_title = "";
        string askorder_title = "";

        for (auto i = 1; i < 51; i++)
        {
            bidorder_title += ("bid_order" + to_string(i) + ",");
            askorder_title += ("ask_order" + to_string(i) + ",");
        }
        bidorder_title.pop_back();
        askorder_title.pop_back();

        std::string strTitle = fmt::format("\
MsgType,UpdateTime,SecurityID,\
BidOrderPrice,BidOrderQty,AskOrderPrice,AskOrderQty,Rsv,\
BidNumOfOrders,AskNumOfOrders,BidNoOrders,AskNoOrders,\
{},{}\n",
                                           bidorder_title.c_str(),
                                           askorder_title.c_str());

        auto ret = fwrite(strTitle.c_str(), 1, strTitle.size(), fp);
        fflush(fp);
    }

    static void print(SseDepthFifty *pData, FILE *fp)
    {
        string bid_order = "";
        string ask_order = "";

        {

            for (auto i = 0; i < 50; i++)
            {
                if (i < pData->BidNoOrders)
                    bid_order += to_string(pData->Orders[i]);
                else
                    bid_order += "0";
                bid_order += ",";
            }
            int askStartIndex = pData->BidNoOrders;

            for (auto i = 0; i < 50; i++)
            {
                if (i < pData->AskNoOrders)
                    ask_order += to_string(pData->Orders[i + askStartIndex]);
                else
                    ask_order += "0";
                ask_order += ",";
            }
        }

        ////

        {
            std::string str = fmt::format("\{},\
{},{},{},{},{},{},{},\
{},{},{},{},\
{}{}\n",

                                          pData->MsgType,

                                          pData->UpdateTime,
                                          mystr2(pData->SecurityID),
                                          pData->BidOrderPrice,
                                          pData->BidOrderQty,
                                          pData->AskOrderPrice,
                                          pData->AskOrderQty,
                                          "",

                                          pData->BidNumOfOrders,
                                          pData->AskNumOfOrders,
                                          pData->BidNoOrders,
                                          pData->AskNoOrders,

                                          bid_order,
                                          ask_order);

            fwrite(str.c_str(), 1, str.size(), fp);
            fflush(fp);
        }
    }
};

class MyStructShOption
{
public:
    MyStructShOption() {}
    static void printHeader(FILE *fp)
    {
        std::string sz = "MsgType,SecurityID,LastPx,TradeQty,\
TradeTime,TradingPhaseCode,Rsv,NumTrades,\
TotalVolumeTrade,TotalValueTrade,PreClosePx,PreSetPx,\
TotalLongPosition,OpenPx,ClosePx,SetPx,\
HighPx,LowPx,BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,BidQty1,BidQty2,BidQty3,BidQty4,BidQty5,\
AskPrice1,AskPrice2,AskPrice3,AskPrice4,AskPrice5,AskQty1,AskQty2,AskQty3,AskQty4,AskQty5,RefrencePrice,RefrenceQty,\
UpdateDate,UpdateTime\n";
        //
        fwrite(sz.c_str(), 1, sz.size(), fp);
        fflush(fp);
    }

    static void print(SseOption *data, FILE *fp)
    {
        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},{},{},{},{},{},{},{},{},\
{},{},{},{},{},{},{},{},{},{},{},{},\
{},{}\n",

                                      data->MsgType,
                                      mystr2(data->SecurityID),
                                      data->LastPx,
                                      data->TradeQty,

                                      mystr2(data->TradeTime),
                                      mystr2(data->TradingPhaseCode),
                                      "",
                                      data->NumTrades,

                                      data->TotalVolumeTrade,
                                      data->TotalValueTrade,
                                      data->PreClosePx,
                                      data->PreSetPx,

                                      data->TotalLongPosition,
                                      data->OpenPx,
                                      data->ClosePx,
                                      data->SetPx,

                                      data->HighPx,
                                      data->LowPx,
                                      data->BidPrice[0], data->BidPrice[1], data->BidPrice[2], data->BidPrice[3], data->BidPrice[4],
                                      data->BidQty[0], data->BidQty[1], data->BidQty[2], data->BidQty[3], data->BidQty[4],

                                      data->AskPrice[0], data->AskPrice[1], data->AskPrice[2], data->AskPrice[3], data->AskPrice[4],
                                      data->AskQty[0], data->AskQty[1], data->AskQty[2], data->AskQty[3], data->AskQty[4],
                                      data->RefrencePrice,
                                      data->RefrenceQty,

                                      data->UpdateDate,
                                      data->UpdateTime);

        auto ret = fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShOrderQueue
{
public:
    MyStructShOrderQueue() {}

    static void printHeader(FILE *fp)
    {
        string title = "\
MsgType,MsgVer,Side,Channel,\
BizIndex,Applseqnum,SecurityID,Reliability,Rsv,TransactTime,\
Trade_Qty1,Trade_Qty2,Trade_Qty3,Trade_Qty4,Trade_Qty5,Trade_Qty6,Trade_Qty7,Trade_Qty8,Trade_Qty9,Trade_Qty10,\
Trade_Price1,Trade_Price2,Trade_Price3,Trade_Price4,Trade_Price5,Trade_Price6,Trade_Price7,Trade_Price8,Trade_Price9,Trade_Price10,\
TradePrice\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SseOrderQueue *data, FILE *fp)
    {
        std::string strTrade_Qty, strTradePrice;
        for (int i = 0; i < 10; ++i)
        {
            strTrade_Qty += std::to_string(data->Trade_Qty[i]);
            strTrade_Qty += ",";

            strTradePrice += std::to_string(data->Trade_Price[i]);
            strTradePrice += ",";
        }
        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{}{}{}\n",

                                      data->MsgType,
                                      data->MsgVer,
                                      data->Side,
                                      data->Channel,

                                      data->BizIndex,
                                      data->Applseqnum,
                                      mystr2(data->SecurityID),
                                      data->Reliability,

                                      mystr2(data->Rsv),
                                      data->TransactTime,

                                      strTrade_Qty,
                                      strTradePrice,
                                      data->TradePrice);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShOrderQueueErr
{
public:
    MyStructShOrderQueueErr() {}
    static void printHeader(FILE *fp)
    {
        string title = "MsgType,MsgVer,ErrType,Channel,\
TransactTime,SeqNum\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SseOrderQueueErr *data, FILE *fp)
    {
        std::string str = fmt::format("{},{},{},{},\
{},{}\n",
                                      data->MsgType,
                                      data->MsgVer,
                                      data->ErrType,
                                      data->Channel,
                                      data->TransactTime,
                                      data->BizIndex);
        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShIOPV
{
public:
    MyStructShIOPV() {}
    static void printHeader(FILE *fp)
    {
        string title = "MsgType,SecurityID,IOPV,Cstock_TradeTime,\
TradePrice,TransactTime\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SseIOPV *data, FILE *fp)
    {
        std::string str = fmt::format("{},{},{},{},\
{},{}\n",
data->MsgType,
mystr2(data->SecurityID),
data->IOPV,
data->Cstock_TradeTime,
data->TradePrice,
data->TransactTime);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructShRealtimeIndex
{
public:
    MyStructShRealtimeIndex() {}
    static void printHeader(FILE *fp)
    {
        string title = "MsgType,IndexID,LastIndex,TradeTime,\
NumTrades,TotalVolumeTrade,TotalValueTrade,PreCloseIndex,\
OpenIndex,HighIndex,LowIndex,CloseIndex\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SseRealtimeIndex *data, FILE *fp)
    {
        std::string str = fmt::format("{},{},{},{},\
{},{},{},{},\
{},{},{},{}\n",
data->MsgType,
data->IndexID,
data->LastIndex,
data->TradeTime,

data->NumTrades,
data->TotalVolumeTrade,
data->TotalValueTrade,
data->PreCloseIndex,

data->OpenIndex,
data->HighIndex,
data->LowIndex,
data->CloseIndex);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

#pragma pack(pop)

class LogRecorderSh
{
public:
    LogRecorderSh()
    {
        fp_entrust_ = fopen("sh_tbt_entrust.csv", "wt");
        fp_trade_ = fopen("sh_tbt_trade.csv", "wt");
        fp_index_ = fopen("sh_index.csv", "wt");

        fp_depth_ = fopen("sh_depth.csv", "wt");
        fp_depth_fifty_ = fopen("sh_depth_fifty.csv", "wt");
        fp_option_ = fopen("sh_option.csv", "wt");

        fp_orderbook_ = fopen("sh_orderbook.csv", "wt");
        fp_orderbook_err_ = fopen("sh_orderbook_err.csv", "wt");

        fp_iopv_ = fopen("sh_iopv.csv", "wt");
        fp_realtime_index_ = fopen("sh_realtime_index.csv", "wt");

        MyStructShTbtEntrust::printHeader(fp_entrust_);
        MyStructShTbtTrade::printHeader(fp_trade_);
        MyStructShIndexMarket::printHeader(fp_index_);
        MyStructShDepthMarketOrBond::printHeader(fp_depth_);
        MyStructShDepthFifty::printHeader(fp_depth_fifty_);
        MyStructShOption::printHeader(fp_option_);

        MyStructShOrderQueue::printHeader(fp_orderbook_);
        MyStructShOrderQueueErr::printHeader(fp_orderbook_err_);

        MyStructShIOPV::printHeader(fp_iopv_);
        MyStructShRealtimeIndex::printHeader(fp_realtime_index_);

    }
    ~LogRecorderSh()
    {

        fclose(fp_entrust_);
        fclose(fp_trade_);
        fclose(fp_index_);
        fclose(fp_depth_);
        fclose(fp_depth_fifty_);
        fclose(fp_option_);
        fclose(fp_orderbook_);
        fclose(fp_orderbook_err_);
        fclose(fp_iopv_);
    }

    void addSseEntrustNode(SseEntrust *data, unsigned long longm_local_time)
    {
        MyStructShTbtEntrust::print(data, fp_entrust_);
    }
    void addSseTradeNode(SseTrade *data, unsigned long longm_local_time)
    {
        MyStructShTbtTrade::print(data, fp_trade_);
    }
    void addSseIndexNode(SseIndex *data, unsigned long longm_local_time)
    {
        MyStructShIndexMarket::print(data, fp_index_);
    }

    void addSseMdNode(SseDepth *data, unsigned long longm_local_time, DataType dataType)
    {
        MyStructShDepthMarketOrBond::print(data, fp_depth_, dataType);
    }
    void addSseDepthFiftyNode(SseDepthFifty *data, unsigned long longm_local_time)
    {
        MyStructShDepthFifty::print(data, fp_depth_fifty_);
    }
    void addSseOptionData(SseOption *data, unsigned long longm_local_time)
    {
        MyStructShOption::print(data, fp_option_);
    }

    void addSseOrderbookQueueNode(SseOrderQueue *data, unsigned long longm_local_time)
    {
        MyStructShOrderQueue::print(data, fp_orderbook_);
    }

    void addSseOrderBookQueueErrNode(SseOrderQueueErr *data, unsigned long longm_local_time)
    {
        MyStructShOrderQueueErr::print(data, fp_orderbook_err_);
    }
    void addSseIOPVNode(SseIOPV *data, unsigned long longm_local_time)
    {
        MyStructShIOPV::print(data, fp_iopv_);
    }
    void addSseRealtimeIndexNode(SseRealtimeIndex *data, unsigned long longm_local_time)
    {
        MyStructShRealtimeIndex::print(data, fp_realtime_index_);
    }

private:
    FILE *fp_entrust_;
    FILE *fp_trade_;
    FILE *fp_index_;

    FILE *fp_depth_;
    FILE *fp_depth_fifty_;
    FILE *fp_option_;

    FILE *fp_orderbook_;
    FILE *fp_orderbook_err_;

    FILE *fp_iopv_;
    FILE* fp_realtime_index_;
};
