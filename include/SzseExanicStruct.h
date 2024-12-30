#pragma once
/** 修改记录:
    20211015 "初始版本"
	20211201 "统一结构体名称;删除不必要的注释"
    20220623 "增加订单簿结构体"
	20220711 "SzszOrderQueueErr"添加 Rsv字段；注释补充更新
    20230810 "增加IOPV结构体"
    20231010 "增加实时指数结构体"
*/

#include <stdint.h>

#define SZSE_PRICE_DECIMAL_4 10000.0
#define SZSE_PRICE_DECIMAL_6 1000000.0
#define SZSE_QTY_DECIMAL 100.0
#define SZSE_MONEY_DECIMAL 10000.0

namespace istone
{
	namespace base
	{
		static std::string Szse_MD_SpotType    = "010";
		static std::string Szse_MD_RepoType    = "020";
		static std::string Szse_MD_BondType    = "030";
		static std::string Szse_MD_OptionType  = "040";
		static std::string Szse_MD_IndexType   = "900";
		static std::string Szse_HK_MD_SpotType = "630";

		static std::string Szse_TBT_SpotType   = "011";
		static std::string Szse_TBT_RepoType   = "021";
		static std::string Szse_TBT_OptionType = "041";

		static double transformSzseIndex_Nx_6(uint64_t price)
		{
			return (double)(price / SZSE_PRICE_DECIMAL_6);
		}

		static double transformSzse_Nx_6(uint32_t price)
		{
			return (double)(price / SZSE_PRICE_DECIMAL_6);
		}

		static double transformSzse_Nx_4(uint64_t price)
		{
			return (double)(price / SZSE_PRICE_DECIMAL_4);
		}

		static double transformSzsePrice(uint64_t price)
		{
			return (double)(price/ SZSE_PRICE_DECIMAL_4);
		}

		static uint64_t transformSzseQty(uint64_t qty)
		{
			return (uint64_t)(qty / SZSE_QTY_DECIMAL);
		}

		enum szseMsgType
		{
			szseTradeStaticsType = 'A',			//成交量统计行情
			szseIndexType = 'B',             	//指数行情
			szseEntrustType = 'C', 			    //逐笔委托
			szseTradeType = 'D',   			    //逐笔成交
			szseDepthOrOptionType = 'E',     	//基础行情快照(含期权)
			szseDepthFiftyType = 'F',        	//50笔委托
      		szseOrderQueueType = 'P',	        //基础订单簿
      		szseOrderQueueCageType = 'Q',	    //带笼子内价格订单簿(仅创业板有效)  
      		szseOrderQueueErrType = 'X',    	//订单簿错误信息包文(X) 
      		szseIOPVType = 'I',    	            //IOPV 
            szseRealtimeIndex = 'Z',            //实时指数
		};
#pragma pack(push, 1)


		/*********************************************************************
		  309111  910 成交量统计指标快照行情
		*********************************************************************/

		struct SzseTradeStatics
		{
      		char        MsgType; 			          	//消息头(“A”)
			char        TradingPhaseCode[3]; 	  		//市场状态
			uint64_t    OrigTime; 				      	//数据生成时间
      		char        SecurityID[8];			    	//证券代码
			uint64_t    PrevClosePx; 			      	//昨收价，4位小数。
			uint64_t    NumTrades;				      	//成交笔数 
			uint64_t    TotalVolumeTrade;		    	//成交总量，2位小数。
			uint64_t    TotalValueTrade;		    	//成交总金额，4位小数。
			uint32_t    StockNum;				        //统计量指标样本个数
		};

		/*********************************************************************
			309011  900 指数快照行情
		  309011  920 国证指数快照行情
		*********************************************************************/
		struct SzseIndex
		{
			char        MsgType;			          	//消息头(“B”)
			char        TradingPhaseCode[3];    		//市场状态
			uint64_t    OrigTime; 			        	//数据生成时间
      		char        SecurityID[8];		      		//证券代码
			uint64_t    NumTrades; 			        	//成交笔数
			uint64_t    TotalVolumeTrade; 	    		//成交总量，2位小数。
			uint64_t    TotalValueTrade; 	      		//成交总金额，4位小数。
      		uint64_t	LastIndex; 		          		//当前指数,6位小数。
      		uint64_t 	PreCloseIndex;		      		//昨日收盘指数,6位小数。
      		uint64_t    OpenIndex;			        	//开盘指数,6位小数。
      		uint64_t    HighIndex; 		          		//最高指数,6位小数。
			uint64_t    LowIndex; 			        	//最低指数,6位小数。
			uint64_t    CloseIndex;		          		//收盘指数,6位小数。
		};

