To build project it is need to run from root dir:
```
cmake -DBOOST_ROOT=/opt/homebrew/include -S. -B ./build
```

And then run:
```
cmake --build ./build
```
To start server:
```
./build/src/server/server --port 10001
```
or to start ssl server
```
./build/src/server/server --port 11111 --ssl --key sslkeys/private.key --cert sslkeys/selfsigned.crt
```

To start client:
```
./build/src/client/client --host localhost --port 10001
```
or to activate ssl connection
```
./build/src/client/client --host localhost --port 11111 --ssl --cert sslkeys/selfsigned.crt --userid 123
```
