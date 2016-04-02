#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
using namespace std;

class Command {
private:
    string commandWord;
    string secondWord;

public:
    Command(string firstWord, string secondWord);
    //~Command();

    /*inline string getCommandWord();
        inline string getSecondWord();
    inline bool isUnknown();
    inline bool hasSecondWord();*/

    /**
     * Return the command word (the first word) of this command. If the
     * command was not understood, the result is null.
     */
    inline string getCommandWord() {
        return this->commandWord;
    }

    /**
     * Return the second word of this command. Returns null if there was no
     * second word.
     */
    inline string getSecondWord() {
        return this->secondWord;
    }

    /**
     * Return true if this command was not understood.
     */
    inline bool isUnknown() {
        return (commandWord.empty());
    }

    /**
     * Return true if the command has a second word.
     */
    inline bool hasSecondWord() {
        return (!secondWord.empty());
    }
};

#endif /*COMMAND_H_*/