		/*********************************************************************
			300111  010 现货（股票，基金等）集中竞价交易快照行情
					    040 期权集中竞价交易快照行情
			300211	020 债券通用质押式回购匹配交易快照行情
					    030 债券分销快照行情
					    410 债券现券交易快照行情
			300611	060 以收盘价交易的盘后定价大宗交易快照行情
					    061 以成交量加权平均价交易的盘后定价大宗交易快照行情
			303711	370 盘后定价交易快照行情
			306311	630 港股实时行情
		*********************************************************************/
		struct SzseDepth
		{
			char     	MsgType;				    //消息头(“E”)
			char    	MDStreamID[3];				//行情类别
			char  	    TradingPhaseCode[2];		//市场状态
			char     	SecurityID[8];				//证券代码
			uint64_t  	OrigTime; 				  	//数据生成时间
			uint16_t  	ChannelNo; 	    			//频道代码
			uint32_t    PrevClosePx; 			  	//昨收价，4位小数。
			uint32_t    LastPrice; 			    	//最近价，6位小数。
			uint32_t    OpenPrice; 			    	//开盘价，6位小数。
			uint32_t    HighPrice; 			    	//最高价（行情：7），6位小数。
			uint32_t    LowPrice;  			    	//最低价（行情：8），6位小数。
			uint64_t    UpperLimitPrice; 			//涨停价（行情：xe），6位小数。
			uint64_t    LowerLimitPrice; 			//跌停价（行情：xf），6位小数。
			uint32_t    AvgPrice; 				 	//加权平均价（行情：9）为现货时-空，为质押式回购时-行情。
			                                		//字段表示质押式回购的实时成交量加权平均利率及债券现券交易成交量加权平均价。
			                                		//质押式回购的该条目仅限于质押式回购及债券现券交易产品发布。
												    //实时成交量加权平均利率，精确到 5 位小数。
			uint64_t    NumTrades; 				  	//成交笔数 
			uint64_t    TotalVolumeTrade; 			//成交总量，2位小数。
			uint64_t    TotalValueTrade; 			//成交总金额，4位小数。
      		uint64_t    TotalBidQty; 	      		//委托买入总量（行情：x3=买入汇总（总量及加权平均价）），2位小数。
      		uint64_t    TotalAskQty; 	      		//委托卖出总量（行情：x4=卖出汇总（总量及加权平均价）），2位小数。
      		uint64_t    MaBidPrice; 	      		//加权委托买入价格（行情：x3=买入汇总（总量及加权平均价）），6位小数。
      		uint64_t    MaAskPrice; 	      		//加权委托卖出价格（行情：x4=卖出汇总（总量及加权平均价）），6位小数。
      		uint32_t    BidPrice[10];       		//10档买价（行情：0），6位小数。
      		uint64_t    BidQty[10];		      		//10档买量（行情：0），2位小数。
      		uint32_t    AskPrice[10];  				//10档卖价（行情：1），6位小数。
      		uint64_t    AskQty[10];   				//10档卖量（行情：1），2位小数。
      		//快照期权区分字段
      		uint64_t    InstrQtyNum;        		//合约持仓量,期权有效，2位小数。
      		uint64_t    BrkRefPrice;        		//参考价,期权有效，6位小数。
			                                		//如果处于冷静期，则表示冷靜期內的参考价格。
												    //如果处于收盘集合竞价时段，则表示收盘集合竞价时段参考价，
												    //如果处于开盘集合竞价时段，则表示开盘集合竞价时段参考价。
      		uint32_t    Iopv; 					    //基金实时参考净值，包括ETF（行情：x8=基金实时参考净值（包括 ETF的 IOPV）），6位小数,期权无效
      		uint32_t    PreIopv;				    //基金T-1日净值（行情：x7=基金 T-1 日净值），6位小数,期权无效。
		};
		/*********************************************************************
			竞价行情快照委托队列数据
		*********************************************************************/
		struct SzseDepthFifty
		{
			char        MsgType;			    	//消息头(“F”)
			char     	MDStreamID[3];				//行情类别
			uint64_t  	OrigTime; 			  		//数据生成时间
			char    	SecurityID[8];				//证券代码
      		uint32_t    BidOrderPrice;    			//买一档委托价格，6位小数。
      		uint64_t    BidOrderQty;   				//买一档委托量，2位小数。
      		uint32_t    AskOrderPrice;    			//卖一档委托价格，6位小数。
      		uint64_t    AskOrderQty;   				//卖一档委托量，2位小数。
			char		Rsv[2];				    	//
      		uint32_t    BidNumOfOrders; 			//买一档价位总委托笔数（行情：0） 
      		uint32_t    AskNumOfOrders; 			//卖一档价位总委托笔数（行情：1） 
      		uint8_t 	BidNoOrders;  				//买一档价位揭示委托笔数（行情：0） 
      		uint8_t 	AskNoOrders;    			//卖一档价位揭示委托笔数（行情：1） 
      		uint32_t    Orders[100];    			//买/卖一档50笔委托（行情：0） 
		};

