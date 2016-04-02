#include "Command.h"

/**
 * Create a command object. First and second word must be supplied, but
 * either one (or both) can be null. The command word should be null to
 * indicate that this was a command that is not recognised by this game.
 */
Command::Command(string firstWord, string secondWord) {
    this->commandWord = firstWord;
    this->secondWord = secondWord;
}


