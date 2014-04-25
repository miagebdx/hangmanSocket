/*
+---------------------------------------------+
| @authors :                                  |
|             Jérémy Morin                    |
|             Louis Lainé                     |
|             Mathieu Merceron                |
|             Julien Couraud                  |
|             Pierrick Sailler                |
+---------------------------------------------+
| @usage   : Gamer Class                      |
| @class   : joueur.hpp                       |
+---------------------------------------------+

*/

#include "joueur.hpp"



vector<string> joueur::takeWords(){
	vector<string> liste;
	ifstream fichier("Src/server/word");

	string ligne;
	int compteur = 0;
	while (getline(fichier, ligne))
	{
		liste.push_back(ligne);
		++compteur;
	}

	if (compteur==0) throw JoueurException("unable to open file ");
	
	return liste;
}

joueur::joueur()
{
	vector<string> wordsList;
	try{
		wordsList = takeWords();
	}catch(joueur::JoueurException e){
		e.what();
		exit(EXIT_SUCCESS);
	}
	srand(time(NULL));
	int numberWord = rand()%wordsList.size();
	word=wordsList[numberWord];
	blank="";
	letterList="";
	}


void joueur::setLetterList(string _letter)
{
	this->letterList=this->letterList+_letter;
	}

void joueur::setBlank(string blankWord)
{
	this->blank=blankWord;
	}

string joueur::getBlank(){
	return this->blank;
	}


string joueur::getLetterList()
{
	return this->letterList;
	}

string joueur::getWord()
{
	return this->word;
	}

string joueur::actionBlankWord(string wordBlank, string letterUti)
{
	std::transform(wordBlank.begin(), wordBlank.end(), wordBlank.begin(), ::tolower);
	std::transform(letterUti.begin(), letterUti.end(), letterUti.begin(), ::tolower);

	string blank="";

	for (unsigned int i = 0; i < wordBlank.length(); ++i)
	{
		blank=blank+'-';
		}

	string word=this->getWord();
	blank[0]=this->getWord()[0];
	blank[word.size()-1]=word[word.size()-1];

	for (unsigned int j = 0; j < letterUti.length(); ++j)
	{
		for (unsigned int i = 0; i < wordBlank.length(); ++i){
			if (wordBlank[i]==letterUti.at(j)) {blank[i]=wordBlank[i];
				}
			}
		}
	this->setBlank(blank);
	return blank;
	}
