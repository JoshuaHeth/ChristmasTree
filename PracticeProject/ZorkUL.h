#ifndef ZORKUL_H_
#define ZORKUL_H_

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
using namespace std;
using std::vector;

class ZorkUL {
private:
	Parser parser;
	Room *currentRoom;
    vector <Room> rooms;
	void createRooms();
	void printWelcome();
	bool processCommand(Command command);
	void printHelp();
	void goRoom(Command command);
    void createItems();
    void displayItems();
    void teleport();

public:
	ZorkUL();
	void play(MainWindow *window);
	string go(string direction);
};

#endif /*ZORKUL_H_*/
