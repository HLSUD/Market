#pragma once
#include "SzseExanicStruct.h"
#include "fmt/format.h"
#include <stdio.h>


using namespace  istone::base;
using namespace std;
#pragma pack(push, 1)
class MyStructSzTbtEntrust
{
public:
	MyStructSzTbtEntrust() { }

	static void printHeader(FILE* fp)
	{
		string title = "\
MsgType,MDStreamID,Applseqnum,SecurityID,\
ChannalNo,Side,OrdType,Price,\
OrderQty,TransactTime,Rsv\n";
		fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
	}

	static void print(SzseEntrust* data, FILE* fp)
	{
        SzseEntrust* real = data;
		std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{}\n",

		real->MsgType,
		mystr2(real->MDStreamID),
		real->Applseqnum,
		mystr2(real->SecurityID),

		real->ChannelNo,
		real->Side,
		real->OrdType,
		real->Price,

		real->OrderQty,
		real->TransactTime,
		mystr2(real->Rsv));

		fwrite(str.c_str(), 1, str.size(), fp);
		fflush(fp);
	}
};

class MyStructSzTbtTrade
{
public:
	MyStructSzTbtTrade() {  }

	static void printHeader(FILE* fp)
	{
		string title = "\
MsgType,MDStreamID,Applseqnum,BidApplSeqNum,\
OfferApplSeqNum,SecurityID,ChannalNo,ExecType,\
Rsv0,TradePrice,TradeQty,TransactTime,\
Rsv1\n";
		fwrite(title.c_str(), 1, title.size(), fp);

		fflush(fp);

	}



	static void print(SzseTrade* data, FILE* fp)
	{
        SzseTrade* real = data;

		std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{}\n",

real->MsgType,
mystr2(real->MDStreamID),
real->Applseqnum,
real->BidApplSeqNum,

real->OfferApplSeqNum,
mystr2(real->SecurityID),
real->ChannelNo,
real->ExecType,

' ',
real->TradePrice,
real->TradeQty,
real->TransactTime,

"");

		fwrite(str.c_str(), 1, str.size(), fp);
		fflush(fp);
	}
};

class MyStructSzIndex
{
public:
    MyStructSzIndex() {}

	static void printHeader(FILE* fp)
	{
		char sz[1024] = { 0 };
        //落地时间戳、ticker（股票代码）、DataTime（交易所时间戳）、后面加交易所传过来全量字段；
		sprintf(sz, "\
MsgType,TradingPhaseCode,OrigTime,SecurityID,\
NumTrades,TotalVolumeTrade,TotalValueTrade,LastIndex,\
PreCloseIndex,OpenIndex,HighIndex,LowIndex,\
CloseIndex\n");

		auto ret = fwrite(sz, 1, strlen(sz), fp);
		fflush(fp);

	}

	static void print(SzseIndex* pData, FILE* fp)
	{
		SzseIndex* data = pData;
		std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},{}\n",

pData->MsgType,
mystr2(pData->TradingPhaseCode),
pData->OrigTime,
mystr2(pData->SecurityID),

pData->NumTrades,
pData->TotalVolumeTrade,
pData->TotalValueTrade,
pData->LastIndex,

pData->PreCloseIndex,
pData->OpenIndex,
pData->HighIndex,
pData->LowIndex,

pData->CloseIndex);

		fwrite(str.c_str(), 1, str.size(), fp);
		fflush(fp);
	}
	
};

class MyStructSzDepth
{
public:
    MyStructSzDepth() {}

