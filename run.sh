rm -r build
mkdir build
cd build
cmake ..
make 
exchange_id=2
./main ${exchange_id}