/*
+---------------------------------------------+
| @authors :                                  |
|             Jérémy Morin                    |
|             Louis Lainé                     |
|             Mathieu Merceron                |
|             Julien Couraud                  |
|             Pierrick Sailler                |
+---------------------------------------------+
| @usage   : Client Application Class         |
| @class   : client.hpp                       |
+---------------------------------------------+

*/

#include "client.hpp"
#define clear system("clear");
const int autorisedNumber=7;

bool loop=true;
string exitAction="exitAction";
int number;

void SocketClientTest::work(int fwd)
{
  clear;
  while(exitAction.compare("exitAction")==0){
    string answer;
    string request = answerChar(fwd);
    string blankword;

    recvmsg(fwd,request);
    cout<<"\E[32;1m"<<request<<"\E[m"<<endl;
    recvmsg(fwd,request);
    hangingMan(number);
    cout<<"\E[37;1m\t\t"<<request<<"\E[m"<<endl;
    string blankWordTmp=request;
    cout<<""<<endl;
    cout << "\E[31;1m----------------------------------------------\E[m"<<endl;
    while(loop==true)
    {
      recvmsg(fwd,request);
      cout<<"\E[33;1m"<<request<<"\E[m";
      cin>> answer;
      cout<<""<<endl;
      //management exit
      if (answer.compare("exit")==0||answer.compare("EXIT")==0)
      {
        sendmsg(fwd,exitAction);
        exit(EXIT_SUCCESS);
        }

      //only one letter
      clear;
      if (answer.length()==1)
      {
        sendmsg(fwd, answer);
        }
      else
      {
        cout << "\E[31;1mCheater !\E[m" << endl;
        sendmsg(fwd,"");
        }

      //display blankword
      string usedLetters;
      recvmsg(fwd,blankword);
      recvmsg(fwd,usedLetters);
      if (blankWordTmp.compare(blankword)==0)
      {
        number++;
        }
      blankWordTmp=blankword;
      hangingMan(number);
      cout<<""<<endl;
      cout<<"\E[33;1m \t\t"<<blankword<<"\E[m"<<endl;
      cout<<""<<endl;

      cout << "\E[31;1m----------------------------------------------\E[m"<<endl;
      cout << "\E[34;1m\tUsed letter(s) : "<<usedLetters<<"\E[m"<<endl;
      // cout << "\E[33;1mAnswer's number(s) : "<<number<<"\E[m"<<endl;
      cout << "\E[36;1m\tYou have : "<<autorisedNumber-number<<" chance(s)."<<"\E[m"<<endl;
      cout << "\texit to quit"<<endl;
      cout <<""<<endl;
      string test;
      recvmsg(fwd, test);
      if (test.compare(blankword)==0)
      {
        cout << "\E[32;1mYou find the word !\E[m" << endl;
        sendmsg(fwd,exitAction);
        exit(EXIT_SUCCESS);
        }
      if (number==autorisedNumber)
      {
        cout<<"\E[31;1mYou loose ! - "<<"word : "<<test<<"\E[m"<<endl;
        sendmsg(fwd,exitAction);
        exit(EXIT_SUCCESS);
        }
      }


    }
  }

/*
* @ return : server question
* @ usage : reply to server just one char
*/
string SocketClientTest::answerChar(int fwd)
{
  string request;
  string answer;
  recvmsg(fwd,request);

  cout<<"\E[33;1m"<<request<<"\E[m";
  cin>> answer;
  if (answer.length()==1 && (answer.compare("y")==0 || answer.compare("Y")==0)) sendmsg(fwd, answer);
  else if (answer.compare("y")!=1 || answer.compare("Y")!=1)
  {
    sendmsg(fwd,exitAction);
    cout<<"\E[31;1mDeconnect !\E[m"<<endl;
    exit(EXIT_SUCCESS);

    }
  else {
    cout << "\E[31;1mCheater !\E[m" << endl;
    sendmsg(fwd,"");}
  clear;
  return request;
  }

/*
* @ return : void
* @ usage : display hangMan
*/

void SocketClientTest::hangingMan( int number )
{
  switch ( number )
  {
    case 0:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 1:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 2:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        |   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 3:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        |]  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 4:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       [|]  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 5:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       [|]  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 6:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       [|]  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       /    | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    case 7:
    cout<<"\E[33;1m\t\t\t\t        ----| \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        '   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t        O   | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       [|]  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t       / \\  | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    cout<<"\E[33;1m\t\t\t\t            | \E[m"<<endl;
    break;
    }

  printf( "\n\n" );
  }

