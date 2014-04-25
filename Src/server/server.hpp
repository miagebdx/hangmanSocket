/*
+---------------------------------------------+
| @authors :                                  |
|			 Jérémy Morin                     |
|			 Louis Lainé                      |
|			 Mathieu Merceron                 |
|			 Julien Couraud                   |
|			 Pierrick Sailler			      |
+---------------------------------------------+
| @usage     : Server Class                   |
| @methods   : server.cpp                     |
+---------------------------------------------+

*/

#include "../socket/socket.cpp"

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include "joueur/joueur.hpp"
#include <vector>
#include <ext/stdio_filebuf.h> // GNU standard only !


using namespace std;

class SocketServerTest : public SocketServer,joueur
{

public:
	SocketServerTest(int port) : SocketServer(port) {};
	~SocketServerTest(){}
	virtual void work(int fdw);
	string askConnexion(int fwd,string question);

};
