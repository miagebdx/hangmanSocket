/*
+---------------------------------------------+
| @authors :                                  |
|             Jérémy Morin                    |
|             Louis Lainé                     |
|             Mathieu Merceron                |
|             Julien Couraud                  |
|             Pierrick Sailler                |
+---------------------------------------------+
| @usage   : Client Class                     |
| @methods : client.cpp                       |
+---------------------------------------------+

*/
#include "../socket/socket.cpp"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <string>
#include <ext/stdio_filebuf.h> // GNU standard only !
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <stdlib.h>

using namespace std;

class SocketClientTest : public SocketClient
{
public:
	SocketClientTest(std::string hostname, int port): SocketClient(hostname,port) {};
	virtual void work(int);
	string answerChar(int);
	void hangingMan(int);
};