    static void printHeader(FILE* fp)
    {
        std::string strTitleBidPrice, strTitleBidQty, strTitleAskPrice, strTitleAskQty;
        for (int i = 1; i < 11; ++i)
        {
            strTitleBidPrice += fmt::format("BidPrice{},", i);
            strTitleBidQty += fmt::format("BidQty{},", i);
            strTitleAskPrice += fmt::format("AskPrice{},", i);
            strTitleAskQty += fmt::format("AskQty{},", i);
        }
        
        std::string title = fmt::format(
        //落地时间戳、ticker（股票代码）、DataTime（交易所时间戳）、后面加交易所传过来全量字段；
"\
MsgType,MDStreamID,TradingPhaseCode,SecurityID,\
OrigTime,ChannelNo,PrevClosePx,LastPrice,\
OpenPrice,HighPrice,LowPrice,UpperLimitPrice,\
LowerLimitPrice,AvgPrice,NumTrades,TotalVolumeTrade,\
TotalValueTrade,TotalBidQty,TotalAskQty,MaBidPrice,\
MaAskPrice,{}{}{}{}\
InstrQtyNum,BrkRefPrice,Iopv,PreIopv\n", strTitleBidPrice, strTitleBidQty, strTitleAskPrice, strTitleAskQty);

        auto ret = fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);

    }

    static void print(SzseDepth* pData, FILE* fp)
    {
        SzseDepth* data = pData;

        std::string strBidPrice10;
        std::string strBidQty10;
        std::string strAskPrice10;
        std::string strAskQty10;

        for (auto i = 0; i < 10; ++i)
        {
            strBidPrice10 += fmt::format("{},",pData->BidPrice[i]);
            strBidQty10 += fmt::format("{},", pData->BidQty[i]);
            strAskPrice10 += fmt::format("{},", pData->AskPrice[i]);
            strAskQty10 += fmt::format("{},", pData->AskQty[i]);
        }

        std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{}{}{}{}\
{},{},{},{}\n",

pData->MsgType,
mystr2(pData->MDStreamID),
mystr2(pData->TradingPhaseCode),
mystr2(pData->SecurityID),

pData->OrigTime,
pData->ChannelNo,
pData->PrevClosePx,
pData->LastPrice,

pData->OpenPrice,
pData->HighPrice,
pData->LowPrice,
pData->UpperLimitPrice,

pData->LowerLimitPrice,
pData->AvgPrice,
pData->NumTrades,
pData->TotalVolumeTrade,

pData->TotalValueTrade,
pData->TotalBidQty,
pData->TotalAskQty,
pData->MaBidPrice,

pData->MaAskPrice,
strBidPrice10,
strBidQty10,
strAskPrice10,

strAskQty10,
pData->InstrQtyNum,
pData->BrkRefPrice,
pData->Iopv,
pData->PreIopv);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructSzDepthFifty
{
public:
    MyStructSzDepthFifty() { }

	static void printHeader(FILE* fp)
	{
		string bidorder_title = "";
		string askorder_title = "";

		for (auto i = 1; i < 51; i++) {
			bidorder_title += ("bid_order" + to_string(i) + ",");
			askorder_title += ("ask_order" + to_string(i) + ",");
		}
        bidorder_title.pop_back();
        askorder_title.pop_back();

		std::string strTitle = fmt::format( "\
MsgType,MDStreamID,OrigTime,SecurityID,\
BidOrderPrice,BidOrderQty,AskOrderPrice,AskOrderQty,\
Rsv,BidNumOfOrders,AskNumOfOrders,BidNoOrders,\
AskNoOrders,{},{}\n",
		bidorder_title.c_str(),
		askorder_title.c_str()
	);

		auto ret = fwrite(strTitle.c_str(), 1, strTitle.size(), fp);
		fflush(fp);

	}


	static void print(SzseDepthFifty* pData, FILE* fp)
	{
		string bid_order = "";
		string ask_order = "";
		
		{
			
			for (auto i = 0; i < 50; i++) {
				if (i < pData->BidNoOrders)
					bid_order += to_string(pData->Orders[i]);
				else
					bid_order += "0";
				bid_order += ",";
			}

            int askStartIndex = pData->BidNoOrders;
            for (auto i = 0; i < 50; i++) {
                if (i < pData->AskNoOrders)
                    ask_order += to_string(pData->Orders[i + askStartIndex]);
                else
                    ask_order += "0";
                ask_order += ",";
            }

		}
		
		////

		{
			std::string str = fmt::format("\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{}{}\n",

				pData->MsgType,
                mystr2(pData->MDStreamID),
				pData->OrigTime,
				mystr2(pData->SecurityID),

                pData->BidOrderPrice,
                pData->BidOrderQty,
                pData->AskOrderPrice,
                pData->AskOrderQty,

				mystr2(pData->Rsv),
                pData->BidNumOfOrders,
                pData->AskNumOfOrders,
                pData->BidNoOrders,

                pData->AskNoOrders,
                bid_order.c_str(),
                ask_order.c_str()
			);

			fwrite(str.c_str(), 1, str.size(), fp);
			fflush(fp);
		}

	}
	
};
class MyStructSzTradeStatics
{
public:
	MyStructSzTradeStatics() { }

