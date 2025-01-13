#pragma once
#include <vector>
#include <string>

class Stock{

    protected:
        std::string stock_id;
        double market_cap;
        double price_limit;

    public:
    Stock(const std::string& col1 = "", double col2 = 0.0, double col3 = 0.0)
        : stock_id(col1), market_cap(col2), price_limit(col3) {};
    
    std::string get_stock_id();
    double get_price_limit();
    double get_cap();
};

void loadCSV(const std::string& filename, std::vector<Stock>& data);