#ifndef BUYLIMIT_H
#define BUYLIMIT_H
#include <atomic>
#include <map>
#include <mutex>
#include <thread>

class buylimit {
public:
 	buylimit(){ _bInit.store(false);}
	~buylimit() = default;
	void Init(int buyLimitCnt);
	bool buyRequest(const std::string& mkt, const std::string& sccode);
	void saveToFile(const std::map<std::string, int>& myMap, int myInt, const std::string& filename);
	bool loadFromFile(std::map<std::string, int>& myMap, int& myInt, const std::string& filename);
	int getOrderCnt(const std::string& mkt, const std::string& sccode);
	void flush();

private:
	std::mutex _mtx;
	std::string _fileName;
	int _buyLimitCnt         = 0;
	int _buyCnt              = 0;
	std::atomic<bool> _bInit;
	std::map<std::string, int> _orderCnt;
};

#endif //BUYLIMIT_H
