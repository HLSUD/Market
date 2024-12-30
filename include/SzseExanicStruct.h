#pragma once
/** �޸ļ�¼:
    20211015 "��ʼ�汾"
	20211201 "ͳһ�ṹ������;ɾ������Ҫ��ע��"
    20220623 "���Ӷ������ṹ��"
	20220711 "SzszOrderQueueErr"��� Rsv�ֶΣ�ע�Ͳ������
    20230810 "����IOPV�ṹ��"
    20231010 "����ʵʱָ���ṹ��"
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
			szseTradeStaticsType = 'A',			//�ɽ���ͳ������
			szseIndexType = 'B',             	//ָ������
			szseEntrustType = 'C', 			    //���ί��
			szseTradeType = 'D',   			    //��ʳɽ�
			szseDepthOrOptionType = 'E',     	//�����������(����Ȩ)
			szseDepthFiftyType = 'F',        	//50��ί��
      		szseOrderQueueType = 'P',	        //����������
      		szseOrderQueueCageType = 'Q',	    //�������ڼ۸񶩵���(����ҵ����Ч)  
      		szseOrderQueueErrType = 'X',    	//������������Ϣ����(X) 
      		szseIOPVType = 'I',    	            //IOPV 
            szseRealtimeIndex = 'Z',            //ʵʱָ��
		};
#pragma pack(push, 1)


		/*********************************************************************
		  309111  910 �ɽ���ͳ��ָ���������
		*********************************************************************/

		struct SzseTradeStatics
		{
      		char        MsgType; 			          	//��Ϣͷ(��A��)
			char        TradingPhaseCode[3]; 	  		//�г�״̬
			uint64_t    OrigTime; 				      	//��������ʱ��
      		char        SecurityID[8];			    	//֤ȯ����
			uint64_t    PrevClosePx; 			      	//���ռۣ�4λС����
			uint64_t    NumTrades;				      	//�ɽ����� 
			uint64_t    TotalVolumeTrade;		    	//�ɽ�������2λС����
			uint64_t    TotalValueTrade;		    	//�ɽ��ܽ�4λС����
			uint32_t    StockNum;				        //ͳ����ָ����������
		};

		/*********************************************************************
			309011  900 ָ����������
		  309011  920 ��ָ֤����������
		*********************************************************************/
		struct SzseIndex
		{
			char        MsgType;			          	//��Ϣͷ(��B��)
			char        TradingPhaseCode[3];    		//�г�״̬
			uint64_t    OrigTime; 			        	//��������ʱ��
      		char        SecurityID[8];		      		//֤ȯ����
			uint64_t    NumTrades; 			        	//�ɽ�����
			uint64_t    TotalVolumeTrade; 	    		//�ɽ�������2λС����
			uint64_t    TotalValueTrade; 	      		//�ɽ��ܽ�4λС����
      		uint64_t	LastIndex; 		          		//��ǰָ��,6λС����
      		uint64_t 	PreCloseIndex;		      		//��������ָ��,6λС����
      		uint64_t    OpenIndex;			        	//����ָ��,6λС����
      		uint64_t    HighIndex; 		          		//���ָ��,6λС����
			uint64_t    LowIndex; 			        	//���ָ��,6λС����
			uint64_t    CloseIndex;		          		//����ָ��,6λС����
		};

		/*********************************************************************
			300111  010 �ֻ�����Ʊ������ȣ����о��۽��׿�������
					    040 ��Ȩ���о��۽��׿�������
			300211	020 ծȯͨ����Ѻʽ�ع�ƥ�佻�׿�������
					    030 ծȯ������������
					    410 ծȯ��ȯ���׿�������
			300611	060 �����̼۽��׵��̺󶨼۴��ڽ��׿�������
					    061 �Գɽ�����Ȩƽ���۽��׵��̺󶨼۴��ڽ��׿�������
			303711	370 �̺󶨼۽��׿�������
			306311	630 �۹�ʵʱ����
		*********************************************************************/
		struct SzseDepth
		{
			char     	MsgType;				    //��Ϣͷ(��E��)
			char    	MDStreamID[3];				//�������
			char  	    TradingPhaseCode[2];		//�г�״̬
			char     	SecurityID[8];				//֤ȯ����
			uint64_t  	OrigTime; 				  	//��������ʱ��
			uint16_t  	ChannelNo; 	    			//Ƶ������
			uint32_t    PrevClosePx; 			  	//���ռۣ�4λС����
			uint32_t    LastPrice; 			    	//����ۣ�6λС����
			uint32_t    OpenPrice; 			    	//���̼ۣ�6λС����
			uint32_t    HighPrice; 			    	//��߼ۣ����飺7����6λС����
			uint32_t    LowPrice;  			    	//��ͼۣ����飺8����6λС����
			uint64_t    UpperLimitPrice; 			//��ͣ�ۣ����飺xe����6λС����
			uint64_t    LowerLimitPrice; 			//��ͣ�ۣ����飺xf����6λС����
			uint32_t    AvgPrice; 				 	//��Ȩƽ���ۣ����飺9��Ϊ�ֻ�ʱ-�գ�Ϊ��Ѻʽ�ع�ʱ-���顣
			                                		//�ֶα�ʾ��Ѻʽ�ع���ʵʱ�ɽ�����Ȩƽ�����ʼ�ծȯ��ȯ���׳ɽ�����Ȩƽ���ۡ�
			                                		//��Ѻʽ�ع��ĸ���Ŀ��������Ѻʽ�ع���ծȯ��ȯ���ײ�Ʒ������
												    //ʵʱ�ɽ�����Ȩƽ�����ʣ���ȷ�� 5 λС����
			uint64_t    NumTrades; 				  	//�ɽ����� 
			uint64_t    TotalVolumeTrade; 			//�ɽ�������2λС����
			uint64_t    TotalValueTrade; 			//�ɽ��ܽ�4λС����
      		uint64_t    TotalBidQty; 	      		//ί���������������飺x3=������ܣ���������Ȩƽ���ۣ�����2λС����
      		uint64_t    TotalAskQty; 	      		//ί���������������飺x4=�������ܣ���������Ȩƽ���ۣ�����2λС����
      		uint64_t    MaBidPrice; 	      		//��Ȩί������۸����飺x3=������ܣ���������Ȩƽ���ۣ�����6λС����
      		uint64_t    MaAskPrice; 	      		//��Ȩί�������۸����飺x4=�������ܣ���������Ȩƽ���ۣ�����6λС����
      		uint32_t    BidPrice[10];       		//10����ۣ����飺0����6λС����
      		uint64_t    BidQty[10];		      		//10�����������飺0����2λС����
      		uint32_t    AskPrice[10];  				//10�����ۣ����飺1����6λС����
      		uint64_t    AskQty[10];   				//10�����������飺1����2λС����
      		//������Ȩ�����ֶ�
      		uint64_t    InstrQtyNum;        		//��Լ�ֲ���,��Ȩ��Ч��2λС����
      		uint64_t    BrkRefPrice;        		//�ο���,��Ȩ��Ч��6λС����
			                                		//��������侲�ڣ����ʾ���o�ڃȵĲο��۸�
												    //����������̼��Ͼ���ʱ�Σ����ʾ���̼��Ͼ���ʱ�βο��ۣ�
												    //������ڿ��̼��Ͼ���ʱ�Σ����ʾ���̼��Ͼ���ʱ�βο��ۡ�
      		uint32_t    Iopv; 					    //����ʵʱ�ο���ֵ������ETF�����飺x8=����ʵʱ�ο���ֵ������ ETF�� IOPV������6λС��,��Ȩ��Ч
      		uint32_t    PreIopv;				    //����T-1�վ�ֵ�����飺x7=���� T-1 �վ�ֵ����6λС��,��Ȩ��Ч��
		};
		/*********************************************************************
			�����������ί�ж�������
		*********************************************************************/
		struct SzseDepthFifty
		{
			char        MsgType;			    	//��Ϣͷ(��F��)
			char     	MDStreamID[3];				//�������
			uint64_t  	OrigTime; 			  		//��������ʱ��
			char    	SecurityID[8];				//֤ȯ����
      		uint32_t    BidOrderPrice;    			//��һ��ί�м۸�6λС����
      		uint64_t    BidOrderQty;   				//��һ��ί������2λС����
      		uint32_t    AskOrderPrice;    			//��һ��ί�м۸�6λС����
      		uint64_t    AskOrderQty;   				//��һ��ί������2λС����
			char		Rsv[2];				    	//
      		uint32_t    BidNumOfOrders; 			//��һ����λ��ί�б��������飺0�� 
      		uint32_t    AskNumOfOrders; 			//��һ����λ��ί�б��������飺1�� 
      		uint8_t 	BidNoOrders;  				//��һ����λ��ʾί�б��������飺0�� 
      		uint8_t 	AskNoOrders;    			//��һ����λ��ʾί�б��������飺1�� 
      		uint32_t    Orders[100];    			//��/��һ��50��ί�У����飺0�� 
		};

		/*********************************************************************
			300192  011 �ֻ�����Ʊ������ծȯ�ȣ����о��۽����������
			        041 ��Ȩ���о��۽����������
			300592  051 Э�齻�������������
			        052 Э�齻����ʶ�������
			300792  071 ת��֤ͨȯ�����������
			300292  021 ծȯͨ����Ѻʽ�ع�ƥ��ɽ��������
			        411 ծȯ��ȯ����ƥ��ɽ��������
			300392  413 ծȯ��ȯ���׵���ɽ��������
			        415 ծȯ��ȯ���������걨�������
			300492  416 ծȯ��ȯ���׾���ɽ��������
			300392  417 ծȯ��ȯ����ƥ��ɽ�����������
		***********************************************************************/
		struct SzseEntrust
		{
			char      	MsgType;		    	//��Ϣͷ(��C��)
			char    	MDStreamID[3];			//�������
			uint64_t   	Applseqnum; 	  		//��Ϣ��¼�Ŵ� 1 ��ʼ����
			char   		SecurityID[8];			//֤ȯ����
			uint16_t  	ChannelNo; 	    		//Ƶ������
			char    	Side;			      	//��������
			char   		OrdType;		    	//�������
			uint32_t 	Price;  		    	//ί�м۸�,4λС��
			uint32_t   	OrderQty; 		  		//ί������,2λС��
			uint64_t   	TransactTime;	  		//ί��ʱ��
			char    	Rsv[24];        		//Ӳ�������ֶ�
		};

		/*********************************************************************
		300191  011 �ֻ�����Ʊ������ծȯ�ȣ����о��۽����������
            041 ��Ȩ���о��۽����������
    300591  051 Э�齻�������������
            052 Э�齻����ʶ�������
		300791	071 ת��֤ͨȯ�����������
		300291	021 ծȯͨ����Ѻʽ�ع�ƥ��ɽ��������
				    411 ծȯ��ȯ����ƥ��ɽ��������
		300391  412 ծȯ��ȯ����Э�̳ɽ��������
				    413 ծȯ��ȯ���׵���ɽ��������
				    414 ծȯ��ȯ����ѯ�۳ɽ��������
		300491	416 ծȯ��ȯ���׾���ɽ��������
		300391  417 ծȯ��ȯ����ƥ��ɽ�����������
		***********************************************************************/
		struct SzseTrade
		{
			char     	MsgType;			    //��Ϣͷ(��D��)
			char    	MDStreamID[3];			//�������
			uint64_t   	Applseqnum; 		  	//��Ϣ��¼�Ŵ� 1 ��ʼ����
			uint64_t   	BidApplSeqNum;			//��ί�������� 1 ��ʼ������0 ��ʾ�޶�Ӧί��
			uint64_t   	OfferApplSeqNum;  		//����ί�������� 1 ��ʼ������0 ��ʾ�޶�Ӧί��
			char    	SecurityID[8];			//֤ȯ����
			uint16_t  	ChannelNo ; 		  	//Ƶ������
			char    	ExecType; 			  	//�ɽ����4=����F=�ɽ�
			char 		Rsv0;
			uint32_t	TradePrice;		    	//�ɽ��۸�4λС����
			uint32_t   	TradeQty;			    //�ɽ�������2λС����
			uint64_t   	TransactTime;		  	//�ɽ�ʱ��
			char    	Rsv1[8];          		//Ӳ�������ֶ�
		};

        /*********************************************************************
            ������
        *********************************************************************/

        struct SzseOrderQueue           //����������
        {
            char 		MsgType;               	//��Ϣ���ͣ���P����
            uint8_t 	MsgVer;             	//�汾��
            char 		Side;                  	//�������� ��1��=�� �� 2��=��
            char 		Status;                	//����״̬ ��1��=���� �� 2��=����
            uint64_t 	SeqNum;            		//������������Ϣ���
            uint64_t 	ApplSeqNum;        		//ԭʼ��ʱ��
            char 		SecurityID[8];         	//֤ȯ����
            uint64_t 	TransactTime;      		//ʱ�� yyyy mm dd hh mm ss sss
            uint32_t 	Last_Price;        		//���¼� N13(4)
            uint64_t 	Trade_Mark_Qty;    		//�мۣ�����N15(2)
            uint64_t 	Trade_Qty[10];     		//1��-10��������N15(2)
            uint32_t 	Trade_Price[10];   		//1��-10�����ۣ�N13(4)
        };

        struct SzseOrderQueueCage       //�������ڼ۸񶩵���(����ҵ����Ч)
        {
            char 		MsgType;               	//��Ϣ���ͣ���Q����
            uint8_t 	MsgVer;             	//�汾��
            char 		Side;                  	//�������� ��1��=�� �� 2��=��
            char 		Status;                	//����״̬ ��1��=���� �� 2��=����
            uint64_t 	SeqNum;            		//������������Ϣ���
            uint64_t 	ApplSeqNum;        		//ԭʼ��ʱ��
            char 		SecurityID[8];         	//֤ȯ����
            uint64_t 	TransactTime;      		//ʱ�� yyyy mm dd hh mm ss sss
            uint32_t 	Last_Price;        		//���¼� N13(4)
            uint64_t 	Trade_Mark_Qty;    		//�мۣ�����N15(2) 
            uint64_t 	Trade_Qty[10];     		//ԭʼ1��-10��������N15(2)
            uint32_t 	Trade_Price[10];   		//ԭʼ1��-10�����ۣ�N13(4) 
            uint64_t 	Cage_Qty[10];      		//�۸�����1��-10��������N15(2) 
            uint32_t 	Cage_Price[10];    		//�۸�����1��-10�����ۣ�N13(4)  
        };

        struct SzszOrderQueueErr             	//������������Ϣ����
        {
            char 		MsgType;               	//��Ϣ���ͣ���X����
            uint8_t 	MsgVer;             	//�汾��
            char 		ErrType;               	//�������� ��a��= ͨ����ʶ�ʧ
            char 		Rsv1;                  	//Ӳ�������ֶ�
            uint32_t 	TransactTime;      		//ʱ�� hh mm ss sss
            uint16_t 	Chanel;            		//����ͨ��
			char 		Rsv[2];					
            uint64_t 	SeqNum;            		//������Ϣ���
            char 		Rsv2[76];              	
        };

        struct SzseIOPV                      //IOPV
        {
            char 		MsgType;            //��Ϣ����(I)
            char 		SecurityID[8];      //֤ȯ���루ETF�����г��Ľ��״��룩
            uint64_t 	IOPV;               //ʵʱ��ֵ������ݶ�ο���ֵ����4λС��
            uint32_t    Cstock_TradeTime;   //�ɷֹɽ���ʱ�� hh mm ss sss 
            uint32_t 	TradePrice;         //���¼ۣ�ETF�����³ɽ��۸�û�гɽ�ʱΪ0����4λС��
            uint32_t 	TransactTime;       //ʱ�� ��ETF�����³ɽ�ʱ�䣬û�гɽ�ʱΪ0��
            char        Rsv[35];
        };

        struct SzseRealtimeIndex            //ʵʱָ��
        {
            char		MsgType;			//��Ϣ����(Z��
            char		IndexID[7];			//ָ������
            uint64_t	LastIndex;			//ʵʱ���������ָ����6λС��
            uint64_t	TradeTime;			//�ɷֹɵ���ʳɽ�ʱ�� hh mm ss sss
            uint64_t	NumTrades;			//ָ��������ܳɽ�����
            uint64_t	TotalVolumeTrade;	//ָ������ĳɽ�������2λС��
            uint64_t	TotalValueTrade;	//ָ������ĳɽ��ܽ�4λС��
            uint64_t	PreCloseIndex;		//ǰ����ָ����6λС��
            uint64_t	OpenIndex;			//����ָ����6λС��
            uint64_t	HighIndex;			//���ָ����6λС��
            uint64_t	LowIndex;			//���ָ����6λС��
            uint64_t	CloseIndex;			//������ָ����6λС��
            uint64_t 	UpdateTime;			//����ָ���������ʱ�� hh mm ss sss
        };
#pragma pack(pop)
	}
}