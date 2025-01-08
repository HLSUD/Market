#ifndef _LEV2STRUCT_H
#define _LEV2STRUCT_H


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TORATstpLev2ApiDataType.h"
#include "TORATstpLev2ApiStruct.h"

// #include "TORATstpLev2ApiDataType.h"
namespace TORALEV2API_V2
{
    enum sseMsgType
    {
        sseEntrustType = (char)'a',         // Shanghai Entrust
        sseTradeType = (char)'t',           // Shanghai Trade
        sseSnapshotType = (char)'s',        // Shanghai Snapshot
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

    enum szseMsgType
    {
        szseEntrustType = (char)'A', 			    // Shenzhen Entrust
        szseTradeType = (char)'T',   			    // Shenzhen Trade
        szseSnapshotType = (char)'S',               // Shenzhen Snapshot
        szseTradeStaticsType = (char)'C',			//�ɽ���ͳ������
        szseIndexType = (char)'B',             	//ָ������
        szseDepthOrOptionType = (char)'E',     	//�����������(����Ȩ)
        szseDepthFiftyType = (char)'F',        	//50��ί��
        szseOrderQueueType = (char)'P',	        //����������
        szseOrderQueueCageType = (char)'Q',	    //�������ڼ۸񶩵���(����ҵ����Ч)  
        szseOrderQueueErrType = (char)'X',    	//������������Ϣ����(X) 
        szseIOPVType = (char)'I',    	            //IOPV 
        szseRealtimeIndex = (char)'Z',            //ʵʱָ��
    };
    #pragma pack(push, 1)
    struct SHSseNGTS
    {
        //Type
        char type;

        ///证券代码
        TORALEV2API::TTORATstpSecurityIDType	SecurityID;

        TORALEV2API::CTORATstpLev2NGTSTickField *field;
    };

    struct SHSse{

    };

    /// Lev2逐笔成交
	struct SzseTrade
	{
		//Type
        char type;

        ///证券代码
        TORALEV2API::TTORATstpSecurityIDType	SecurityID;

        TORALEV2API::CTORATstpLev2TransactionField *field;

	};

    /// Lev2逐笔委托
	struct SzseEntrust
	{
		//Type
        char type;

        ///证券代码
        TORALEV2API::TTORATstpSecurityIDType	SecurityID;

        TORALEV2API::CTORATstpLev2OrderDetailField *field;
	};

    /// Lev2逐笔委托
	struct SeSnapshot
	{
		//Type
        char type;

        ///证券代码
        TORALEV2API::TTORATstpSecurityIDType	SecurityID;

        TORALEV2API::CTORATstpLev2MarketDataField *field;
	};
    #pragma pack(pop)
}
#endif