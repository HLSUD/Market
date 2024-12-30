#pragma once
/** �޸ļ�¼:
    20231211 "��ʼ�汾"
    
*/

#include <stdint.h>

namespace istone
{
    namespace base
    {
        enum bseMsgType
        {
            bseIndexType = (char)'J',           //ָ������ 
            bseDepthType = (char)'K',           //�������� 
        };
#pragma pack(push, 1)

        /*********************************************************************
           ָ����������
        *********************************************************************/
        struct BseIndex
        {
            char        MsgType;			          	//��Ϣͷ(��J��)
            uint64_t    OrigTime; 			        	//��������ʱ��
            char        SecurityID[8];		      		//֤ȯ����
            char        TradingPhaseCode[8];    		//��Ʒ�����Ľ��׽׶εĴ���
            uint64_t    NumTrades; 			        	//�ɽ�����
            uint64_t    TotalVolumeTrade; 	    		//�ɽ�������3λС����
            uint64_t    TotalValueTrade; 	      		//�ɽ��ܽ�3λС����
            uint64_t	LastIndex; 		          		//��ǰָ��,5λС����
            uint64_t 	PreCloseIndex;		      		//��������ָ��,5λС����
            uint64_t    OpenIndex;			        	//����ָ��,5λС����
            uint64_t    HighIndex; 		          		//���ָ��,5λС����
            uint64_t    LowIndex; 			        	//���ָ��,5λС����
            uint64_t    CloseIndex;		          		//����ָ��,5λС����
        };
        /*********************************************************************
            ���ۣ���ָ������������
        *********************************************************************/
        struct BseDepth
        {
            char        MsgType; 			          	//��Ϣͷ(��K��)
            uint64_t    OrigTime; 				      	//��������ʱ��
            uint16_t  	ChannelNo; 	    				//Ƶ������
            char    	MDStreamID[3];					//�������
            char        SecurityID[8];			    	//֤ȯ����
            char        TradingPhaseCode[8]; 	  		//��Ʒ�����Ľ��׽׶εĴ���
            uint32_t    PrevClosePx; 			      	//���ռۣ�5λС����
            uint64_t    NumTrades;				      	//�ɽ����� 
            uint64_t    TotalVolumeTrade;		    	//�ɽ�������3λС����
            uint64_t    TotalValueTrade;		    	//�ɽ��ܽ�3λС����
            uint64_t    UpperLimitPrice; 				//��ͣ�ۣ�5λС����
            uint64_t    LowerLimitPrice; 				//��ͣ�ۣ�5λС����
            uint32_t    LastPrice; 						//����ɽ��ۣ�����:2����5λС����
            uint32_t    OpenPrice; 						//���̼ۣ����飺4����5λС����
            uint32_t    ClosePrice; 					//���̼ۣ����飺5����5λС����
            uint32_t    HighPrice; 						//��߼ۣ����飺7����5λС����
            uint32_t    LowPrice;  						//��ͼۣ����飺8����5λС����
            uint32_t    AvgPrice; 						//��Ȩƽ���ۣ����飺9����5λС����
            uint64_t    TotalBidQty; 					//ί���������������飺x3=������ܣ���������Ȩƽ���ۣ�����3λС����
            uint64_t    TotalAskQty; 					//ί���������������飺x4=�������ܣ���������Ȩƽ���ۣ�����3λС����
            uint32_t    MaBidPrice; 					//��Ȩί������۸����飺x3=������ܣ���������Ȩƽ���ۣ�����5λС����
            uint32_t    MaAskPrice; 					//��Ȩί�������۸����飺x4=�������ܣ���������Ȩƽ���ۣ�����5λС����
            uint32_t    BidPrice[10];          			//10����ۣ����飺0����5λС����
            uint64_t    BidQty[10];						//10�����������飺0����3λС����
            uint32_t    AskPrice[10];  					//10�����ۣ����飺1����5λС����
            uint64_t    AskQty[10];   					//10�����������飺1����3λС����
            uint64_t    InstrQtyNum;				    //��Լ�ֲ���,��Ȩ��Ч��3λС����
        };
        

#pragma pack(pop)
    }
}
