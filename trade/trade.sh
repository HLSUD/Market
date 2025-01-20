# export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
# g++ demo_trade_stock.cpp -o demo -L. -lfasttraderapi
# ./demo

rm -r build
mkdir build
cd build
cmake ..
make 
./main