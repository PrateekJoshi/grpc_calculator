PROTO=protoc
CPP_PLUGIN=../bins/opt/grpc_cpp_plugin
CXXFLAGS += -std=c++11 `pkg-config --cflags protobuf grpc`
LDFLAGS += -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc`\
            -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
            -ldl
PROTOS_PATH = ../protos/
CPP_OUT_PATH=.
GRPC_OUT_PATH=.
CPP_COMPILER="g++"

calculator_service : calculator.proto CalculatorServer CalculatorClient

calculator.proto : 
	$(PROTO) -I ../protos --grpc_out=. --plugin=protoc-gen-grpc=$(CPP_PLUGIN) $(PROTOS_PATH)calculator.proto 
	$(PROTO) -I ../protos --proto_path=$(PROTOS_PATH)  --cpp_out=. $(PROTOS_PATH)calculator.proto	

CalculatorServer : calculator.pb.o calculator.grpc.pb.o CalculatorServer.o 
	$(CPP_COMPILER) $^ -L/usr/local/lib $(LDFLAGS) -o $@ 
	
CalculatorClient : calculator.pb.o calculator.grpc.pb.o CalculatorClient.o
	$(CPP_COMPILER) $^ -L/usr/local/lib $(LDFLAGS) -o $@ 
	
CalculatorServer.o : CalculatorServer.cc
	$(CPP_COMPILER) $(CXXFLAGS) -c -o $@ $^
	
CalculatorClient.o : CalculatorClient.cc
	$(CPP_COMPILER) $(CXXFLAGS) -c -o $@ $^	

calculator.pb.o : calculator.pb.cc
	$(CPP_COMPILER) $(CXXFLAGS)  -c -o $@ $^ 		
	
calculator.grpc.pb.o : calculator.grpc.pb.cc
	$(CPP_COMPILER) $(CXXFLAGS)  -c -o $@ $^

clean:
	rm -rf *.pb.cc *pb.h *.o *.h *.o CalculatorServer CalculatorClient  
