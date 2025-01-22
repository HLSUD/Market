#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unordered_map>
#include <cstring>
#include <chrono>
#include <mutex>
#include "TraderConfig.h"
#include "TORATstpTraderApi.h"

using namespace TORASTOCKAPI;
using namespace std;

class TradeSpi : public CTORATstpTraderSpi
{
public:
    std::unordered_map<std::string, CTORATstpPositionField*> postion_map_;
    std::unordered_map<std::string, int> avai_postion_map_;
    // std::unordered_map<std::string, std::string> query_trade_map_;
    std::unordered_map<std::string, int> query_trade_option_map_; // 1. query 2. cancel buy 3. cancel sell
    std::unordered_map<std::string, int> query_map_;
    std::mutex buy_num_mtx;
    int total_buy_num;
    int position_resp_last;

    TradeSpi(CTORATstpTraderApi *api)
    {
        m_api = api;
        m_req_id = 1;
    }

    TradeSpi(CTORATstpTraderApi *api, TraderConfig config)
    {
        m_api = api;
        m_req_id = 1;
        // set account and trading information
        InvestorID = config.InvestorID;
        UserID = config.UserID;
        AccountID = config.AccountID;
        Password = config.Password;
        SH_ShareHolderID = config.SH_ShareHolderID;
        SZ_ShareHolderID = config.SZ_ShareHolderID;
        BJ_ShareHolderID = config.BJ_ShareHolderID;
        DepartmentID = config.DepartmentID;
        login_Status = 0;
    }

    ~TradeSpi()
    {

    }

private:

    // Function to convert GBK to UTF-8
    // void gbk_to_utf8(const char *gbk_str, char *utf8_str, size_t utf8_len) {
    //     iconv_t cd = iconv_open("UTF-8", "GBK");
    //     if (cd == (iconv_t)-1) {
    //         perror("iconv_open");
    //         return;
    //     }

    //     char *inbuf = (char *)gbk_str;
    //     size_t inbytesleft = strlen(gbk_str);
    //     char *outbuf = utf8_str;
    //     size_t outbytesleft = utf8_len;

    //     // Perform the conversion
    //     if (iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft) == (size_t)-1) {
    //         perror("iconv");
    //     }

    //     // Null-terminate the output string
    //     *outbuf = '\0';

    //     iconv_close(cd);
    // }
    virtual void OnFrontConnected()
    {
        printf("TradeApi OnFrontConnected\n");

        // 获取终端信息
        int ret = m_api->ReqGetConnectionInfo(m_req_id++);
        if (ret != 0)
        {
            printf("ReqGetConnectionInfo fail, ret[%d]\n", ret);
        }
    }

    virtual void OnFrontDisconnected(int nReason)
    {
        printf("TradeApi OnFrontDisconnected: [%d]\n", nReason);
    }

