#include "rwqueue/KsTool.h"
#include <string>
#include "BseExanicStruct.h"
#include "SseExanicStruct.h"
#include "SzseExanicStruct.h"
#include "KsHSInterfaceEx.h"
#include <unordered_map>
#include <string>

using namespace istone::base;

namespace
{
    struct STRUCTSIZE
    {
        char type;
        uint16_t  size;
    };
    struct STRUCTSIZE typeSize[] = {
        //sh
        {'a', 64},
        {'b', 64},
        {'c', sizeof(SseIndex)},
        {'d', sizeof(SseDepth)},
        {'e', sizeof(SseDepth)},
        {'f', sizeof(SseDepthFifty)},
        {'g', sizeof(SseOption)},
        {'p', sizeof(SseOrderQueue)},
        {'x', sizeof(SseOrderQueueErr)},
        {'i', sizeof(SseIOPV)},
        {'z', sizeof(SseRealtimeIndex)},
        //{'r', sizeof(SseOrderbookSnapAT)},
        //{'s', sizeof(SseOrderbookSnapErr)},
        {'l', sizeof(SseIndex)},
        {'m', sizeof(SseDepth)},
        {'n', sizeof(SseDepth)},
        {'o', sizeof(SseOption)},
        //sz
        {'A', sizeof(SzseTradeStatics)},
        {'B', sizeof(SzseIndex)},
        {'C', 64},
        {'D', 64},
        {'E', sizeof(SzseDepth)},
        {'F', sizeof(SzseDepthFifty)},
        {'P', sizeof(SzseOrderQueue)},
        {'Q', sizeof(SzseOrderQueueCage)},
        {'X', sizeof(SzszOrderQueueErr)},
        {'I', sizeof(SzseIOPV)},
        {'Z', sizeof(SzseRealtimeIndex)},
        //{'R', sizeof(SzseOrderbookSnapAT)},
        //{'S', sizeof(SzseOrderbookSnapErr)},

        //bj
        {'J', sizeof(BseIndex)},
        {'K', sizeof(BseDepth)},
    };
}

uint16_t KsTool::getTypeSize(char type)
{
    static std::unordered_map<char, uint16_t> map_;
    if (map_.empty())
    {
        for (int i = 0; i < sizeof(typeSize) / sizeof(typeSize[0]); ++i)
        {
            map_[typeSize[i].type] = typeSize[i].size;
        }
        return -1;
    }
    else
    {
        return map_[type];
    }
}

std::string KsTool::getCode(const char* data)
{
    using namespace istone_hs;
    std::string code = "";
    char type = data[0];
    switch (type)
    {
    //sh
    case sseEntrustType:
        code = mystr2(((SseEntrust*)data)->SecurityID);
        break;
    case sseTradeType:
        code = mystr2(((SseTrade*)data)->SecurityID);
        break;
    case sseDepthFiftyType:
        code = mystr2(((SseDepthFifty*)data)->SecurityID);
        break;
    case sseDepthType0:
        code = mystr2(((SseDepth*)data)->SecurityID);
        break;
    case sseDepthType1:
        code = mystr2(((SseDepth*)data)->SecurityID);
        break;
    //todo
    //sz
    case szseEntrustType:
        code = mystr2(((SzseEntrust*)data)->SecurityID);
        break;
    case szseTradeType:
        code = mystr2(((SzseTrade*)data)->SecurityID);
        break;
    case szseDepthFiftyType:
        code = mystr2(((SzseDepthFifty*)data)->SecurityID);
        break;
    case szseDepthOrOptionType:
        code = mystr2(((SzseDepth*)data)->SecurityID);
        break;
    }
    return code;
}