#pragma once
#include "BseExanicStruct.h"
#include "fmt/format.h"
#include <stdio.h>


using namespace  istone::base;
using namespace std;
#pragma pack(push, 1)

class MyStructBjIndex
{
public:
    MyStructBjIndex() {}

	static void printHeader(FILE* fp)
	{
		char sz[1024] = { 0 };
		sprintf(sz, "MsgType,\
OrigTime,SecurityID,TradingPhaseCode,NumTrades,\
TotalVolumeTrade,TotalValueTrade,LastIndex,PreCloseIndex,\
OpenIndex,HighIndex,LowIndex,CloseIndex\n");

		auto ret = fwrite(sz, 1, strlen(sz), fp);
		fflush(fp);

	}

	static void print(BseIndex* pData, FILE* fp)
	{
		BseIndex* data = pData;
		std::string str = fmt::format("{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{}\n",

pData->MsgType,

pData->OrigTime,
mystr2(pData->SecurityID),
mystr2(pData->TradingPhaseCode),
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

class MyStructBjDepth
{
public:
    MyStructBjDepth() {}

    static void printHeader(FILE* fp)
    {

        
        std::string title = fmt::format(
        //落地时间戳、ticker（股票代码）、DataTime（交易所时间戳）、后面加交易所传过来全量字段；
"\
MsgType,\
OrigTime,ChannelNo,MDStreamID,SecurityID,\
TradingPhaseCode,PrevClosePx,NumTrades,TotalVolumeTrade,\
TotalValueTrade,UpperLimitPrice,LowerLimitPrice,LastPrice,\
OpenPrice,ClosePrice,HighPrice,LowPrice,\
AvgPrice,TotalBidQty,TotalAskQty,MaBidPrice,\
MaAskPrice,\
BidPrice1,BidPrice2,BidPrice3,BidPrice4,BidPrice5,BidPrice6,BidPrice7,BidPrice8,BidPrice9,BidPrice10,\
BidQty1,BidQty2,BidQty3,BidQty4,BidQty5,BidQty6,BidQty7,BidQty8,BidQty9,BidQty10,\
AskPrice1,AskPrice2,AskPrice3,AskPrice4,AskPrice5,AskPrice6,AskPrice7,AskPrice8,AskPrice9,AskPrice10,\
AskQty1,AskQty2,AskQty3,AskQty4,AskQty5,AskQty6,AskQty7,AskQty8,AskQty9,AskQty10,\
InstrQtyNum\n");

        auto ret = fwrite(title.c_str(), 1, title.size(), fp);
        fflush(fp);

    }

    static void print(BseDepth* pData, FILE* fp)
    {
        BseDepth* data = pData;

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

        std::string str = fmt::format("{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},{},{},{},\
{},\
{}{}{}{}\
{}\n",

pData->MsgType,

pData->OrigTime,
pData->ChannelNo,
mystr2(pData->MDStreamID),
mystr2(pData->SecurityID),

mystr2(pData->TradingPhaseCode),
pData->PrevClosePx,
pData->NumTrades,
pData->TotalVolumeTrade,

pData->TotalValueTrade,
pData->UpperLimitPrice,
pData->LowerLimitPrice,
pData->LastPrice,

pData->OpenPrice,
pData->ClosePrice,
pData->HighPrice,
pData->LowPrice,

pData->AvgPrice,
pData->TotalBidQty,
pData->TotalAskQty,
pData->MaBidPrice,

pData->MaAskPrice,

strBidPrice10,
strBidQty10,
strAskPrice10,
strAskQty10,

pData->InstrQtyNum
);

        fwrite(str.c_str(), 1, str.size(), fp);
        fflush(fp);
    }
};

#pragma pack(pop)

class LogRecorderBj
{
public:
    LogRecorderBj()
    {
        fp_index_ =         fopen("bj_index.csv", "wt");
        fp_depth_ =         fopen("bj_depth.csv", "wt");

        MyStructBjIndex::printHeader(fp_index_);
        MyStructBjDepth::printHeader(fp_depth_);
    }

	~LogRecorderBj()
    {
        fclose(fp_index_);
        fclose(fp_depth_);
    }

	
    void addBjIndexNode(BseIndex* data, unsigned long longm_local_time)
    {
        MyStructBjIndex::print(data, fp_index_);
    }
    void addBjDepthNode(BseDepth* data, unsigned long longm_local_time)
    {
        MyStructBjDepth::print(data, fp_depth_);
    }

private:

    FILE* fp_index_;
    FILE* fp_depth_;

};