    virtual void OnRspGetConnectionInfo(CTORATstpConnectionInfoField *pConnectionInfoField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        if (pRspInfo->ErrorID == 0)
        {
            printf("inner_ip_address[%s]\n"
                "inner_port[%d]\n"
                "outer_ip_address[%s]\n"
                "outer_port[%d]\n"
                "mac_address[%s]\n",
                pConnectionInfoField->InnerIPAddress,
                pConnectionInfoField->InnerPort,
                pConnectionInfoField->OuterIPAddress,
                pConnectionInfoField->OuterPort,
                pConnectionInfoField->MacAddress);


            TORASTOCKAPI::CTORATstpReqUserLoginField field;
            memset(&field, 0, sizeof(TORASTOCKAPI::CTORATstpReqUserLoginField));

            // 支持以用户代码、资金账号和股东账号方式登录
            // （1）以用户代码方式登录
            strcpy(field.LogInAccount, UserID);
            field.LogInAccountType = TORASTOCKAPI::TORA_TSTP_LACT_UserID;
            // （2）以资金账号方式登录
            //strcpy(field.DepartmentID, DepartmentID);
            //strcpy(field.LogInAccount, AccountID);
            //field.LogInAccountType = TORA_TSTP_LACT_AccountID;
            // （3）以上海股东账号方式登录
            //strcpy(field.LogInAccount, SSE_ShareHolderID);
            //field.LogInAccountType = TORA_TSTP_LACT_SHAStock;
            // （4）以深圳股东账号方式登录
            //strcpy(field.LogInAccount, SZSE_ShareHolderID);
            //field.LogInAccountType = TORA_TSTP_LACT_SZAStock;

            // 支持以密码和指纹(移动设备)方式认证
            // （1）密码认证
            // 密码认证时AuthMode可不填
            //field.AuthMode = TORA_TSTP_AM_Password;
            strcpy(field.Password, Password);
            // （2）指纹认证
            // 非密码认证时AuthMode必填
            //field.AuthMode = TORA_TSTP_AM_FingerPrint;
            //strcpy(field.DeviceID, "03873902");
            //strcpy(field.CertSerial, "9FAC09383D3920CAEFF039");

            // 终端信息采集
            // UserProductInfo填写终端软件标识，必填，模拟测试也需要填。
            strcpy(field.UserProductInfo, "此处填写信息");
            // DynamicPassword 为该软件的终端动态秘钥，需与UserProductInfo相匹配。必填，模拟测试可以不填。
            strcpy(field.DynamicPassword,"此处填写信息");
            // 按照监管要求填写终端信息。必填，模拟测试也需要填。
            strcpy(field.TerminalInfo, "此处填写信息");
            // 以下内外网IP地址若不填则柜台系统自动采集，若填写则以终端填值为准报送
            //strcpy(field.MacAddress, pConnectionInfoField->MacAddress);
            //strcpy(field.InnerIPAddress, pConnectionInfoField->InnerIPAddress);
            //strcpy(field.OuterIPAddress, pConnectionInfoField->OuterIPAddress);


            int ret = m_api->ReqUserLogin(&field, m_req_id++);
            if (ret != 0)
            {
                printf("TradeApi ReqUserLogin fail, ret[%d]\n", ret);
            }
            
        }
        else
        {
            printf("get connection info fail! error_id[%d] error_msg[%s]\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
    }

    void update_password(){
        // 修改密码  模拟环境不支持修改密码
        CTORATstpUserPasswordUpdateField field;
        memset(&field, 0, sizeof(field));

        strcpy(field.UserID, UserID);
        strcpy(field.OldPassword, Password);
        strcpy(field.NewPassword, "123456");

        int ret = m_api->ReqUserPasswordUpdate(&field, m_req_id++);
        if (ret != 0)
        {
            printf("ReqUserPasswordUpdate fail, ret[%d]\n", ret);
        }
        return;
    }
public:    
    int queryByID(std::string stock_id){
        // Query the position of current stock by id
        TORASTOCKAPI::CTORATstpQryPositionField field;
        memset(&field, 0, sizeof(TORASTOCKAPI::CTORATstpQryPositionField));
        
        // 以下字段不填表示不设过滤条件，即查询所有持仓
        // if (!(stock_id == "all")){
        //     strcpy(field.SecurityID, stock_id.c_str());
        //     query_map_[field.SecurityID] = 0; // waiting for response
        // }
        if (stock_id == "all"){
            position_resp_last = 0;
        }
        else if (stock_id == "shenzhen"){
            field.ExchangeID = '2';
            position_resp_last = 0; // waiting for response
        }
        else if (stock_id == "shanghai"){
            field.ExchangeID = '1';
            position_resp_last = 0; // waiting for response
        }
        else{
            strcpy(field.SecurityID, stock_id.c_str());
            query_map_[field.SecurityID] = 0; // waiting for response
        }

		int ret = -1;
		if(m_api){
        	ret = m_api->ReqQryPosition(&field, m_req_id++);
		}
	
        if (ret == 0){
            return ret;
        }
        else{
            printf("ReqQryPosition fail, ret[%d]\n", ret);
            query_map_[field.SecurityID] = 1;
            return -1;
        }
        
    }

    int queryReqByID(std::string stock_id){
        // 查询报单
        TORASTOCKAPI::CTORATstpQryOrderField field;
        memset(&field, 0, sizeof(field));
        
        // 以下字段不填表示不设过滤条件，即查询所有报单
        strcpy(field.SecurityID, stock_id.c_str());
        //strcpy(field.InsertTimeStart, "09:35:00");
        //strcpy(field.InsertTimeEnd, "10:30:00");

        // IsCancel字段填1表示只查询可撤报单
        // field.IsCancel = 1;
        query_map_[field.SecurityID] = 0; // waiting for response
		// if(m_api){
			int ret = m_api->ReqQryOrder(&field, m_req_id++);
		// }
		// else{
		// 	int ret = 0;
		// 	printf("11111w2");
		// }
        
        if (ret == 0){
            return ret;
        }
        else{
            printf("ReqQryOrder fail, ret[%d]\n", ret);
            query_map_[field.SecurityID] = 1;
            return -1;
        }
    }

    int reqLimitTrade(std::string security_id, const double price, const int volume, const char direction){
        // Direction: '0' buy, '1' sell
        // 请求报单
        TORASTOCKAPI::CTORATstpInputOrderField field_oi;
        memset(&field_oi, 0, sizeof(TORASTOCKAPI::CTORATstpInputOrderField));
        if (security_id[0] == '6'){
            // SH:TORA_TSTP_EXD_SSE, SZ: TORASTOCKAPI::TORA_TSTP_EXD_SZSE
            field_oi.ExchangeID = TORASTOCKAPI::TORA_TSTP_EXD_SSE;
            strcpy(field_oi.ShareholderID, SH_ShareHolderID);
        }
        else if((security_id[0] == '3') || (security_id[0] == '0')){
            // SH:TORA_TSTP_EXD_SSE, SZ: TORASTOCKAPI::TORA_TSTP_EXD_SZSE
            field_oi.ExchangeID = TORASTOCKAPI::TORA_TSTP_EXD_SZSE;
            strcpy(field_oi.ShareholderID, SZ_ShareHolderID);
        }
        
        strcpy(field_oi.SecurityID, security_id.c_str());
        field_oi.Direction = direction;
        field_oi.VolumeTotalOriginal = volume;

        // 上交所支持限价指令和最优五档剩撤、最优五档剩转限两种市价指令，对于科创板额外支持本方最优和对手方最优两种市价指令和盘后固定价格申报指令
        // 深交所支持限价指令和立即成交剩余撤销、全额成交或撤销、本方最优、对手方最优和最优五档剩撤五种市价指令
        // 限价指令和上交所科创板盘后固定价格申报指令需填写报单价格，其它市价指令无需填写报单价格
        // 以下以上交所限价指令为例，其它指令参考开发指南相关说明填写OrderPriceType、TimeCondition和VolumeCondition三个字段:
        field_oi.LimitPrice = price;
        field_oi.OrderPriceType = TORA_TSTP_OPT_LimitPrice;
        field_oi.TimeCondition = TORA_TSTP_TC_GFD;
        field_oi.VolumeCondition = TORA_TSTP_VC_AV;


        // OrderRef为报单引用，类型为整型，该字段报单时为选填
        // 若不填写，则系统会为每笔报单自动分配一个报单引用
        // 若填写，则需保证同一个TCP会话下报单引用严格单调递增，不要求连续递增，至少需从1开始编号
        // field_oi.OrderRef = 1;


        //InvestorID为选填，若填写则需保证填写正确
        //Operway为委托方式，根据券商要求填写，无特殊说明置空即可

        // 终端自定义字段，终端可根据需要填写如下字段的值，该字段值不会被柜台系统修改，在报单回报和查询报单时返回给终端
        //strcpy(field.SInfo, "sinfo");
        //field.IInfo = 678;
        
        //其它字段置空
        
        int ret_oi = m_api->ReqOrderInsert(&field_oi, m_req_id++);
        // int ret_oi = 0;

        // if (ret_oi != 0)
        // {
        //     FILE *fp = fopen("output.txt", "a");
        //     fprintf(fp, "ReqOrderInsert fail, ret[%d]\n", ret_oi);
        // }
        return ret_oi;
    }

    int reqCancelByRefSysID(std::string security_id, std::string refSysID){
        // Direction: '0' buy, '1' sell
        // exchange id - TORASTOCKAPI::TORA_TSTP_EXD_SZSE,  TORA_TSTP_EXD_SSE
        TORASTOCKAPI::CTORATstpInputOrderActionField recall_field;
        memset(&recall_field, 0, sizeof(TORASTOCKAPI::CTORATstpInputOrderActionField));
        if (security_id[0] == '6'){
            // SH:TORA_TSTP_EXD_SSE, SZ: TORASTOCKAPI::TORA_TSTP_EXD_SZSE
            recall_field.ExchangeID = TORASTOCKAPI::TORA_TSTP_EXD_SSE;
        }
        else if((security_id[0] == '3') || (security_id[0] == '0')){
            // SH:TORA_TSTP_EXD_SSE, SZ: TORASTOCKAPI::TORA_TSTP_EXD_SZSE
            recall_field.ExchangeID = TORASTOCKAPI::TORA_TSTP_EXD_SZSE;
        }
        recall_field.ActionFlag = TORA_TSTP_AF_Delete;
        

        // 撤单支持以下两种方式定位原始报单：
        // （1）报单引用方式
        //field.OrderRef = 1;
        //field.FrontID = m_front_id;
        //field.SessionID = m_session_id;
        // （2）系统报单编号方式
        strcpy(recall_field.OrderSysID, refSysID.c_str());


        // OrderActionRef报单操作引用，用法同报单引用，可根据需要选填
        
        // 终端自定义字段，终端可根据需要填写如下字段的值，该字段值不会被柜台系统修改，在查询撤单时返回给终端
        //strcpy(field.SInfo, "sinfo");
        //field.IInfo = 678;

        // 委托方式字段根据券商要求填写，无特殊说明置空即可
        //Operway
        int recall_ret = m_api->ReqOrderAction(&recall_field, m_req_id++);

        // int recall_ret = -1;
        // if ((direction==0) && (cancel_buy_map_[security_id]==0)){
        //  cancel_buy_map_[security_id] =1;
        //  int recall_ret = m_api->ReqOrderAction(&recall_field, m_req_id++);
        // }
        // else if ((direction==1) && (cancel_sell_map_[security_id]==0)){
        //  cancel_sell_map_[security_id] =1;
        //  recall_ret = m_api->ReqOrderAction(&recall_field, m_req_id++);
        // }

        // avoid several same requests
        // auto it = std::find(query_trade_ref_vector_map_[security_id].begin(), query_trade_ref_vector_map_[security_id].end(), refrSysID);
        // if (it != query_trade_ref_vector_map_[security_id].end()){
        //  query_trade_ref_vector_map_[security_id].erase(it);
        // }
        // if (recall_ret != 0)
        // {
            // if (direction==0){
            //  cancel_buy_map_[security_id] =0;
            // }
            // else if (direction==1){
            //  cancel_sell_map_[security_id] =0;
            // }
        //  printf("ReqOrderAction fail, ret[%d]\n", recall_ret);
        // }
        return recall_ret;
    }
private:
    void OnRspUserLogin(TORASTOCKAPI::CTORATstpRspUserLoginField *pRspUserLoginField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo,
     int nRequestID)
    {
        FILE *fp = fopen("output.txt", "a");
        fprintf(fp, "---------------------\nStart...\n");
        if (pRspInfo->ErrorID == 0)
        {
            printf("TradeApi OnRspUserLogin: OK! [%d]\n", nRequestID); 
            login_Status = 1;
            m_front_id = pRspUserLoginField->FrontID;
            m_session_id = pRspUserLoginField->SessionID;
       
        }
        else
        {
            fprintf(fp, "TradeApi OnRspUserLogin: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);

    }

    virtual void OnRspUserPasswordUpdate(CTORATstpUserPasswordUpdateField *pUserPasswordUpdateField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        if (pRspInfo->ErrorID == 0)
        {
            printf("OnRspUserPasswordUpdate: OK! [%d]\n", nRequestID);
        }
        else
        {
            printf("OnRspUserPasswordUpdate: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
    }
    
    virtual void OnRspOrderInsert(CTORATstpInputOrderField *pInputOrderField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        // FILE *file = fopen("/home/liuhonghao/Documents/Github/Market.v.03/out.txt", "a");  // Open file in append mode
        if (pRspInfo->ErrorID == 0)
        {
            printf("Trade RESPONSE: OnRspOrderInsert: OK! [%d] [%d] [%s]\n", nRequestID, pInputOrderField->OrderRef, pInputOrderField->OrderSysID);
        }
        else
        {
            FILE *file = fopen("out.txt", "a");  // Open file in append mode
            fprintf(file, "Trade OnRspOrderInsert: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
            fclose(file);
        }
        // fclose(file);
        // printf("insert rep out...\n");
    }

    virtual void OnRspOrderAction(CTORATstpInputOrderActionField *pInputOrderActionField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        // FILE *fp = fopen("output.txt", "a");
        if (pRspInfo->ErrorID == 0)
        {
            // query_trade_ref_vector_map_
            printf("OnRspOrderAction: OK! [%d] [%d] [%s] \n", nRequestID, pInputOrderActionField->OrderActionRef, pInputOrderActionField->CancelOrderSysID);
        }
        else
        {
            printf("OnRspOrderAction: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        // fclose(fp);
    }

    virtual void OnRspInquiryJZFund(CTORATstpRspInquiryJZFundField *pRspInquiryJZFundField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        if (pRspInfo->ErrorID == 0)
        {
            printf("OnRspInquiryJZFund: OK! [%d] [%.2f] [%.2f]\n", nRequestID, pRspInquiryJZFundField->UsefulMoney, pRspInquiryJZFundField->FetchLimit);
        }
        else
        {
            printf("OnRspInquiryJZFund: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
    }

    virtual void OnRspTransferFund(CTORATstpInputTransferFundField *pInputTransferFundField, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID)
    {
        if (pRspInfo->ErrorID == 0)
        {
            printf("OnRspTransferFund: OK! [%d] [%d]", nRequestID, pInputTransferFundField->ApplySerial);
        }
        else
        {
            printf("OnRspTransferFund: Error! [%d] [%d] [%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
    }

    virtual void OnRtnTransferFund(CTORATstpTransferFundField *pTransferFund)
    {
        printf("OnRtnTransferFund: FundSerial[%d] ApplySerial[%d] FrontID[%d] SessionID[%u] DepartmentID[%s] AccountID[%s] CurrencyID[%c] TransferDirection[%c] Amount[%.2f] TransferStatus[%c] OperateTime[%s]",
            pTransferFund->FundSerial, pTransferFund->ApplySerial, pTransferFund->FrontID, pTransferFund->SessionID,
            pTransferFund->DepartmentID, pTransferFund->AccountID, pTransferFund->CurrencyID, pTransferFund->TransferDirection,
            pTransferFund->Amount, pTransferFund->TransferStatus, pTransferFund->OperateTime);
    }

    virtual void OnRtnOrder(CTORATstpOrderField *pOrder)
    {
        FILE *fp = fopen("output.txt", "a");
        fprintf(fp,
            "OnRtnOrder:::\n"
            "---RequestID[%d] SecurityID[%s] OrderRef[%d] OrderLocalID[%s] OrderSysID[%s]\n"
            "---OrderType[%c] LimitPrice[%.2f]\n"
            "---OrderStatus[%c] StatusMsg[%s] OrderSubmitStatus[%c]\n"
            "---VolumeTotalOriginal[%d] VolumeTraded[%d] VolumeCanceled[%d]\n"
            "---InsertUser[%s] InsertDate[%s] InsertTime[%s] AcceptTime[%s]\n"
            "---CancelUser[%s] CancelTime[%s]"
            "---PbuID[%s]"
            "\n"
            , pOrder->RequestID, pOrder->SecurityID, pOrder->OrderRef, pOrder->OrderLocalID, pOrder->OrderSysID
            , pOrder->OrderType, pOrder->LimitPrice
            , pOrder->OrderStatus, pOrder->StatusMsg, pOrder->OrderSubmitStatus
            , pOrder->VolumeTotalOriginal, pOrder->VolumeTraded, pOrder->VolumeCanceled
            , pOrder->InsertUser, pOrder->InsertDate, pOrder->InsertTime, pOrder->AcceptTime
            , pOrder->CancelUser, pOrder->CancelTime
            , pOrder->PbuID
            );
        
        //撤单测试
        #if 0
            // 请求撤单  交易所已接收
            if(TORA_TSTP_OST_Accepted==pOrder->OrderStatus && TORA_TSTP_OSS_InsertSubmitted==pOrder->OrderSubmitStatus)
            {

                CTORATstpInputOrderActionField field;
                memset(&field, 0, sizeof(CTORATstpInputOrderActionField));
                
                field.ExchangeID = pOrder->ExchangeID;
                field.ActionFlag = TORA_TSTP_AF_Delete;
                

                // 撤单支持以下两种方式定位原始报单：
                // （1）报单引用方式
                //field.OrderRef = 1;
                //field.FrontID = m_front_id;
                //field.SessionID = m_session_id;
                // （2）系统报单编号方式
                strcpy(field.OrderSysID, pOrder->OrderSysID);


                // OrderActionRef报单操作引用，用法同报单引用，可根据需要选填
                
                // 终端自定义字段，终端可根据需要填写如下字段的值，该字段值不会被柜台系统修改，在查询撤单时返回给终端
                //strcpy(field.SInfo, "sinfo");
                //field.IInfo = 678;

                // 委托方式字段根据券商要求填写，无特殊说明置空即可
                //Operway
                
                int ret = m_api->ReqOrderAction(&field, m_req_id++);
                if (ret != 0)
                {
                    printf("ReqOrderAction fail, ret[%d]\n", ret);
                }
            } //end if
            #endif
        fclose(fp);

    }

    virtual void OnRtnTrade(CTORATstpTradeField *pTrade)
    {
        FILE *fp = fopen("output.txt", "a");
        fprintf(fp,"OnRtnTrade: TradeID[%s] InvestorID[%s] SecurityID[%s] OrderRef[%d] OrderLocalID[%s] Price[%.2f] Volume[%d]\n",
            pTrade->TradeID, pTrade->InvestorID, pTrade->SecurityID, pTrade->OrderRef, pTrade->OrderLocalID, pTrade->Price, pTrade->Volume);
        fclose(fp);

    }

    virtual void OnRtnMarketStatus(CTORATstpMarketStatusField *pMarketStatus)
    {
        FILE *fp = fopen("output.txt", "a");
        fprintf(fp,"OnRtnMarketStatus: MarketID[%c] MarketStatus[%c]\n", pMarketStatus->MarketID, pMarketStatus->MarketStatus);
        fclose(fp);

    }

    virtual void OnRspQrySecurity(CTORATstpSecurityField *pSecurity, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        FILE *fp = fopen("output.txt", "a");

        if (pSecurity)
        {
            fprintf(fp,"OnRspQrySecurity[%d]: SecurityID[%s] SecurityName[%s] MarketID[%c] OrderUnit[%c] OpenDate[%s] UpperLimitPrice[%.2f] LowerLimitPrice[%.2f]\n",
                nRequestID, pSecurity->SecurityID, pSecurity->SecurityName, pSecurity->MarketID, pSecurity->OrderUnit,
                pSecurity->OpenDate, pSecurity->UpperLimitPrice, pSecurity->LowerLimitPrice);
        }
        if (bIsLast)
        {
            fprintf(fp,"Query contract end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);
    }

    virtual void OnRspQryInvestor(CTORATstpInvestorField *pInvestor, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        FILE *fp = fopen("output.txt", "a");
        if (pInvestor)
        {
            fprintf(fp,"OnRspQryInvestor[%d]: InvestorID[%s] InvestorName[%s] Operways[%s]\n", nRequestID, pInvestor->InvestorID, pInvestor->InvestorName, pInvestor->Operways);
        }

        if (bIsLast)
        {
            fprintf(fp,"Query investor end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);
    }

    virtual void OnRspQryShareholderAccount(CTORATstpShareholderAccountField *pShareholderAccount, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        FILE *fp = fopen("output.txt", "a");
        if (pShareholderAccount)
        {
            fprintf(fp,"OnRspQryShareholderAccount[%d]: InvestorID[%s] ExchangeID[%c] ShareholderID[%s]\n", 
                nRequestID, 
                pShareholderAccount->InvestorID, 
                pShareholderAccount->ExchangeID, 
                pShareholderAccount->ShareholderID);
        }

        if (bIsLast)
        {
            fprintf(fp,"Query investor account end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);
    }

    virtual void OnRspQryTradingAccount(CTORATstpTradingAccountField *pTradingAccount, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        FILE *fp = fopen("output.txt", "a");
        
        if (pTradingAccount)
        {
            fprintf(fp,"OnRspQryTradingAccount[%d]: DepartmentID[%s] InvestorID[%s] AccountID[%s] CurrencyID[%c] UsefulMoney[%.2f] FetchLimit[%.2f]\n", nRequestID, 
                pTradingAccount->DepartmentID, pTradingAccount->InvestorID, pTradingAccount->AccountID, pTradingAccount->CurrencyID,
                pTradingAccount->UsefulMoney, pTradingAccount->FetchLimit);
        }

        if (bIsLast)
        {
            fprintf(fp,"Query trading account fund end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);
    }

    virtual void OnRspQryOrder(CTORATstpOrderField *pOrder, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        // FILE *fp = fopen("output.txt", "a");
        // std::string security_id = "";
        if (pOrder)
        {
            // query_trade_map_[pOrder->SecurityID] = query_trade_map_[pOrder->SecurityID]+pOrder->OrderSysID+" ";
            // security_id = pOrder->SecurityID;
            // printf("sid %s\n",security_id.c_str());

            // printf("%s\n",query_trade_map_[pOrder->SecurityID].c_str());
            // printf("%d\n",query_map_[pOrder->SecurityID]);
            switch(query_trade_option_map_[pOrder->SecurityID]){
                // Direction 0 buy, 1 sell
                case 1:
                    printf(
                        " OnRspQryOrder[%d]:SecurityID[%s] OrderLocalID[%s] OrderRef[%d] OrderSysID[%s] VolumeTraded[%d] OrderStatus[%c] OrderSubmitStatus[%c] StatusMsg[%s] Direction[%c]\n",
                        nRequestID,
                        pOrder->SecurityID,
                        pOrder->OrderLocalID, pOrder->OrderRef, pOrder->OrderSysID, pOrder->VolumeTraded,
                        pOrder->OrderStatus, pOrder->OrderSubmitStatus, pOrder->StatusMsg, pOrder->Direction);
                    break;
                case 2: // cancel buy order
                    //get buy order
                    if ((pOrder->Direction=='0')&&((pOrder->OrderStatus=='2')||(pOrder->OrderStatus=='3'))){
                        // check if ref id not in cancel vector of security id
                        // printf("+++++\n");
                        // auto it = std::find(query_trade_ref_vector_map_[pOrder->SecurityID].begin(), query_trade_ref_vector_map_[pOrder->SecurityID].end(), pOrder->OrderSysID);
                        // if (it == query_trade_ref_vector_map_[pOrder->SecurityID].end()){
                            //  cancel buy by ref
                            // query_trade_ref_vector_map_[pOrder->SecurityID].push_back(pOrder->OrderSysID);
                            int ret = reqCancelByRefSysID(pOrder->SecurityID, pOrder->OrderSysID);
                            if (ret==0){
                                printf("撤单请求成功 SecurityID[%s] RefSysID[%s] Direction[%c]\n", pOrder->SecurityID, pOrder->OrderSysID, pOrder->Direction);
                            }
                            else{
                                printf("撤单请求失败 SecurityID[%s] RefSysID[%s] Direction[%c]\n", pOrder->SecurityID, pOrder->OrderSysID, pOrder->Direction);
                            }
                            // cancel reponse remove ref from vector
                        // }
                        
                    }
                    
                    break;
                case 3: // cancel sell order
                    if ((pOrder->Direction=='1')&&((pOrder->OrderStatus=='2')||(pOrder->OrderStatus=='3'))){
                        // check if ref id not in cancel vector of security id
                        
                        // auto it = std::find(query_trade_ref_vector_map_[pOrder->SecurityID].begin(), query_trade_ref_vector_map_[pOrder->SecurityID].end(), pOrder->OrderSysID);
                        // if (it == query_trade_ref_vector_map_[pOrder->SecurityID].end()){
                            //  cancel buy by ref
                            // query_trade_ref_vector_map_[pOrder->SecurityID].push_back(pOrder->OrderSysID);
                            int ret = reqCancelByRefSysID(pOrder->SecurityID, pOrder->OrderSysID);
                            if (ret==0){
                                printf("撤单请求成功 SecurityID[%s] RefSysID[%s] Direction[%c]\n", pOrder->SecurityID, pOrder->OrderSysID, pOrder->Direction);
                            }
                            else{
                                printf("撤单请求失败 SecurityID[%s] RefSysID[%s] Direction[%c]\n", pOrder->SecurityID, pOrder->OrderSysID, pOrder->Direction);
                            }
                            // cancel reponse remove ref from vector
                        // }
                        
                    }
                    break;
            }
            
        }

        if (bIsLast)
        {
            // printf("Order end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        // fclose(fp);
    }

    virtual void OnRspQryPosition(CTORATstpPositionField *pPosition, TORASTOCKAPI::CTORATstpRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
    {
        // get volume
        FILE *fp = fopen("output.txt", "a");

        if (pPosition)
        {
            // if (unordered_map[pPosition->SecurityID]){
            //     delete unordered_map[pPosition->SecurityID];
            // }
            postion_map_[pPosition->SecurityID] = pPosition;
            avai_postion_map_[pPosition->SecurityID] = pPosition->AvailablePosition;
            query_map_[pPosition->SecurityID] = 1;
            printf("RESPONSE: OnRspQryPosition[%d]: InvestorID[%s] SecurityID[%s] HistoryPos[%d] TodayBSPos[%d] TodayPRPos[%d] AvailablePosition[%d] CurrentPosition[%d]\n", nRequestID, pPosition->InvestorID, pPosition->SecurityID, pPosition->HistoryPos, pPosition->TodayBSPos, pPosition->TodayPRPos,pPosition->AvailablePosition, pPosition->CurrentPosition);
        }

        if (bIsLast)
        {
            position_resp_last = 1;
            fprintf(fp,"Query position end[%d] ErrorID[%d] ErrorMsg[%s]\n", nRequestID, pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        }
        fclose(fp);
    }
public:
    int get_position_info_by_id(std::string stock_id){
        
        if (query_map_[stock_id]){
            // position_p = postion_map_[stock_id];
            return 0;
        }
        return -1;
    }
    int get_login_status(){
        return login_Status;
    }

    int get_init_positions(int exchange_id){
        // exchange id 1: shanghai, 2: shenzhen
        int ret = -1;
        if (exchange_id == 1){
            ret = queryByID("shanghai");
        }
        else if (exchange_id == 2){
            ret = queryByID("shenzhen");
        }
        else {
            ret = queryByID("all");
        }
        
        if (ret == 0){
            printf("查询所有持仓请求成功...\n");
        }
        else{
            printf("查询所有持仓请求失败...\n");
            return 1;
        }
        // waiting for query response
        auto start = std::chrono::high_resolution_clock::now();
        while(position_resp_last == 0){
            auto end = std::chrono::high_resolution_clock::now();

            // Calculate the elapsed time in milliseconds
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
            // printf("%d T: %d\n",_tradeApi->get_position_info_by_id(code_, position_p),elapsed.count());
            if (elapsed.count() > 1000){
                printf("Fail to query, high latency issue.");
                ret = 0;
                return 2;
            }
        }
        // print all code and position
        printf("Initial position information:\n");
        for (const auto& pair : avai_postion_map_) {
            std::cout << pair.first << ": " << pair.second << '\n';
        }
        return 0;
    }
    // std::string get_ref_system_id(std::string security_id){
    //  return query_trade_map_[security_id];
    // }
    
private:
    CTORATstpTraderApi *m_api;
    int m_req_id;
    int m_front_id;
    int m_session_id;
    const char *InvestorID;   //投资者账户 
    const char *UserID;    //操作员账户 //同客户号保持一致即可
    const char *AccountID;      //以Req(TradingAccount)查询的为准//资金账户 
    const char *Password;       //N视界注册模拟账号的交易密码，不是登录密码//登陆密码
    const char *SH_ShareHolderID;   //以Req(ShareholderAccount)查询的为准//上海交易所股东账号
    const char *SZ_ShareHolderID;   //以Req(ShareholderAccount)查询的为准//深圳交易所股东账号
    const char *BJ_ShareHolderID;//北京交易所股东账号
    const char *DepartmentID;       //默认客户号的前4位
    int login_Status;
};