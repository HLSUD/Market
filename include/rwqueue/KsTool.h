#pragma once
#include <stdint.h>
#include <string>

class KsTool
{
public:
    static uint16_t getTypeSize(char type);

    static std::string getCode(const char* data);    

};