#pragma once
/** 修改记录:
    20231211 "初始版本"
    
*/

#include <stdint.h>

namespace istone
{
    namespace base
    {
        enum bseMsgType
        {
            bseIndexType = (char)'J',           //指数行情 
            bseDepthType = (char)'K',           //快照行情 
        };
#pragma pack(push, 1)

        /*********************************************************************
           指数快照行情
        *********************************************************************/
        struct BseIndex
        {
            char        MsgType;			          	//消息头(“J”)
            uint64_t    OrigTime; 			        	//数据生成时间
            char        SecurityID[8];		      		//证券代码
            char        TradingPhaseCode[8];    		//产品所处的交易阶段的代码
            uint64_t    NumTrades; 			        	//成交笔数
            uint64_t    TotalVolumeTrade; 	    		//成交总量，3位小数。
            uint64_t    TotalValueTrade; 	      		//成交总金额，3位小数。
            uint64_t	LastIndex; 		          		//当前指数,5位小数。
            uint64_t 	PreCloseIndex;		      		//昨日收盘指数,5位小数。
            uint64_t    OpenIndex;			        	//开盘指数,5位小数。
            uint64_t    HighIndex; 		          		//最高指数,5位小数。
            uint64_t    LowIndex; 			        	//最低指数,5位小数。
            uint64_t    CloseIndex;		          		//收盘指数,5位小数。
        };
        /*********************************************************************
            竞价（非指数）快照行情
        *********************************************************************/
        struct BseDepth
        {
            char        MsgType; 			          	//消息头(“K”)
            uint64_t    OrigTime; 				      	//数据生成时间
            uint16_t  	ChannelNo; 	    				//频道代码
            char    	MDStreamID[3];					//行情类别
            char        SecurityID[8];			    	//证券代码
            char        TradingPhaseCode[8]; 	  		//产品所处的交易阶段的代码
            uint32_t    PrevClosePx; 			      	//昨收价，5位小数。
            uint64_t    NumTrades;				      	//成交笔数 
            uint64_t    TotalVolumeTrade;		    	//成交总量，3位小数。
            uint64_t    TotalValueTrade;		    	//成交总金额，3位小数。
            uint64_t    UpperLimitPrice; 				//涨停价，5位小数。
            uint64_t    LowerLimitPrice; 				//跌停价，5位小数。
            uint32_t    LastPrice; 						//最近成交价（行情:2），5位小数。
            uint32_t    OpenPrice; 						//开盘价（行情：4），5位小数。
            uint32_t    ClosePrice; 					//收盘价（行情：5），5位小数。
            uint32_t    HighPrice; 						//最高价（行情：7），5位小数。
            uint32_t    LowPrice;  						//最低价（行情：8），5位小数。
            uint32_t    AvgPrice; 						//加权平均价（行情：9），5位小数。
            uint64_t    TotalBidQty; 					//委托买入总量（行情：x3=买入汇总（总量及加权平均价）），3位小数。
            uint64_t    TotalAskQty; 					//委托卖出总量（行情：x4=卖出汇总（总量及加权平均价）），3位小数。
            uint32_t    MaBidPrice; 					//加权委托买入价格（行情：x3=买入汇总（总量及加权平均价）），5位小数。
            uint32_t    MaAskPrice; 					//加权委托卖出价格（行情：x4=卖出汇总（总量及加权平均价）），5位小数。
            uint32_t    BidPrice[10];          			//10档买价（行情：0），5位小数。
            uint64_t    BidQty[10];						//10档买量（行情：0），3位小数。
            uint32_t    AskPrice[10];  					//10档卖价（行情：1），5位小数。
            uint64_t    AskQty[10];   					//10档卖量（行情：1），3位小数。
            uint64_t    InstrQtyNum;				    //合约持仓量,期权有效，3位小数。
        };
        

#pragma pack(pop)
    }
}
