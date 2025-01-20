#include <string>
#include <unordered_map>
// #include <string>
// #include "BseExanicStruct.h"
// #include "SseExanicStruct.h"
// #include "SzseExanicStruct.h"
#include "rwqueue/KsTool.h"
#include "TORATstpLev2ApiStruct.h"
#include "Lev2Struct_Extension.h"
// #include "KsHSInterfaceEx.h"


namespace
{
    #define mystr2(x)  std::string(x, sizeof(x)).c_str()

    struct STRUCTSIZE
    {
        char type;
        uint16_t  size;
    };
    struct STRUCTSIZE typeSize[] = {
        //sh
        {'a', sizeof(TORALEV2API_V2::SHSseNGTS)},
        {'t', sizeof(TORALEV2API_V2::SHSseNGTS)},
        {'s', sizeof(TORALEV2API_V2::SeSnapshot)},
        // {'c', sizeof(TORALEV2API_V2::SseIndex)},
        // {'d', sizeof(TORALEV2API_V2::SseDepth)},
        // {'e', sizeof(TORALEV2API_V2::SseDepth)},
        // {'f', sizeof(TORALEV2API_V2::SseDepthFifty)},
        // {'g', sizeof(TORALEV2API_V2::SseOption)},
        // {'p', sizeof(TORALEV2API_V2::SseOrderQueue)},
        // {'x', sizeof(TORALEV2API_V2::SseOrderQueueErr)},
        // {'i', sizeof(TORALEV2API_V2::SseIOPV)},
        // {'z', sizeof(TORALEV2API_V2::SseRealtimeIndex)},
        // {'w', sizeof(TORALEV2API::CTORATstpLev2NGTSTickField)},

        // //{'r', sizeof(SseOrderbookSnapAT)},
        // //{'s', sizeof(SseOrderbookSnapErr)},
        // {'l', sizeof(TORALEV2API_V2::SseIndex)},
        // {'m', sizeof(TORALEV2API_V2::SseDepth)},
        // {'n', sizeof(TORALEV2API_V2::SseDepth)},
        // {'o', sizeof(TORALEV2API_V2::SseOption)},
        // //sz
        {'A', sizeof(TORALEV2API_V2::SzseEntrust)},
        {'T', sizeof(TORALEV2API_V2::SzseTrade)},
        {'S', sizeof(TORALEV2API_V2::SeSnapshot)},
        // {'B', sizeof(TORALEV2API_V2::SzseIndex)},
        // {'C', 64},
        // {'D', 64},
        // {'E', sizeof(TORALEV2API_V2::SzseDepth)},
        // {'F', sizeof(TORALEV2API_V2::SzseDepthFifty)},
        // {'P', sizeof(TORALEV2API_V2::SzseOrderQueue)},
        // {'Q', sizeof(TORALEV2API_V2::SzseOrderQueueCage)},
        // {'X', sizeof(TORALEV2API_V2::SzszOrderQueueErr)},
        // {'I', sizeof(TORALEV2API_V2::SzseIOPV)},
        // {'Z', sizeof(TORALEV2API_V2::SzseRealtimeIndex)},
        //{'R', sizeof(SzseOrderbookSnapAT)},
        //{'S', sizeof(SzseOrderbookSnapErr)},

        //bj
        // {'J', sizeof(BseIndex)},
        // {'K', sizeof(BseDepth)},
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
    std::string code = "";
    char type = data[0];
    // printf("Type %c\n",type);

    switch (type)
    {
        //sh
        case TORALEV2API_V2::sseEntrustType:
            code = mystr2(((TORALEV2API_V2::SHSseNGTS*)data)->SecurityID);
            break;
        case TORALEV2API_V2::sseTradeType:
            code = mystr2(((TORALEV2API_V2::SHSseNGTS*)data)->SecurityID);
            break;
        case TORALEV2API_V2::sseSnapshotType:
            code = mystr2(((TORALEV2API_V2::SeSnapshot*)data)->SecurityID);
            break;
        // case sseDepthFiftyType:
        //     code = mystr2(((SseDepthFifty*)data)->SecurityID);
        //     break;
        // case sseDepthType0:
        //     code = mystr2(((SseDepth*)data)->SecurityID);
        //     break;
        // case sseDepthType1:
        //     code = mystr2(((SseDepth*)data)->SecurityID);
        //     break;
        // //todo
        //sz
        case TORALEV2API_V2::szseEntrustType:
            code = mystr2(((TORALEV2API_V2::SzseEntrust*)data)->SecurityID);
            // printf("Entrust Code %s %c\n",code.c_str(),type);
            break;
        case TORALEV2API_V2::szseTradeType:
            code = mystr2(((TORALEV2API_V2::SzseTrade*)data)->SecurityID);
            // printf("Trade Code %s\n",code.c_str());
            break;
        case TORALEV2API_V2::szseSnapshotType:
            code = mystr2(((TORALEV2API_V2::SeSnapshot*)data)->SecurityID);
            break;
        // case szseDepthFiftyType:
        //     code = mystr2(((SzseDepthFifty*)data)->SecurityID);
        //     break;
        // case szseDepthOrOptionType:
        //     code = mystr2(((SzseDepth*)data)->SecurityID);
        //     break;
    }
    return code;
}