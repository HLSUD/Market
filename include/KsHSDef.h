#pragma once
/** �޸ļ�¼:
    20211015 "��ʼ�汾"
*/
#include "stdint.h"

namespace istone
{ 
    namespace comm
    {
        static const int DEFAULT_MEM_BLOCK = 10; //ȱʡ�ڴ���С
        static const int  DEFAULT_CPU_ID = -1;   //Ĭ��cpu����id
        static const uint16_t DEFAULT_PORT = 0;  //Ĭ��socket�˿�

        enum MARKET
        {
            UNKNOWN_MARKET = 0,     //δ֪
            SH = 1,                 //�Ͻ���
            SZ = 2,                 //���
        };


        enum STATUS
        {
            STATUS_OK = 0,             //����      
            STATUS_DO_REQUEST,         //����ִ�д���
            STATUS_RETRY_CONNECTING,   //����������
            STATUS_CONNECTED,          //���ӳɹ�
            STATUS_DISCONNECTED,       //����ʧ��
            STATUS_LOGINING,           //��½��
            STATUS_LOGIN_SUCC,         //��¼�ɹ�
            STATUS_LOGOUT_SUCC,        //�ǳ�ʧ��
            STATUS_LOGIN_FAIL,         //��¼ʧ��
            STATUS_LOGOUT_FAIL,        //�ǳ�ʧ��
			STATUS_CFG_AUTH,           //δ���ü�Ȩ��Ϣ
            STATUS_NAMEORPWD_IS_NULL,  //�û���/����Ϊ��    
            STATUS_OTHER,              //��������
        };

        enum FilterMode
        {
            All = 0,        //ȫ��ͨ��
            None = 1,       //ȫ����ͨ��
            Part = 2,       //����ͨ��
        };

        enum SubType
        {
            TICK = 1,       //��ʣ����ί�С���ʳɽ���
            DEPTH           //����
        };

        enum CacheMode
        {
            DEFAULT = 1,    //Ĭ�ϻ���
            ADVANCED,       //�߼����壨δʵ�֣������ڴ���
        };

        //���ݻص�����ԭ��
        using DATACALLBACK = void(*)(void*);
        //��Ȩ�ص�����ԭ��
        using STATUSCALLBACK = void(*)(STATUS, const char*);
    }
};
