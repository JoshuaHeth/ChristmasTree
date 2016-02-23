#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

using namespace std;
#include <stdlib.h>
#include <iostream>

//inline method for clearing the QStringList used to display text to the UI TextListView
inline void MainWindow::clearListView()
{
    stringList.clear();
}

//Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createRooms();
}

//Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

//Main method used to initialize the application, window, view, etc
int main(int argc, char *argv[])
{
    //Create the application
    QApplication a(argc, argv);
    //Create the MainWindow UI
    MainWindow *window = new MainWindow();

    QGraphicsRectItem *rect = new QGraphicsRectItem(180, 180, 20, 20);
    //rect->setRect(180,180, 20, 20);
    rect->setBrush(* new QBrush(Qt::red));

    QGraphicsScene *scene = new QGraphicsScene();
    //rect->setRect(300, 180, 20, 20);
    scene->addWidget(window);
    scene->addItem(rect);
    QGraphicsView *view = new QGraphicsView(scene);

    view->show();
    view->size();
   // window->size();
    //window->show();
    window->play(rect);
    return a.exec();
}

void MainWindow::createRooms()
{
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

//                  (Up, Right, Down, Left)
    prison->setExits(NULL, observation, NULL, NULL);
    observation->setExits(NULL, battle, mainStairwell, prison);
    battle->setExits(NULL, NULL, hallway, observation);
    mainStairwell->setExits(observation, hallway, sickbay, NULL); //secondaryStairwell);
    sickbay->setExits(mainStairwell, NULL, NULL, NULL);
    hallway->setExits(battle, cockpit, NULL, mainStairwell);
    cockpit->setExits(NULL, NULL, NULL, hallway);
    //secondaryStairwell->setExits(mainStairwell, riddle, armoury, NULL);
    //riddle->setExits(NULL, NULL, NULL, secondaryStairwell);
    //armoury->setExits(secondaryStairwell, NULL, NULL, NULL);

    //Prison - 		x(180) y(180)
    prison->setCharacterPosition(180, 180);
    //Observation - 		x(300) y(180)
    observation->setCharacterPosition(300, 180);
    //Battle - 		x(400) y(180)
    battle->setCharacterPosition(400, 180);
    //Main Stairwell - 	x(330) y(260)
    mainStairwell->setCharacterPosition(330, 260);
    //SickBay - 		x(300) y(400)
    sickbay->setCharacterPosition(300, 400);
    //Hallway -		x(450) y(280)
    hallway->setCharacterPosition(450, 280);
    //Cockpit - 		x(700) y(280)
    cockpit->setCharacterPosition(700, 280);

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
void MainWindow::play(QGraphicsRectItem *rectItem)
{
    rect = rectItem;
    model = new QStringListModel(this);


    //stringList.clear();
    printWelcome();

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
    /*QString qstr = "Trying to get home"
                   "\nyadda yadda yadda,"
                   "\nship gets attacked,"
                   "\nyadda yadda yadda,"
                   "\nneed to escape,"
                   "\nyadda yadda yadda,"
                   "\nfight the bad guys,"
                   "\nyadda yadda yadda,"
                   "\nrescue the princ....."
                   "\nA princess on a sanitation rig?"
                   "\nYeah right!";
    stringList.append("Welcome to the game!");
    stringList.append("Introduction");
    stringList.append(qstr);*/
    QString str = QString::fromStdString(currentRoom->longDescription());
    stringList.append(str);
    setListViewText();
}

/**
 * Given a command, process (that is: execute) the command.
 * If this command ends the ZorkUL game, true is returned, otherwise false is
 * returned.
 */
bool MainWindow::processCommand(Command command) {
    if (command.isUnknown()) {
        //cout << "invalid input"<< endl;
        clearListView();
        stringList.append("Welcome to the game!");
        setListViewText();
        return false;
    }

    string commandWord = command.getCommandWord();
    if (commandWord.compare("info") == 0)
        printHelp();

    else if (commandWord.compare("go") == 0)
        goRoom(command);

    else if (commandWord.compare("take") == 0)
    {
        if (!command.hasSecondWord())
        {
            clearListView();
            stringList.append("incomplete input");
            setListViewText();
        }
        else
        {
             if (command.hasSecondWord())
             {
                cout << "you're trying to take " + command.getSecondWord() << endl;
                int location = currentRoom->isItemInRoom(command.getSecondWord());
                if (location  < 0 )
                {
                    cout << "item is not in room" << endl;
                }
                else
                {
                    cout << "item is in room" << endl;
                    cout << "index number " << + location << endl;
                    cout << endl;
                    //cout << currentRoom->longDescription() << endl;
                }
            }
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
        clearListView();
        int roomNumber = rand() % rooms.size();
        Room randomRoom = rooms.at(roomNumber);
        currentRoom = &randomRoom;
        QString qstr = QString::fromStdString(randomRoom.longDescription());
        stringList.append(qstr);
        setListViewText();
    }

    else if (commandWord.compare("quit") == 0) {
        if (command.hasSecondWord()){
            clearListView();
            stringList.append("overdefined input");
            setListViewText();
        }
        else
            return true; /**signal to quit*/
    }
    return false;
}
/** COMMANDS **/
void MainWindow::printHelp() {
    //cout << "valid inputs are; " << endl;
    clearListView();
    stringList.append("Valid inputs are:");
    vector<string> commandWords = parser.showCommands();

    for(unsigned int i = 0; i < commandWords.size();i++)
    {
        QString qstr = QString::fromStdString(commandWords[i]);
        stringList.append(qstr);
    }
    setListViewText();
}

void MainWindow::goRoom(Command command) {
    if (!command.hasSecondWord()) {
        //clearListView();
        stringList.append("incomplete input");
        setListViewText();
        return;
    }

    string direction = command.getSecondWord();

    // Try to leave current room.
    Room* nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL){
        //clearListView();
        stringList.append("underdefined input");
        setListViewText();
    }
    else {
        currentRoom = nextRoom;
        clearListView();
        QString description = QString::fromStdString(currentRoom->longDescription());
        //cout << currentRoom->longDescription() << endl;
        stringList.append(description);
        setListViewText();
    }
}

/*string MainWindow::go(string direction) {
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
}*/

void MainWindow::on_okBtn_clicked()
{
    QString input = ui->commandInput->toPlainText();
    std::string buffer = input.toLocal8Bit().constData();
    if(buffer.compare("") != 0)
    {
        Command* command = parser.getCommand(buffer);
            // Pass dereferenced command and check for end of game.
        finished = processCommand(*command);
            // Free the memory allocated by "parser.getCommand()"
            //   with ("return new Command(...)")
        delete command;
        ui->commandInput->setText("");
        if (finished)
        {
            close();
        }
    }
}

void MainWindow::on_upBtn_clicked()
{
    std::string buffer = "go up";
    buttonCommand(buffer);
}

void MainWindow::on_rightBtn_clicked()
{
    std::string buffer = "go right";
    buttonCommand(buffer);
}

void MainWindow::on_downBtn_clicked()
{
    std::string buffer = "go down";
    buttonCommand(buffer);
}

void MainWindow::on_leftBtn_clicked()
{
    std::string buffer = "go left";
    buttonCommand(buffer);
}

void MainWindow::buttonCommand(string buffer)
{
    Command* command = parser.getCommand(buffer);
    finished = processCommand(*command);
    delete command;
    positionCharacter();

}

void MainWindow::positionCharacter()
{
    vector<int> temp = currentRoom->getCharacterPosition();
    //cout << temp.at(0) << endl;
    //cout << temp.at(1) << endl;
    int x = temp.at(0);
    int y = temp.at(1);
    rect->setRect(x, y, 20, 20);
}
