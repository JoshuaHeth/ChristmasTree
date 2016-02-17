#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>

using namespace std;
#include <stdlib.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createRooms();
}

MainWindow::~MainWindow()
{
    delete ui;
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow *window = new MainWindow();

    window->size();
    window->show();

    window->play();
    return a.exec();
}

/*ZorkUL::ZorkUL() {
    createRooms();
}*/

void MainWindow::createRooms()  {
    Room *prison, *observation, *battle, *mainStairwell, *sickbay, *hallway, *cockpit;//, *secondaryStairwell, *riddle, *armoury;

    prison = new Room("Prison");
        //a->addItem(new Item("x", 1, 11));
        //a->addItem(new Item("y", 2, 22));
    observation = new Room("Observation Room");
        //b->addItem(new Item("xx", 3, 33));
        //b->addItem(new Item("yy", 4, 44));
    battle = new Room("Battle");
    mainStairwell = new Room("Stairwell Level 1");
    sickbay = new Room("SickBay");
    hallway = new Room("Hallway of Something");
    cockpit = new Room("Cockpit");
    //secondaryStairwell = new Room("Stairwell Level 2");
    //riddle = new Room("Riddle Room");
    //armoury = new Room("Armoury");

//                  (N, E, S, W)
    prison->setExits(NULL, observation, NULL, NULL);
    observation->setExits(NULL, battle, mainStairwell, prison);
    battle->setExits(NULL, NULL, NULL, observation);
    mainStairwell->setExits(observation, hallway, sickbay, NULL); //secondaryStairwell);
    sickbay->setExits(mainStairwell, NULL, NULL, NULL);
    hallway->setExits(battle, cockpit, NULL, mainStairwell);
    cockpit->setExits(NULL, NULL, NULL, hallway);
    //secondaryStairwell->setExits(mainStairwell, riddle, armoury, NULL);
    //riddle->setExits(NULL, NULL, NULL, secondaryStairwell);
    //armoury->setExits(secondaryStairwell, NULL, NULL, NULL);

    currentRoom = prison;

    rooms.push_back(*prison);
    rooms.push_back(*observation);
    rooms.push_back(*battle);
    rooms.push_back(*mainStairwell);
    rooms.push_back(*sickbay);
    rooms.push_back(*hallway);
    rooms.push_back(*cockpit);
    //rooms.push_back(*secondaryStairwell);
    //rooms.push_back(*riddle);
    //rooms.push_back(*armoury);
}

/**
 *  Main play routine.  Loops until end of play.
 */
void MainWindow::play() {
    model = new QStringListModel(this);
    stringList.append("Welcome to the game!");
    stringList.append("Type info for help.");
    setListViewText();

    //stringList.clear();
    //printWelcome();

    // Enter the main command loop.  Here we repeatedly read commands and
    // execute them until the ZorkUL game is over.
    //bool finished = false;
    //while (!finished)
    //{
        // Create pointer to command and give it a command.
            //QString buffer;
            //istream::getline(ui->commandInput->toPlainText(), buffer, '\n');
            //std::string current_locale_text = buffer.toLocal8Bit().constData();
        //Command* command = parser.getCommand();
            // Pass dereferenced command and check for end of game.
        //finished = processCommand(*command);
            // Free the memory allocated by "parser.getCommand()"
            //   with ("return new Command(...)")
        //delete command;
    //}
    //cout << endl;
    //cout << "end" << endl;
}

void MainWindow::setListViewText(){
    model->setStringList(stringList);
    ui->textListView->setModel(model);
}

void MainWindow::printWelcome() {
    cout << "start"<< endl;
    cout << "info for help"<< endl;
    cout << endl;
    cout << currentRoom->longDescription() << endl;
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool MainWindow::processCommand(Command command) {
    if (command.isUnknown()) {
        //cout << "invalid input"<< endl;
        stringList.clear();
        stringList.append("Welcome to the game!");
        setListViewText();
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("map") == 0)
        {
            stringList.clear();
            stringList.append("[prison] --- [observation] --- [battle]               ");
            stringList.append("                  |                |                  ");
            stringList.append("              [stairwell] ---- [hallway] --- [cockpit]");
            stringList.append("                  |                                   ");
            stringList.append("              [sickbay]                               ");
            setListViewText();
        }

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
         if (command.hasSecondWord()) {
        cout << "you're trying to take " + command.getSecondWord() << endl;
        int location = currentRoom->isItemInRoom(command.getSecondWord());
        if (location  < 0 )
            cout << "item is not in room" << endl;
        else
            cout << "item is in room" << endl;
            cout << "index number " << + location << endl;
            cout << endl;
            cout << currentRoom->longDescription() << endl;
        }
    }

    else if (commandWord.compare("put") == 0)
    {

    }
    /*
    {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        }
        else
            if (command.hasSecondWord()) {
            cout << "you're adding " + command.getSecondWord() << endl;
            itemsInRoom.push_Back;
        }
    }
*/
    else if (commandWord.compare("teleport") == 0){
        int roomNumber = rand() % rooms.size();
        Room randomRoom = rooms.at(roomNumber);
        currentRoom = &randomRoom;
        cout << randomRoom.longDescription() << endl;
    }

    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord())
            cout << "overdefined input"<< endl;
        else
            return true; /**signal to quit*/
    }
    return false;
}
/** COMMANDS **/
void MainWindow::printHelp() {
    //cout << "valid inputs are; " << endl;
    stringList.clear();
    stringList.append("Valid inputs are:");
    vector<string> commandWords = parser.showCommands();

    for(int i = 0; i < commandWords.size();i++)
    {
        QString qstr = QString::fromStdString(commandWords[i]);
        stringList.append(qstr);
    }
    setListViewText();
}

void MainWindow::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        cout << "incomplete input"<< endl;
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL)
        cout << "underdefined input"<< endl;
    else {
        currentRoom = nextRoom;
        cout << currentRoom->longDescription() << endl;
    }
}

string MainWindow::go(string direction) {
    //Make the direction lowercase
    //transform(direction.begin(), direction.end(), direction.begin(),:: tolower);
    //Move to the next room
    Room* nextRoom = currentRoom->nextRoom(direction);
    if (nextRoom == NULL)
        return("direction null");
    else
    {
        currentRoom = nextRoom;
        return currentRoom->longDescription();
    }
}

void MainWindow::on_okBtn_clicked()
{
    QString input = ui->commandInput->toPlainText();
    std::string buffer = input.toLocal8Bit().constData();
    Command* command = parser.getCommand(buffer);
        // Pass dereferenced command and check for end of game.
    finished = processCommand(*command);
        // Free the memory allocated by "parser.getCommand()"
        //   with ("return new Command(...)")
    delete command;
}
