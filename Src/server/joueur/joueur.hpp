/*
+---------------------------------------------+
| @authors :                                  |
|             Jérémy Morin                    |
|             Louis Lainé                     |
|             Mathieu Merceron                |
|             Julien Couraud                  |
|             Pierrick Sailler                |
+---------------------------------------------+
| @usage     : Gamer class                    |
| @methods   : joueur.cpp                     |
+---------------------------------------------+

*/
#ifndef HPP_JOUEUR
#define HPP_JOUEUR


using namespace std;
#include <string>
#include <algorithm>


class joueur
{
public:
	joueur();
	~joueur(){};
	void setLetterList(string _letter);
	string getLetterList();
	string getWord();
	void setBlank(string blankWord);
	string getBlank();
	string actionBlankWord(string wordBlank, string letterUti);
	vector<string> takeWords();

	class JoueurException
	{
	private:
		string message;

	public:
		JoueurException(string _message=""){
			this->message = _message;
		};
		~JoueurException(){};
		void what(){
			cout << "Exception throws JoueurException => " << this->message << endl;
		}
		
	};


protected:
	string word;
	string letterList;
	string blank;


};
#endif