		/*********************************************************************
			300192  011 现货（股票，基金，债券等）集中竞价交易逐笔行情
			        041 期权集中竞价交易逐笔行情
			300592  051 协议交易逐笔意向行情
			        052 协议交易逐笔定价行情
			300792  071 转融通证券出借逐笔行情
			300292  021 债券通用质押式回购匹配成交逐笔行情
			        411 债券现券交易匹配成交逐笔行情
			300392  413 债券现券交易点击成交逐笔行情
			        415 债券现券交易意向申报逐笔行情
			300492  416 债券现券交易竞买成交逐笔行情
			300392  417 债券现券交易匹配成交大额逐笔行情
		***********************************************************************/
		struct SzseEntrust
		{
			char      	MsgType;		    	//消息头(“C”)
			char    	MDStreamID[3];			//行情类别
			uint64_t   	Applseqnum; 	  		//消息记录号从 1 开始计数
			char   		SecurityID[8];			//证券代码
			uint16_t  	ChannelNo; 	    		//频道代码
			char    	Side;			      	//买卖方向
			char   		OrdType;		    	//订单类别
			uint32_t 	Price;  		    	//委托价格,4位小数
			uint32_t   	OrderQty; 		  		//委托数量,2位小数
			uint64_t   	TransactTime;	  		//委托时间
			char    	Rsv[24];        		//硬件保留字段
		};

		/*********************************************************************
		300191  011 现货（股票，基金，债券等）集中竞价交易逐笔行情
            041 期权集中竞价交易逐笔行情
    300591  051 协议交易逐笔意向行情
            052 协议交易逐笔定价行情
		300791	071 转融通证券出借逐笔行情
		300291	021 债券通用质押式回购匹配成交逐笔行情
				    411 债券现券交易匹配成交逐笔行情
		300391  412 债券现券交易协商成交逐笔行情
				    413 债券现券交易点击成交逐笔行情
				    414 债券现券交易询价成交逐笔行情
		300491	416 债券现券交易竞买成交逐笔行情
		300391  417 债券现券交易匹配成交大额逐笔行情
		***********************************************************************/
		struct SzseTrade
		{
			char     	MsgType;			    //消息头(“D”)
			char    	MDStreamID[3];			//行情类别
			uint64_t   	Applseqnum; 		  	//消息记录号从 1 开始计数
			uint64_t   	BidApplSeqNum;			//买方委托索引从 1 开始计数，0 表示无对应委托
			uint64_t   	OfferApplSeqNum;  		//卖方委托索引从 1 开始计数，0 表示无对应委托
			char    	SecurityID[8];			//证券代码
			uint16_t  	ChannelNo ; 		  	//频道代码
			char    	ExecType; 			  	//成交类别4=撤销F=成交
			char 		Rsv0;
			uint32_t	TradePrice;		    	//成交价格，4位小数。
			uint32_t   	TradeQty;			    //成交数量，2位小数。
			uint64_t   	TransactTime;		  	//成交时间
			char    	Rsv1[8];          		//硬件保留字段
		};

        /*********************************************************************
            订单簿
        *********************************************************************/

