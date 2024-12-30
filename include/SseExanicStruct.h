#pragma once
/** 修改记录:
    20211015 "初始版本"
    20211201 "统一结构体名称;删除不必要的注释"
    20220623 "增加订单簿结构体;注释补充更新"
	20220818 "更新订单簿结构体;注释补充更新"
	20230404 "更新订单簿结构体;价格字段修改"
    20230810 "增加IOPV结构体"
    20231010 "增加实时指数结构体"
*/

#include <stdint.h>

#define SSE_PRICE_DECIMAL 1000.0
#define SSE_MONEY_DECIMAL 100000.0
#define SSE_INDEX_MONEY_DECIMAL 10.0
#define SSE_QTY_DECIMAL 1000.0
#define SSE_OPTION_DECIMAL 100000.0

namespace istone
{
    namespace base
    {
        static double transformSsePrice(uint32_t price)
        {
            return (double)(price / SSE_PRICE_DECIMAL);
        }

        static double transformSseMoney(uint64_t money)
        {
            return (double)(money / SSE_MONEY_DECIMAL);
        }

        static double transformSseIndexMoney(uint64_t money)
        {
            return (double)(money / SSE_INDEX_MONEY_DECIMAL);
        }

        static int64_t transformSseQty(uint64_t qty)
        {
            return (int64_t)(qty / SSE_QTY_DECIMAL);
        }

        static double transformSseOption(uint64_t money)
        {
            return (double)(money / SSE_OPTION_DECIMAL);
        }
        enum DataType
        {
            HAS_PRICE,//全部发送
            NO_PRICE //硬件不发送十档和委托明细，补0
        };

        enum sseMsgType
        {
            sseEntrustType = (char)'a',         //逐笔委托 
            sseTradeType = (char)'b',           //逐笔成交 
            sseIndexType = (char)'c',           //指数行情 
            sseDepthType0 = (char)'d',          //快照行情 
            sseDepthType1 = (char)'e',          //快照行情（不含10档）
            sseDepthFiftyType = (char)'f',      //50笔委托 
            sseOptionType = (char)'g',          //期权快照
            sseOrderQueueType = (char)'p',      //基础订单簿
            SseOrderQueueErrType = (char)'x',   //订单簿错误信息包文 
            sseIOPVType = (char)'i',            //IOPV
            sseRealtimeIndex = (char)'z',       //实时指数
        };
#pragma pack(push, 1)

        /*********************************************************************
            UA3113 CategoryID=6  指数行情数据
        *********************************************************************/
        struct SseIndex
        {
            char		MsgType;			     	// 消息头（c）
            uint32_t 	UpdateTime;			   		// 行情时间
            char		SecurityID[8];		 		// 证券代码
            uint64_t	PreCloseIndex;		 		// 前收盘指数，5位小数。
            uint64_t	OpenIndex;			   		// 今开盘指数，5位小数。
            uint64_t	Turnover;			     	// 参与计算相应指数的成交金额（元），1位小数。
            uint64_t	HighIndex;			   		// 最高指数，5位小数。
            uint64_t	LowIndex;			     	// 最低指数，5位小数。
            uint64_t	LastIndex;			   		// 最新指数，5位小数。
            uint32_t	TradeTime;			   		// 成交时间
            uint64_t	TotalVolumeTrade;	 		// 参与计算相应指数的交易数量（手），5位小数。
            uint64_t	CloseIndex;			   		// 今收盘指数（大于0为有效值），5位小数。
            char	    Rsv[3];				     	// 保留字段
        };
        /*********************************************************************
            UA3202 CategoryID=6  竞价行情快照数据（非债券）
			UA3802 CategoryID=6  竞价行情快照数据（债券）
        *********************************************************************/
        struct SseDepth
        {
            char		MsgType;				   	// 消息头（d:含买卖10档 e:无买卖10档）股票 权证 基金 债券					
            uint32_t	UpdateTime;				  	// 最新订单时间
            char		SecurityID[8];				// 证券代码，6字节有效
            uint32_t	PreClosePx;					// 昨收盘价，3位小数。
            uint32_t	OpenPx;						// 开盘价，3位小数。
            uint32_t	HighPx;						// 最高价，3位小数。
            uint32_t	LowPx;						// 最低价，3位小数。
            uint32_t	LastPx;						// 现价，3位小数。
            uint32_t	ClosePx;					// 今日收盘价格，3位小数。
            char		InstruStatus[6];			// 当前品种交易状态
            char		TradingPhaseCode[5];		// 当前产品状态
            uint32_t    UpperLimitPrice; 			// 涨停价（行情：xe），3位小数，取自静态文件。
            uint32_t    LowerLimitPrice;			// 跌停价（行情：xf），3位小数，取自静态文件。
            uint32_t	NumTrades;					// 成交笔数
            uint64_t	TotalVolumeTrade;			// 成交总量，3位小数。  
            uint64_t	TotalValueTrade;			// 成交总金额 ，5位小数。  
            uint64_t	TotalBidQty;				// 委托买入总量 ，3位小数。  
            uint32_t	WeightedAvgBidPx;			// 加权委买价格 ，债券共用，3位小数。
            uint64_t	TotalOfferQty;				// 委托卖出总量，3位小数。
            uint32_t	WeightedAvgOfferPx;			// 加权委卖价格，债券共用，3位小数。
            uint32_t	WeightedAvgPx;				// 债券加权平均价格,债券有效，非债券为0，3位小数。
            uint32_t	TotalBidNumber;				// 买入总笔数。
            uint32_t	TotalOfferNumber;			// 卖出总笔数。

