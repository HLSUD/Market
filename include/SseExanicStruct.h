#pragma once
/** �޸ļ�¼:
    20211015 "��ʼ�汾"
    20211201 "ͳһ�ṹ������;ɾ������Ҫ��ע��"
    20220623 "���Ӷ������ṹ��;ע�Ͳ������"
	20220818 "���¶������ṹ��;ע�Ͳ������"
	20230404 "���¶������ṹ��;�۸��ֶ��޸�"
    20230810 "����IOPV�ṹ��"
    20231010 "����ʵʱָ���ṹ��"
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
            HAS_PRICE,//ȫ������
            NO_PRICE //Ӳ��������ʮ����ί����ϸ����0
        };

        enum sseMsgType
        {
            sseEntrustType = (char)'a',         //���ί�� 
            sseTradeType = (char)'b',           //��ʳɽ� 
            sseIndexType = (char)'c',           //ָ������ 
            sseDepthType0 = (char)'d',          //�������� 
            sseDepthType1 = (char)'e',          //�������飨����10����
            sseDepthFiftyType = (char)'f',      //50��ί�� 
            sseOptionType = (char)'g',          //��Ȩ����
            sseOrderQueueType = (char)'p',      //����������
            SseOrderQueueErrType = (char)'x',   //������������Ϣ���� 
            sseIOPVType = (char)'i',            //IOPV
            sseRealtimeIndex = (char)'z',       //ʵʱָ��
            sseMyEntrustType = (char)'w',         //���ί�� 

        };
#pragma pack(push, 1)

        /*********************************************************************
            UA3113 CategoryID=6  ָ����������
        *********************************************************************/
        struct SseIndex
        {
            char		MsgType;			     	// ��Ϣͷ��c��
            uint32_t 	UpdateTime;			   		// ����ʱ��
            char		SecurityID[8];		 		// ֤ȯ����
            uint64_t	PreCloseIndex;		 		// ǰ����ָ����5λС����
            uint64_t	OpenIndex;			   		// ����ָ����5λС����
            uint64_t	Turnover;			     	// ���������Ӧָ���ĳɽ���Ԫ����1λС����
            uint64_t	HighIndex;			   		// ���ָ����5λС����
            uint64_t	LowIndex;			     	// ���ָ����5λС����
            uint64_t	LastIndex;			   		// ����ָ����5λС����
            uint32_t	TradeTime;			   		// �ɽ�ʱ��
            uint64_t	TotalVolumeTrade;	 		// ���������Ӧָ���Ľ����������֣���5λС����
            uint64_t	CloseIndex;			   		// ������ָ��������0Ϊ��Чֵ����5λС����
            char	    Rsv[3];				     	// �����ֶ�
        };
        /*********************************************************************
            UA3202 CategoryID=6  ��������������ݣ���ծȯ��
			UA3802 CategoryID=6  ��������������ݣ�ծȯ��
        *********************************************************************/
        struct SseDepth
        {
            char		MsgType;				   	// ��Ϣͷ��d:������10�� e:������10������Ʊ Ȩ֤ ���� ծȯ					
            uint32_t	UpdateTime;				  	// ���¶���ʱ��
            char		SecurityID[8];				// ֤ȯ���룬6�ֽ���Ч
            uint32_t	PreClosePx;					// �����̼ۣ�3λС����
            uint32_t	OpenPx;						// ���̼ۣ�3λС����
            uint32_t	HighPx;						// ��߼ۣ�3λС����
            uint32_t	LowPx;						// ��ͼۣ�3λС����
            uint32_t	LastPx;						// �ּۣ�3λС����
            uint32_t	ClosePx;					// �������̼۸�3λС����
            char		InstruStatus[6];			// ��ǰƷ�ֽ���״̬
            char		TradingPhaseCode[5];		// ��ǰ��Ʒ״̬
            uint32_t    UpperLimitPrice; 			// ��ͣ�ۣ����飺xe����3λС����ȡ�Ծ�̬�ļ���
            uint32_t    LowerLimitPrice;			// ��ͣ�ۣ����飺xf����3λС����ȡ�Ծ�̬�ļ���
            uint32_t	NumTrades;					// �ɽ�����
            uint64_t	TotalVolumeTrade;			// �ɽ�������3λС����  
            uint64_t	TotalValueTrade;			// �ɽ��ܽ�� ��5λС����  
            uint64_t	TotalBidQty;				// ί���������� ��3λС����  
            uint32_t	WeightedAvgBidPx;			// ��Ȩί��۸� ��ծȯ���ã�3λС����
            uint64_t	TotalOfferQty;				// ί������������3λС����
            uint32_t	WeightedAvgOfferPx;			// ��Ȩί���۸�ծȯ���ã�3λС����
            uint32_t	WeightedAvgPx;				// ծȯ��Ȩƽ���۸�,ծȯ��Ч����ծȯΪ0��3λС����
            uint32_t	TotalBidNumber;				// �����ܱ�����
            uint32_t	TotalOfferNumber;			// �����ܱ�����

            //------------ȫ����Ϣ������10���۲�����ʱ��������--------------
            uint32_t	BidPrice[10];				// 10����ۣ�3λС����
            uint64_t	BidQty[10];					// 10��������3λС����
            uint32_t	AskPrice[10];				// 10�����ۣ�3λС����
            uint64_t	AskQty[10];					// 10��������3λС����

            
        };
        /*********************************************************************
            UA3202 CategoryID=6  �����������ί�ж�������
			UA3802 CategoryID=6  ծȯ�������ί�ж�������
        *********************************************************************/
        struct SseDepthFifty
        {
            char        MsgType;			    	//��Ϣͷ(��f��)
            uint32_t  	UpdateTime; 		  		//���¶���ʱ��
            char  		SecurityID[8];				//֤ȯ����
            uint32_t    BidOrderPrice;    			//��һ��ί�м۸�3λС����
            uint64_t    BidOrderQty;   				//��һ��ί������3λС����
            uint32_t    AskOrderPrice;    			//��һ��ί�м۸�3λС����
            uint64_t    AskOrderQty;   				//��һ��ί������3λС����
            char		Rsv;				        
            uint32_t    BidNumOfOrders; 			//��һ����λ��ί�б��������飺0��
            uint32_t    AskNumOfOrders; 			//��һ����λ��ί�б��������飺1��
            uint8_t 	BidNoOrders;  				//��һ����λ��ʾί�б��������飺0��
            uint8_t 	AskNoOrders;    			//��һ����λ��ʾί�б��������飺1��
            uint32_t    Orders[100];    			//��һ��/��һ��50��ί�У����飺0��
        };
        /*********************************************************************
            UA9002 CategoryID=30  ����������Ȩ�������� MsgType=W
        *********************************************************************/
        struct SseOption
        {
            char  		MsgType;                //��Ϣͷ��g��
            char		SecurityID[8];          //֤ȯ����
            uint64_t	LastPx;                 //�ɽ��ۣ�5λС����
            uint64_t	TradeQty;               //�ɽ���
            char		TradeTime[8];           //�ɽ�ʱ��
            char		TradingPhaseCode[4];	//��ǰ��Ʒ״̬
            char		Rsv[3];				    //�����ֶ�
            uint32_t	NumTrades;              //�ɽ�����
            uint64_t	TotalVolumeTrade;       //�ɽ�����
            uint64_t  	TotalValueTrade;		//�ܳɽ���5λС����
            uint64_t  	PreClosePx;             //�����̼ۣ�5λС����
            uint64_t  	PreSetPx;               //�����ۣ�5λС����
            uint64_t	TotalLongPosition;      //δƽ�ֺ�Լ����
            uint64_t 	OpenPx;                 //���̼ۣ�5λС����
            uint64_t  	ClosePx;                //�����̼ۣ�5λС����
            uint64_t  	SetPx;                  //�����ۣ�5λС����
            uint64_t  	HighPx;                 //������߳ɽ��ۣ�5λС����
            uint64_t  	LowPx;                  //������ͳɽ��ۣ�5λС����
            uint64_t	BidPrice[5];            //���嵵�۸�5λС����
            uint64_t	BidQty[5];              //���嵵����
            uint64_t	AskPrice[5];            //���嵵�۸�5λС����
            uint64_t	AskQty[5];              //���嵵����
            uint64_t  	RefrencePrice;          //��̬�ο��۸�5λС����
            uint64_t  	RefrenceQty;            //��̬�ο���
            uint32_t    UpdateDate;             //�������ʱ�� yyyy mm dd
            uint32_t    UpdateTime;             //�������ʱ�� 
        };

        /*********************************************************************
            UA5801 CategoryID=58 �������ί������
			UA5803 CategoryID=9 �������ί�кϲ�����/��Ʒ״̬
            UA3901 CategoryID=39 ծȯ���ί������/��Ʒ״̬
        *********************************************************************/
        struct  SseEntrust
        {
            char        MsgType;        //��Ϣͷ��a��			
            char        OrderType;      //�������ͣ�A-����ί�ж�����D-ɾ��ί�ж�����S-��Ʒ״̬������
            char        OrderBSFlag;    //������־ OrderType��A��Dʱ��OrderBSFlagΪB-�� S-����,OrderType��Sʱ��Ч��	
            char        TickBSFlag;     //��Ʒ״̬ OrderType��A��Dʱ��Ч��OrderType��Sʱ��TickBSFlagΪA-ADD S-START O-OCALL T-TRADE S-SUSP C-CLOSE Q-CCALL��
            uint32_t    OrderIndex;     //��š����ھ������ί�����ݣ���1��ʼ��Channel����������ծȯ�;��ۺϲ����ݣ���'b'��ծȯ�;��ۺϲ����ݵ�TradeIndex�ϲ���Channel������
            uint32_t    OrderChannel;   //ͨ����
            char        SecurityID[8];  //֤ȯ����
            uint32_t    OrderTime;      //ί��ʱ��
            uint64_t    OrderNO;        //ԭʼ������
            uint32_t    OrderPrice;     //ί�м۸�3λС��
            uint64_t    Balance;        //ʣ��ί������3λС��
            uint64_t    BizIndex;       //��š����ھ������ί�����ݣ��뾺����ʳɽ����ݺϲ���Channel����������ծȯ��Ч�����ھ��ۺϲ����ݣ��롮b���о��ۺϲ����ݵ�BizIndex�ϲ���Channel������
            char	    Rsv[12];		//�����ֶ�
        };

        /*********************************************************************
            UA3201 CategoryID=7  ������ʳɽ�����
            UA5803 CategoryID=9  ������ʳɽ��ϲ�����
            UA3901 CategoryID=39 ծȯ��ʳɽ�����
        *********************************************************************/
        struct  SseTrade				//��ʳɽ�
        {
            char		MsgType;	  	// ��Ϣͷ��b��
            uint32_t	TradeIndex;		// ��ţ����ھ�����ʳɽ����ݣ���1��ʼ��Channel����������ծȯ�;��ۺϲ����ݣ���'a'��ծȯ�;��ۺϲ����ݵ�OrderIndex�ϲ���Channel������
            uint32_t	TradeChannel;	// ͨ����
            char		SecurityID[8];	// ֤ȯ����
            uint32_t	TradeTime;		// �ɽ�ʱ��
            uint32_t	TradePrice;		// �ɽ��۸�3λС����
            uint32_t	TradeQty;		// �ɽ�������3λС����
            uint64_t	TradeMoney;		// �ɽ���5λС����
            uint64_t	TradeBuyNo;		// �򷽶�����
            uint64_t	TradeSellNo;	// ����������
            uint64_t  	BizIndex;       // ��ţ����ھ�����ʳɽ����ݣ��뾺�����ί�����ݺϲ���Channel����������ծȯ��Ч�����ھ��ۺϲ����ݣ��롮a���о��ۺϲ����ݵ�BizIndex�ϲ���Channel������
            char		TradeBSFlag;	// �����̱�־
            char		Rsv[2];			// �����ֶ�
        };

        /*********************************************************************
          ������
        *********************************************************************/
        struct SseOrderQueue            //����������
        {
            char 		MsgType;            //��Ϣ����(p)
            uint8_t 	MsgVer;             //�汾��
            char 		Side;               //�������� ��0��=�� ��1��=��
            uint8_t 	Channel;            //ͨ����
            uint32_t 	BizIndex;           //ҵ�����к�
            uint32_t 	Applseqnum;         //������������Ϣ���
            char 		SecurityID[6];      //֤ȯ����
            char 		Reliability;        //���ݿɿ��� ��1��=���� �� 2��=����
            char 		Rsv;                //����
            uint32_t 	TransactTime;       //ʱ�� hh mm ss sss
            uint64_t 	Trade_Qty[10];      // 1��-10����������3λС����
            uint32_t 	Trade_Price[10];	// 1��-10�����۸񣩣�3λС����
            uint32_t    TradePrice;         //���¼ۣ�3λС����
        };

        struct SseOrderQueueErr             //������������Ϣ����
        {
            char 		MsgType;            //��Ϣ����(x)
            uint8_t 	MsgVer;             //�汾��
            char 		ErrType;            //�������� ��a��= ͨ����ʶ�ʧ 
            uint8_t 	Channel;            //����ͨ��
            uint32_t 	TransactTime;       //ʱ�� hh mm ss sss
            uint64_t 	BizIndex;           //������Ϣ���
        };

        struct SseIOPV                      //IOPV
        {
            char 		MsgType;            //��Ϣ����(i)
            char 		SecurityID[8];      //֤ȯ���루ETF�����г��Ľ��״��룩
            uint64_t 	IOPV;               //ʵʱ��ֵ������ݶ�ο���ֵ����4λС��
            uint32_t    Cstock_TradeTime;   //�ɷֹɽ���ʱ�� hh mm ss ss
            uint32_t 	TradePrice;         //���¼ۣ�ETF�����³ɽ��۸�û�гɽ�ʱΪ0����3λС��
            uint32_t 	TransactTime;       //ʱ�� ��ETF�����³ɽ�ʱ�䣬û�гɽ�ʱΪ0��
            char        Rsv[35];
        };

        struct SseRealtimeIndex             //ʵʱָ��
        {
            char		MsgType;			//��Ϣ����(z��
            char		IndexID[7];		    //ָ������
            uint64_t	LastIndex;          //ʵʱ���������ָ����5λС��
            uint64_t	TradeTime;			//�ɷֹɵ���ʳɽ�ʱ��
            uint64_t	NumTrades;          //ָ��������ܳɽ�����
            uint64_t	TotalVolumeTrade;	//ָ������ĳɽ�������5λС��
            uint64_t	TotalValueTrade;	//ָ������ĳɽ��ܽ�1λС��
            uint64_t	PreCloseIndex;		//ǰ����ָ����5λС��
            uint64_t	OpenIndex;			//����ָ����5λС��
            uint64_t	HighIndex;			//���ָ����5λС��
            uint64_t	LowIndex;			//���ָ����5λС��
            uint64_t	CloseIndex;			//������ָ����5λС��
            uint64_t 	UpdateTime;			//����ָ���������ʱ�� hh mm ss sss
        };

#pragma pack(pop)
    }
}
