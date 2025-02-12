To build project it is need to run from root dir
cmake -DBOOST_ROOT=/opt/homebrew/include -S. -B ./build

And then run 
cmake --build ./build

To start server
./build/src/server/server 10001  

To start client
./build/src/client/client 127.0.0.1 10001  
