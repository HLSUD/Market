#ifndef  _KS_HS_INTERFACE_EX_H_
#define  _KS_HS_INTERFACE_EX_H_
/** �޸ļ�¼:
    20220623 "��ʼ�汾"
*/
#include "KsHSDef.h"
#include "stdint.h"
#include "memory.h"
#include <vector>
#include <iostream>

#pragma pack(push, 4)

namespace istone_hs
{
    //�ַ�����װ����
    #define mystr2(x)  std::string(x, sizeof(x)).c_str()
   
    struct MetaInfo
    {
        char* version;              //�汾��
        char* authMetaInfo;         //��Ȩ������Ϣ
        char* multiMetaInfo;        //�鲥������Ϣ
    };

    struct AuthInfo
    {
        char* user;               //�û���
        char* passwd;             //����
        char* nic;                //���ؽ�������/�����ڶ�Ӧ��ip�����߶�֧�֣�
    };

    //���ض�������nicName�Ͻ���msgTypes��������������
    struct CacheAdvanceNicItem
    {
        char*     nicName;          //�������ƣ���һЩ����£���Ӧ��������Ҫ����ip��
        int32_t   cpuId;            //�����ڽ��������̵߳�cpu id
        char*     msgTypes;         //ϣ�����е���������
    };

    //���ݻص�ԭ��.������ҵ�����ݣ�
	using DATACALLBACK_WITHID = void(*)(void*, uint32_t);

    //msgTypes�е����ݹ���һ���������
    struct CacheAdvanceQueueItem
    {
        int32_t  queueId;           //Ψһ��־���벻ͬ
        char*    msgTypes;          //ϣ�����е���������
        int32_t  cpuId;             //�����ڽ��������̵߳�cpu id
        int32_t  blockSize;         //������С��2MB/per��
        DATACALLBACK_WITHID dataCallback;  //���ݻص�����
    };
    
    //���������ʧ�ܣ�����false����ϸ������Ϣ��鿴��־
    bool istone_start_ex(
                      MetaInfo*  metaInfo,

                      AuthInfo* authParam,
                      istone::comm::STATUSCALLBACK authCallback, 

                      CacheAdvanceNicItem* pNicList,
                      uint8_t nNicList,

                      CacheAdvanceQueueItem* pDataQueueList,
                      uint8_t nDataQueue
                      );

    //ֹͣ
    bool istone_stop_ex();

    //���ÿ�ѡ��
    /**
        key:
            AUTO_DEDUPLICATE_MSGTYPE --�Ƿ��Զ�ȥ��      ��1--�Զ�ȥ�أ�2--��ȥ�أ� ��Ĭ��Ϊ1��
            NIC_RECV_MODE            --������ȡ����ģʽ  ��1--SFC_EFVI, 2--EXANIC_PCIE����Ĭ��Ϊ1
    */
    bool istone_set_option_ex(const char* key, int val);

};

#pragma pack(pop)

#endif