            //------------全量信息且买卖10档价不存在时，不发送--------------
            uint32_t	BidPrice[10];				// 10档买价，3位小数。
            uint64_t	BidQty[10];					// 10档买量，3位小数。
            uint32_t	AskPrice[10];				// 10档卖价，3位小数。
            uint64_t	AskQty[10];					// 10档卖量，3位小数。

            
        };
        /*********************************************************************
            UA3202 CategoryID=6  竞价行情快照委托队列数据
			UA3802 CategoryID=6  债券行情快照委托队列数据
        *********************************************************************/
        struct SseDepthFifty
        {
            char        MsgType;			    	//消息头(“f”)
            uint32_t  	UpdateTime; 		  		//最新订单时间
            char  		SecurityID[8];				//证券代码
            uint32_t    BidOrderPrice;    			//买一档委托价格，3位小数。
            uint64_t    BidOrderQty;   				//买一档委托量，3位小数。
            uint32_t    AskOrderPrice;    			//卖一档委托价格，3位小数。
            uint64_t    AskOrderQty;   				//卖一档委托量，3位小数。
            char		Rsv;				        
            uint32_t    BidNumOfOrders; 			//买一档价位总委托笔数（行情：0）
            uint32_t    AskNumOfOrders; 			//卖一档价位总委托笔数（行情：1）
            uint8_t 	BidNoOrders;  				//买一档价位揭示委托笔数（行情：0）
            uint8_t 	AskNoOrders;    			//卖一档价位揭示委托笔数（行情：1）
            uint32_t    Orders[100];    			//买一档/卖一档50笔委托（行情：0）
        };
        /*********************************************************************
            UA9002 CategoryID=30  竞价行情期权快照数据 MsgType=W
        *********************************************************************/
        struct SseOption
        {
            char  		MsgType;                //消息头（g）
            char		SecurityID[8];          //证券代码
            uint64_t	LastPx;                 //成交价，5位小数。
            uint64_t	TradeQty;               //成交量
            char		TradeTime[8];           //成交时间
            char		TradingPhaseCode[4];	//当前产品状态
            char		Rsv[3];				    //保留字段
            uint32_t	NumTrades;              //成交笔数
            uint64_t	TotalVolumeTrade;       //成交总量
            uint64_t  	TotalValueTrade;		//总成交金额，5位小数。
            uint64_t  	PreClosePx;             //昨收盘价，5位小数。
            uint64_t  	PreSetPx;               //昨结算价，5位小数。
            uint64_t	TotalLongPosition;      //未平仓合约数量
            uint64_t 	OpenPx;                 //今开盘价，5位小数。
            uint64_t  	ClosePx;                //今收盘价，5位小数。
            uint64_t  	SetPx;                  //今结算价，5位小数。
            uint64_t  	HighPx;                 //当日最高成交价，5位小数。
            uint64_t  	LowPx;                  //当日最低成交价，5位小数。
            uint64_t	BidPrice[5];            //买五档价格，5位小数。
            uint64_t	BidQty[5];              //买五档数量
            uint64_t	AskPrice[5];            //卖五档价格，5位小数。
            uint64_t	AskQty[5];              //卖五档数量
            uint64_t  	RefrencePrice;          //动态参考价格，5位小数。
            uint64_t  	RefrenceQty;            //动态参考量
            uint32_t    UpdateDate;             //行情更新时间 yyyy mm dd
            uint32_t    UpdateTime;             //行情更新时间 
        };

        /*********************************************************************
            UA5801 CategoryID=58 竞价逐笔委托数据
			UA5803 CategoryID=9 竞价逐笔委托合并数据/产品状态
            UA3901 CategoryID=39 债券逐笔委托数据/产品状态
        *********************************************************************/
        struct  SseEntrust
        {
            char        MsgType;        //消息头（a）			
            char        OrderType;      //订单类型，A-新增委托订单，D-删除委托订单，S-产品状态订单。
            char        OrderBSFlag;    //买卖标志 OrderType是A或D时，OrderBSFlag为B-买单 S-卖单,OrderType是S时无效。	
            char        TickBSFlag;     //产品状态 OrderType是A或D时无效。OrderType是S时，TickBSFlag为A-ADD S-START O-OCALL T-TRADE S-SUSP C-CLOSE Q-CCALL。
            uint32_t    OrderIndex;     //序号。对于竞价逐笔委托数据，从1开始按Channel连续。对于债券和竞价合并数据，与'b'中债券和竞价合并数据的TradeIndex合并后按Channel连续。
            uint32_t    OrderChannel;   //通道号
            char        SecurityID[8];  //证券代码
            uint32_t    OrderTime;      //委托时间
            uint64_t    OrderNO;        //原始订单号
            uint32_t    OrderPrice;     //委托价格，3位小数
            uint64_t    Balance;        //剩余委托量，3位小数
            uint64_t    BizIndex;       //序号。对于竞价逐笔委托数据，与竞价逐笔成交数据合并后按Channel连续。对于债券无效。对于竞价合并数据，与‘b’中竞价合并数据的BizIndex合并后按Channel连续。
            char	    Rsv[12];		//保留字段
        };

