[gRPC based calculator app ](http://github.com/PrateekJoshi/grpc_calculator)
===================================

### Calculator service 

The calculator service is defined in .proto format at [calculator.proto](protos/calculator.proto). 

### Client and server API implementations

The client implementation is at [CalculatorClient.cc](calculator/CalculatorClient.cc).

The server implementation is at [CalculatorServer.cc](calculator/CalculatorServer.cc).

# Building the client and server

```sh
$ make
```

# Running cliet and server

Run server in first terminal as,

```sh
$ ./CalculatorServer
```

Run client in another terminal,

```sh
$ ./CalculatorClient
```