        struct SzseOrderQueue           //基础订单簿
        {
            char 		MsgType;               	//消息类型（“P”）
            uint8_t 	MsgVer;             	//版本号
            char 		Side;                  	//买卖方向 “1”=买 “ 2”=卖
            char 		Status;                	//数据状态 “1”=正常 “ 2”=存疑
            uint64_t 	SeqNum;            		//订单簿推送消息序号
            uint64_t 	ApplSeqNum;        		//原始逐笔编号
            char 		SecurityID[8];         	//证券代码
            uint64_t 	TransactTime;      		//时间 yyyy mm dd hh mm ss sss
            uint32_t 	Last_Price;        		//最新价 N13(4)
            uint64_t 	Trade_Mark_Qty;    		//市价（量）N15(2)
            uint64_t 	Trade_Qty[10];     		//1档-10档（量）N15(2)
            uint32_t 	Trade_Price[10];   		//1档-10档（价）N13(4)
        };

        struct SzseOrderQueueCage       //带笼子内价格订单簿(仅创业板有效)
        {
            char 		MsgType;               	//消息类型（“Q”）
            uint8_t 	MsgVer;             	//版本号
            char 		Side;                  	//买卖方向 “1”=买 “ 2”=卖
            char 		Status;                	//数据状态 “1”=正常 “ 2”=存疑
            uint64_t 	SeqNum;            		//订单簿推送消息序号
            uint64_t 	ApplSeqNum;        		//原始逐笔编号
            char 		SecurityID[8];         	//证券代码
            uint64_t 	TransactTime;      		//时间 yyyy mm dd hh mm ss sss
            uint32_t 	Last_Price;        		//最新价 N13(4)
            uint64_t 	Trade_Mark_Qty;    		//市价（量）N15(2) 
            uint64_t 	Trade_Qty[10];     		//原始1档-10档（量）N15(2)
            uint32_t 	Trade_Price[10];   		//原始1档-10档（价）N13(4) 
            uint64_t 	Cage_Qty[10];      		//价格笼子1档-10档（量）N15(2) 
            uint32_t 	Cage_Price[10];    		//价格笼子1档-10档（价）N13(4)  
        };

        struct SzszOrderQueueErr             	//订单簿错误信息包文
        {
            char 		MsgType;               	//消息类型（“X”）
            uint8_t 	MsgVer;             	//版本号
            char 		ErrType;               	//错误类型 “a”= 通道逐笔丢失
            char 		Rsv1;                  	//硬件保留字段
            uint32_t 	TransactTime;      		//时间 hh mm ss sss
            uint16_t 	Chanel;            		//错误通道
			char 		Rsv[2];					
            uint64_t 	SeqNum;            		//错误消息序号
            char 		Rsv2[76];              	
        };

        struct SzseIOPV                      //IOPV
        {
            char 		MsgType;            //消息类型(I)
            char 		SecurityID[8];      //证券代码（ETF二级市场的交易代码）
            uint64_t 	IOPV;               //实时净值（基金份额参考净值），4位小数
            uint32_t    Cstock_TradeTime;   //成分股交易时间 hh mm ss sss 
            uint32_t 	TradePrice;         //最新价（ETF的最新成交价格，没有成交时为0），4位小数
            uint32_t 	TransactTime;       //时间 （ETF的最新成交时间，没有成交时为0）
            char        Rsv[35];
        };

        struct SzseRealtimeIndex            //实时指数
        {
            char		MsgType;			//消息类型(Z）
            char		IndexID[7];			//指数代码
            uint64_t	LastIndex;			//实时计算的最新指数，6位小数
            uint64_t	TradeTime;			//成分股的逐笔成交时间 hh mm ss sss
            uint64_t	NumTrades;			//指数计算的总成交笔数
            uint64_t	TotalVolumeTrade;	//指数计算的成交总量，2位小数
            uint64_t	TotalValueTrade;	//指数计算的成交总金额，4位小数
            uint64_t	PreCloseIndex;		//前收盘指数，6位小数
            uint64_t	OpenIndex;			//今开盘指数，6位小数
            uint64_t	HighIndex;			//最高指数，6位小数
            uint64_t	LowIndex;			//最低指数，6位小数
            uint64_t	CloseIndex;			//今收盘指数，6位小数
            uint64_t 	UpdateTime;			//本地指数行情计算时间 hh mm ss sss
        };
#pragma pack(pop)
	}
}