
#include <iostream>
#include <fstream>
#include <sstream>
#include "stock.h"

std::string Stock::get_stock_id(){
    return stock_id;
}

double Stock::get_price_limit(){
    return price_limit;
}
double Stock::get_cap(){
    return market_cap;
}

void loadCSV(const std::string& filename, std::vector<Stock>& data) {
    std::string filePath = __FILE__; // Full path of the current file
    size_t lastSlash = filePath.find_last_of("/\\");
    filePath = filePath.substr(0, lastSlash+1);
    filePath = filePath + filename;
    std::ifstream file(filePath);
    // std::cout << "Current file path: "<<filename << filePath << std::endl;
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line);
    int k = 6;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string col1;
        std::string col2Str, col3Str;
        
        // Read each column
        if (std::getline(lineStream, col1, ',') &&
            std::getline(lineStream, col2Str, ',') &&
            std::getline(lineStream, col3Str, ',')) {
            // Convert strings to double
            double col2 = std::stod(col2Str);
            double col3 = std::stod(col3Str);

            // Add to the data vector
            data.push_back({col1.substr(0, k), col2, col3});
        }
    }

    file.close();
}
