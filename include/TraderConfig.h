#pragma once
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

enum TradeType
{
    tradeQuery = (char)'q',         // Query
    tradeLimitBuy = (char)'b',           // Price limit buy
    tradeLimitSellAll = (char)'s',        // Price limit sell all
    tradeCancel = (char)'c',    // Cancel
};

class TraderConfig
{
public:

    const char *InvestorID = "00030557";   //投资者账户 
    const char *UserID = "00032967";	   //操作员账户 //同客户号保持一致即可

    //资金账户 
    const char *AccountID = "00032967";		//以Req(TradingAccount)查询的为准
    //登陆密码
    const char *Password = "53114834";		//N视界注册模拟账号的交易密码，不是登录密码

    //上海交易所股东账号
    const char *SH_ShareHolderID = "A00032967";	//以Req(ShareholderAccount)查询的为准
    //深圳交易所股东账号
    const char *SZ_ShareHolderID = "700032967";	//以Req(ShareholderAccount)查询的为准
    //北京交易所股东账号
    const char *BJ_ShareHolderID = "B00032967";

    const char *DepartmentID = "0003";		//默认客户号的前4位

    int64_t BuyLimitNum = 0;
    // std::string stock_id;
    
    // bool init(tinyxml2::XMLElement* nodeTrader)
    // {
    //     CustId = nodeTrader->FirstChildElement("custId")->GetText();
    //     FundAccountId = nodeTrader->FirstChildElement("fundAccountID")->GetText();
    //     BranchId = nodeTrader->FirstChildElement("branchId")->GetText();
    //     AccountId = nodeTrader->FirstChildElement("accountId")->GetText();
    //     std::string marketid = nodeTrader->FirstChildElement("marketId")->GetText();
    //     Password = nodeTrader->FirstChildElement("password")->GetText();
    //     MarketId = std::stoi(marketid.c_str());
    //     BuyLimitNum = std::stoull(nodeTrader->FirstChildElement("buyLimit")->GetText());
    //     if (MarketId >  ATPMarketIDConst::kBeiJing || MarketId <  ATPMarketIDConst::kShangHai)
    //     {
    //         std::cerr << "error marketId." << MarketId << std::endl;
    //         return false;
    //     }
    //     return true;
    // }

    static TraderConfig& instance()
    {
        static TraderConfig config;
        return config;
    }
};