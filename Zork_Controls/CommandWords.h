#ifndef COMMANDWORDS_H_
#define COMMANDWORDS_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class CommandWords {
private:
	//Define a static vector for our valid command words.
	//We'll populate this in the class constructor
	static vector<string> validCommands;

public:
	CommandWords();
    //~CommandWords();

	bool isCommand(string aString);
    vector<string> showAll();
};


#endif /*COMMANDWORDS_H_*/