	static void printHeader(FILE* fp)
	{
		std::string str="MsgType,TradingPhaseCode,OrigTime,SecurityID,PrevClosePx,NumTrades,TotalVolumeTrade,TotalValueTrade,StockNum\n";
//
		fwrite(str.c_str(), 1, str.size(), fp);
		fflush(fp);

	}

	static void print(SzseTradeStatics* pData, FILE* fp)
	{
		//memset(sz, 0, sizeof(sz));
        //落地时间戳、ticker（股票代码）、DataTime（交易所时间戳）、后面加交易所传过来全量字段；
		std::string str = fmt::format("{},{},{},{},{},{},{},{},{}\n",
				
			pData->MsgType,
			mystr2(pData->TradingPhaseCode),
			pData->OrigTime,
			mystr2(pData->SecurityID),
			pData->PrevClosePx,
			pData->NumTrades,
			pData->TotalVolumeTrade,
			pData->TotalValueTrade,
			pData->StockNum
			);


		auto ret = fwrite(str.c_str(), 1, str.size(), fp);
		fflush(fp);
	}
};
class MyStructSzOrderQueue
{
public:
    MyStructSzOrderQueue() {}

    static void printHeader(FILE *fp)
    {
        string title = "\
MsgType,MsgVer,Side,Status,SeqNum,\
ApplSeqNum,SecurityID,TransactTime,Last_Price,Trade_Mark_Qty,\
TradeQty1,TradeQty2,TradeQty3,TradeQty4,TradeQty5,TradeQty6,TradeQty7,TradeQty8,TradeQty9,TradeQty10,\
TradePrice1,TradePrice2,TradePrice3,TradePrice4,TradePrice5,TradePrice6,TradePrice7,TradePrice8,TradePrice9,TradePrice10\
\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SzseOrderQueue *data, FILE *fp)
    {
        std::string strTradeQty, strTradePrice;
        for (int i = 0; i < 10; ++i)
        {
            strTradeQty += std::to_string(data->Trade_Qty[i]);
            strTradeQty += ",";

            strTradePrice += std::to_string(data->Trade_Price[i]);
            strTradePrice += ",";
        }
        std::string str = fmt::format("\
{},{},{},{},{},\
{},{},{},{},{},\
{}{}\n",

data->MsgType,
data->MsgVer,
data->Side,
data->Status,
data->SeqNum,

data->ApplSeqNum,
mystr2(data->SecurityID),
data->TransactTime,
data->Last_Price,
data->Trade_Mark_Qty,

strTradeQty,
strTradePrice);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructSzOrderQueueCage
{
public:
    MyStructSzOrderQueueCage() {}

    static void printHeader(FILE *fp)
    {
        string title = "\
MsgType,MsgVer,Side,Status,SeqNum,\
ApplSeqNum,SecurityID,TransactTime,Last_Price,Trade_Mark_Qty,\
TradeQty1,TradeQty2,TradeQty3,TradeQty4,TradeQty5,TradeQty6,TradeQty7,TradeQty8,TradeQty9,TradeQty10,\
TradePrice1,TradePrice2,TradePrice3,TradePrice4,TradePrice5,TradePrice6,TradePrice7,TradePrice8,TradePrice9,TradePrice10,\
Cage_Qty1,Cage_Qty2,Cage_Qty3,Cage_Qty4,Cage_Qty5,Cage_Qty6,Cage_Qty7,Cage_Qty8,Cage_Qty9,Cage_Qty10,\
Cage_Price1,Cage_Price2,Cage_Price3,Cage_Price4,Cage_Price5,Cage_Price6,Cage_Price7,Cage_Price8,Cage_Price9,Cage_Price10\
\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(struct SzseOrderQueueCage* data, FILE *fp)
    {
        std::string strTradeQty, strTradePrice, strCageQty, strCagePrice;
        for (int i = 0; i < 10; i++)
        {

            strTradeQty += std::to_string(data->Trade_Qty[i]);
            strTradeQty += ",";

            strTradePrice += std::to_string(data->Trade_Price[i]);
            strTradePrice += ",";

            strCageQty += std::to_string(data->Cage_Qty[i]);
            strCageQty += ",";

            strCagePrice += std::to_string(data->Cage_Price[i]);
            strCagePrice += ",";
        }
        std::string str = fmt::format("\
{},{},{},{},{},\
{},{},{},{},{},\
{}{}{}{}\n",
data->MsgType,
data->MsgVer,
data->Side,
data->Status,
data->SeqNum,

data->ApplSeqNum,
mystr2(data->SecurityID),
data->TransactTime,
data->Last_Price,
data->Trade_Mark_Qty,

strTradeQty,
strTradePrice,
strCageQty,
strCagePrice);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructSzOrderQueueErr
{
public:
    MyStructSzOrderQueueErr() {}

    static void printHeader(FILE *fp)
    {
        string title = "\
MsgType,Ver,ErrType,TransactTime,Channel,SeqNum,Rsv\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(struct SzszOrderQueueErr* data, FILE *fp)
    {
        std::string str = fmt::format("\
{},{},{},{},{},{}\n",
data->MsgType,
data->MsgVer,
data->ErrType,
data->TransactTime,
data->Chanel,

data->SeqNum
);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

class MyStructSzIOPV
{
public:
    MyStructSzIOPV() {}
    static void printHeader(FILE *fp)
    {
        string title = "MsgType,SecurityID,IOPV,Cstock_TradeTime,\
TradePrice,TransactTime\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SzseIOPV *data, FILE *fp)
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

class MyStructSzRealtimeIndex
{
public:
    MyStructSzRealtimeIndex() {}
    static void printHeader(FILE *fp)
    {
        string title = "MsgType,IndexID,LastIndex,TradeTime,\
NumTrades,TotalVolumeTrade,TotalValueTrade,PreCloseIndex,\
OpenIndex,HighIndex,LowIndex,CloseIndex\n";
        fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);
    }

    static void print(SzseRealtimeIndex *data, FILE *fp)
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

class LogRecorderSz
{
public:
    LogRecorderSz() 
    {
        fp_entrust_ =       fopen("sz_tbt_entrust.csv", "wt");
        fp_trade_ =         fopen("sz_tbt_trade.csv", "wt");

        fp_index_ =         fopen("sz_index.csv", "wt");
        fp_depth_ =         fopen("sz_depth.csv", "wt");
        fp_trade_statics_ = fopen("sz_trade_statics.csv", "wt");

        fp_depth_fifty_ =   fopen("sz_depth_fifty.csv", "wt");

        fp_orderbook_ =   fopen("sz_orderbook.csv", "wt");
        fp_orderbook_cage_ =   fopen("sz_orderbook_cage.csv", "wt");
        fp_orderbook_err_ =   fopen("sz_orderbook_err.csv", "wt");

        fp_iopv_ =   fopen("sz_iopv.csv", "wt");

        fp_realtime_index_ =   fopen("sz_realtime_index.csv", "wt");

        MyStructSzTbtEntrust::printHeader(fp_entrust_);
        MyStructSzTbtTrade::printHeader(fp_trade_);
        MyStructSzIndex::printHeader(fp_index_);
        MyStructSzDepth::printHeader(fp_depth_);
        MyStructSzTradeStatics::printHeader(fp_trade_statics_);
        MyStructSzDepthFifty::printHeader(fp_depth_fifty_);

        MyStructSzOrderQueue::printHeader(fp_orderbook_);
        MyStructSzOrderQueueCage::printHeader(fp_orderbook_cage_);
        MyStructSzOrderQueueErr::printHeader(fp_orderbook_err_);

        MyStructSzIOPV::printHeader(fp_iopv_);

        MyStructSzRealtimeIndex::printHeader(fp_realtime_index_);
    }

	~LogRecorderSz() 
    {
        fclose(fp_entrust_);
        fclose(fp_trade_);
        fclose(fp_index_);
        fclose(fp_depth_);
        fclose(fp_trade_statics_);
        fclose(fp_depth_fifty_);

        fclose(fp_orderbook_);
        fclose(fp_orderbook_cage_);
		fclose(fp_orderbook_err_);

		fclose(fp_iopv_);
		fclose(fp_realtime_index_);
    }

    void addSzseEntrustNode(SzseEntrust* data, unsigned long longm_local_time)
    {
        MyStructSzTbtEntrust::print((SzseEntrust*)data, fp_entrust_);
    }
    void addSzseTradeNode(SzseTrade* data, unsigned long longm_local_time)
    {
        MyStructSzTbtTrade::print((SzseTrade*)data, fp_trade_);
    }
	
    void addSzseIndexNode(SzseIndex* data, unsigned long longm_local_time)
    {
        MyStructSzIndex::print(data, fp_index_);
    }
    void addSzseDepthNode(SzseDepth* data, unsigned long longm_local_time)
    {
        MyStructSzDepth::print((SzseDepth*)data, fp_depth_);
    }

    void addSzseDepthFiftyNode(SzseDepthFifty* data, unsigned long longm_local_time)
    {
        MyStructSzDepthFifty::print((SzseDepthFifty*)data, fp_depth_fifty_);
    }

    void addSzseTradeStaticsNode(SzseTradeStatics* data, unsigned long longm_local_time)
    {
        MyStructSzTradeStatics::print(data, fp_trade_statics_);
    }

    void addSzseOrderbookQueueNode(SzseOrderQueue* data, unsigned long longm_local_time)
    {
        MyStructSzOrderQueue::print(data, fp_orderbook_);
    }
    void addSzseOrderbookQueueCageNode(SzseOrderQueueCage* data, unsigned long longm_local_time)
    {
        MyStructSzOrderQueueCage::print(data, fp_orderbook_cage_);
    }
    void addSzseOrderbookQueueErrNode(SzszOrderQueueErr* data, unsigned long longm_local_time)
    {
        MyStructSzOrderQueueErr::print(data, fp_orderbook_err_);
    }
    void addSzseIOPVNode(SzseIOPV* data, unsigned long longm_local_time)
    {
        MyStructSzIOPV::print(data, fp_iopv_);
    }
    void addSzseRealtimeIndexNode(SzseRealtimeIndex* data, unsigned long longm_local_time)
    {
        MyStructSzRealtimeIndex::print(data, fp_realtime_index_);
    }


private:
    FILE* fp_entrust_;
    FILE* fp_trade_;

    FILE* fp_index_;
    FILE* fp_depth_;
    FILE* fp_depth_fifty_;
    FILE* fp_trade_statics_;

    FILE* fp_orderbook_;
    FILE* fp_orderbook_cage_;
    FILE* fp_orderbook_err_;

    FILE* fp_iopv_;
    FILE* fp_realtime_index_;

};

