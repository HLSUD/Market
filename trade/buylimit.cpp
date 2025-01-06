#include "buylimit.h"
#include <chrono>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <sys/stat.h>

#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

inline std::string getCurrentDate() {
    // 获取当前时间
    std::time_t now = std::time(nullptr);
    std::tm* local_time = std::localtime(&now);

    // 创建一个字符数组来存储日期字符串
    char date_str[11]; // "YYYY-MM-DD" 最多需要10个字符加上一个空字符

    // 使用 sprintf 格式化日期
    // 注意：这里使用 snprintf 可以更安全地避免缓冲区溢出，但在这个例子中我们知道数组大小足够
    std::sprintf(date_str, "%04d%02d%02d",
                 local_time->tm_year + 1900, // tm_year 是从1900年开始计数的
                 local_time->tm_mon + 1,    // tm_mon 是从0开始计数的（0=一月，11=十二月）
                 local_time->tm_mday);

    // 返回格式化后的日期字符串
    return std::string(date_str);
}

// 获取当前日期并以 YYYYMMDD 格式返回
//inline std::string getCurrentDate() {

//}

// 创建目录的函数
inline bool createDirectory(const std::string& path) {
	// 使用 mkdir 函数创建目录
	int status = mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (status == 0) {
		std::cout << "Directory created: " << path << std::endl;
		return true;
	}

	std::cerr << "Failed to create directory: " << path << std::endl;
	return false;
}

void buylimit::Init(int buyLimitCnt) {
	auto v = _bInit.load();
	if (_bInit.compare_exchange_strong(v, true)) {
		_fileName = "./gtdata/" + getCurrentDate() + ".dat";
		createDirectory("gtdata");
		loadFromFile(_orderCnt, _buyCnt, _fileName);
		_buyLimitCnt = buyLimitCnt;
	}
}

bool buylimit::buyRequest(const std::string& mkt, const std::string& sccode) {
	//auto symbol = mkt + sccode;
	auto symbol = sccode;
	_mtx.lock();
	if (_buyCnt < _buyLimitCnt || _buyLimitCnt == 0) {
		_buyCnt++;
		auto iter = _orderCnt.find(symbol);
		if (iter != _orderCnt.end()) {
			iter->second++;
		} else {
			_orderCnt.insert({ symbol, 1 });
		}
		_mtx.unlock();

		return true;
	}
	_mtx.unlock();

	return false;
}

// Function to save data to a file
void buylimit::saveToFile(const std::map<std::string, int>& myMap, int myInt, const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error: Unable to open file for writing.\n";
		return;
	}

	// Save the integer first
	file << myInt << "\n";

	// Save the size of the map
	file << myMap.size() << "\n";
	for (const auto& pair : myMap) {
		file << pair.first << " " << pair.second << "\n";
	}

	file.close();
}

// Function to load data from a file
bool buylimit::loadFromFile(std::map<std::string, int>& myMap, int& myInt, const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}

	// Load the integer
	//买入次数汇总
	file >> myInt;

	// Load the map
	size_t size;
	file >> size;
	std::string key;
	int value;
	myMap.clear();
	for (size_t i = 0; i < size; ++i) {
		file >> key >> value;
		myMap[key] = value;
	}

	file.close();
	return true;
}
int buylimit::getOrderCnt(const std::string& mkt, const std::string& sccode) {
	auto symbol = mkt + sccode;
	auto iter   = _orderCnt.find(symbol);
	if (iter != _orderCnt.end()) {
		return iter->second;
	}

	return 0;
}

// 测量函数执行时间的模板
template<typename Func, typename... Args>
long long measureExecutionTime(Func func, Args&&... args) {
	auto start = std::chrono::high_resolution_clock::now(); // 获取开始时间点
	func(std::forward<Args>(args)...);                      // 调用函数
	auto end = std::chrono::high_resolution_clock::now();   // 获取结束时间点

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return duration.count(); // 返回耗时，以毫秒为单位
}

void buylimit::flush() {
	if (_buyLimitCnt > 0) {
		auto start = std::chrono::high_resolution_clock::now(); // 获取开始时间点
		saveToFile(_orderCnt, _buyCnt, _fileName);
		auto end      = std::chrono::high_resolution_clock::now(); // 获取结束时间点
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << "Time taken for task: " << duration.count() << " ms" << std::endl;
	}
}
