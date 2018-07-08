/*
 * CalculatorClient.cc
 *
 *  Created on: Jul 8, 2018
 *      Author: prateek
 */
#include <iostream>
#include <grpcpp/grpcpp.h>
#include "calculator.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using calculator::InputNumber;
using calculator::OutputNumber;
using calculator::Calculator;
using namespace std;

class CalculatorClient
{
 public:
	CalculatorClient(shared_ptr<Channel> channel)
	      : stub_(Calculator::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
int doCalculate(int n1, int n2, const char* opr) {
    // Data we are sending to the server.
	Status status;
    InputNumber request;
    request.set_num1(n1);
    request.set_num2(n2);

    // Container for the data we expect from the server.
    OutputNumber reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    if ( memcmp(opr,"add",3) == 0 )
    {
    	status = stub_->Addition(&context, request, &reply);
    }
    else if ( memcmp(opr,"sub",3) == 0 )
    {
    	status = stub_->Subraction(&context, request, &reply);
    }
    else if ( memcmp(opr,"mul",3) == 0 )
    {
    	status = stub_->Multiply(&context, request, &reply);
    }
    else if ( memcmp(opr,"div",3) == 0 )
    {
    	status = stub_->Divide(&context, request, &reply);
    }

    // Act upon its status.
    if (status.ok())
    {
      return (int) reply.num();
    }
    else
    {
      cout << status.error_code() << ": " << status.error_message()
                << endl;
      cout << "RPC failed";
      return -1;
    }
  }

 private:
  std::unique_ptr<Calculator::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  CalculatorClient calculate(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
  int n1 = 100, n2=10;
  cout << "-------------- GRPC Calculator Client -------------"<<endl;
  cout<<"num1: "<<n1<<" num2: "<<n2<<endl;
  int reply = calculate.doCalculate(n1,n2,"add");
  cout << "Calculator addition received : " << reply << endl;
  reply = calculate.doCalculate(n1,n2,"sub");
  cout << "Calculator subrcation received : " << reply << endl;
  reply = calculate.doCalculate(n1,n2,"mul");
  cout << "Calculator multiplication received: " << reply << endl;
  reply = calculate.doCalculate(n1,n2,"div");
  cout << "Calculator divison received: " << reply << endl;

  return 0;
}



