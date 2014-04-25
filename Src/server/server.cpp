/*
+---------------------------------------------+
| @authors :                                  |
|             Jérémy Morin                    |
|             Louis Lainé                     |
|             Mathieu Merceron                |
|             Julien Couraud                  |
|             Pierrick Sailler                |
+---------------------------------------------+
| @usage   : Server Class                     |
| @class   : server.hpp                       |
+---------------------------------------------+

*/

#include "server.hpp"
#include <time.h>
#include <fstream>
#include <iomanip>
#include <locale>
#include <sstream>
#include "joueur/joueur.cpp"

#define clear system("clear");

bool boucle=true;

/*Fonction main du server
* @return : void
* @usage : manage display & server func's
*/

void SocketServerTest::work(int fwd)
{
	//connexion to client
	string answer="";
	answer = askConnexion(fwd,"Usage : exit to quit\nDo you want to play ? (y/n) \n");

	if (answer.compare("y")==0){

		sendmsg(fwd,"You are connected\n");
		joueur *j = new joueur;
		string blank;

		word=j->getWord();
		cout<<"\E[34;1mThe word "<<fwd<<" : "<<word<<"\E[m"<<endl;
		letterList=j->getLetterList();

		sendmsg(fwd, j->actionBlankWord(j->getWord(),j->getLetterList()));

		while(boucle==true)
		{

			sendmsg(fwd,"Give me a letter : ");
			cout<<"\E[34;1m+ "<<fwd<<" : Ask a letter\E[m"<<endl;
			string letter;
			recvmsg(fwd, letter);
			letterList=j->getLetterList();
			j->setLetterList(letter);
			//management of client exit
			if (letter.compare("exitAction")==0) break;

			//transform string to blankString with find letters
			string blank = j->actionBlankWord(j->getWord(),j->getLetterList());
			sendmsg(fwd, blank);
			sendmsg(fwd, j->getLetterList());
			sendmsg(fwd, j->getWord());

			if (word==blank) break;

			}
		delete j;
		} else {sendmsg(fwd, "Goodbye!\n");}
	}


/*
* @ return : client answer
* @ usage : ask client (fwd).
*/
string SocketServerTest::askConnexion(int fwd,string question)
{
	string answer;
	sendmsg(fwd,question);
	recvmsg(fwd,answer);
	return answer;
}
