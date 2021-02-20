HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)
CXX = g++
CPPFLAGS += `pkg-config --cflags protobuf grpc`
CXXFLAGS += -std=c++11 -I/root/.local/include/
ifeq ($(SYSTEM),Darwin)
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -lgrpc++_reflection\
           -ldl
else
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++`\
           -pthread\
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
           -ldl
endif
PROTOC = protoc
GRPC_CPP_PLUGIN = grpc_cpp_plugin
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`
PROTOS_PATH = ../protos

calculator_service : calculator.proto CalculatorServer CalculatorClient

calculator.proto : 
	$(PROTOC) -I ../protos --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $(PROTOS_PATH)/calculator.proto 
	$(PROTOC) -I ../protos --proto_path=$(PROTOS_PATH)  --cpp_out=. $(PROTOS_PATH)/calculator.proto	

CalculatorServer : calculator.pb.o calculator.grpc.pb.o CalculatorServer.o 
	$(CXX) $^ $(LDFLAGS) -o $@ 
	
CalculatorClient : calculator.pb.o calculator.grpc.pb.o CalculatorClient.o
	$(CXX) $^ $(LDFLAGS) -o $@ 
	
CalculatorServer.o : CalculatorServer.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^
	
CalculatorClient.o : CalculatorClient.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $^	

calculator.pb.o : calculator.pb.cc
	$(CXX) $(CXXFLAGS)  -c -o $@ $^ 		
	
calculator.grpc.pb.o : calculator.grpc.pb.cc
	$(CXX) $(CXXFLAGS)  -c -o $@ $^

clean:
	rm -rf *.pb.cc *pb.h *.o *.h *.o CalculatorServer CalculatorClient  