        /*********************************************************************
            UA3201 CategoryID=7  竞价逐笔成交数据
            UA5803 CategoryID=9  竞价逐笔成交合并数据
            UA3901 CategoryID=39 债券逐笔成交数据
        *********************************************************************/
        struct  SseTrade				//逐笔成交
        {
            char		MsgType;	  	// 消息头（b）
            uint32_t	TradeIndex;		// 序号，对于竞价逐笔成交数据，从1开始按Channel连续。对于债券和竞价合并数据，与'a'中债券和竞价合并数据的OrderIndex合并后按Channel连续。
            uint32_t	TradeChannel;	// 通道号
            char		SecurityID[8];	// 证券代码
            uint32_t	TradeTime;		// 成交时间
            uint32_t	TradePrice;		// 成交价格，3位小数。
            uint32_t	TradeQty;		// 成交数量，3位小数。
            uint64_t	TradeMoney;		// 成交金额，5位小数。
            uint64_t	TradeBuyNo;		// 买方订单号
            uint64_t	TradeSellNo;	// 卖方订单号
            uint64_t  	BizIndex;       // 序号，对于竞价逐笔成交数据，与竞价逐笔委托数据合并后按Channel连续。对于债券无效。对于竞价合并数据，与‘a’中竞价合并数据的BizIndex合并后按Channel连续。
            char		TradeBSFlag;	// 内外盘标志
            char		Rsv[2];			// 保留字段
        };

        /*********************************************************************
          订单簿
        *********************************************************************/
        struct SseOrderQueue            //基础订单簿
        {
            char 		MsgType;            //消息类型(p)
            uint8_t 	MsgVer;             //版本号
            char 		Side;               //买卖方向 “0”=买 “1”=卖
            uint8_t 	Channel;            //通道号
            uint32_t 	BizIndex;           //业务序列号
            uint32_t 	Applseqnum;         //订单簿推送消息序号
            char 		SecurityID[6];      //证券代码
            char 		Reliability;        //数据可靠性 “1”=正常 “ 2”=存疑
            char 		Rsv;                //保留
            uint32_t 	TransactTime;       //时间 hh mm ss sss
            uint64_t 	Trade_Qty[10];      // 1档-10档（量），3位小数。
            uint32_t 	Trade_Price[10];	// 1档-10档（价格），3位小数。
            uint32_t    TradePrice;         //最新价，3位小数。
        };

        struct SseOrderQueueErr             //订单簿错误信息包文
        {
            char 		MsgType;            //消息类型(x)
            uint8_t 	MsgVer;             //版本号
            char 		ErrType;            //错误类型 “a”= 通道逐笔丢失 
            uint8_t 	Channel;            //错误通道
            uint32_t 	TransactTime;       //时间 hh mm ss sss
            uint64_t 	BizIndex;           //错误消息序号
        };

        struct SseIOPV                      //IOPV
        {
            char 		MsgType;            //消息类型(i)
            char 		SecurityID[8];      //证券代码（ETF二级市场的交易代码）
            uint64_t 	IOPV;               //实时净值（基金份额参考净值），4位小数
            uint32_t    Cstock_TradeTime;   //成分股交易时间 hh mm ss ss
            uint32_t 	TradePrice;         //最新价（ETF的最新成交价格，没有成交时为0），3位小数
            uint32_t 	TransactTime;       //时间 （ETF的最新成交时间，没有成交时为0）
            char        Rsv[35];
        };

        struct SseRealtimeIndex             //实时指数
        {
            char		MsgType;			//消息类型(z）
            char		IndexID[7];		    //指数代码
            uint64_t	LastIndex;          //实时计算的最新指数，5位小数
            uint64_t	TradeTime;			//成分股的逐笔成交时间
            uint64_t	NumTrades;          //指数计算的总成交笔数
            uint64_t	TotalVolumeTrade;	//指数计算的成交总量，5位小数
            uint64_t	TotalValueTrade;	//指数计算的成交总金额，1位小数
            uint64_t	PreCloseIndex;		//前收盘指数，5位小数
            uint64_t	OpenIndex;			//今开盘指数，5位小数
            uint64_t	HighIndex;			//最高指数，5位小数
            uint64_t	LowIndex;			//最低指数，5位小数
            uint64_t	CloseIndex;			//今收盘指数，5位小数
            uint64_t 	UpdateTime;			//本地指数行情计算时间 hh mm ss sss
        };

#pragma pack(pop)
    }
}
