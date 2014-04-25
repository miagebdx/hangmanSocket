CXX= g++
CXXFLAGS= -Wall -pthread -std=c++11
EXEC = client server

all:
	g++ Src/mainClient.cpp $(CXXFLAGS) -o client
	g++ Src/mainServer.cpp $(CXXFLAGS) -o server



clean:
	rm -f ${EXEC} *.o *~

