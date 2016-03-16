#include "mainwindow.h"
#include "ui_mainwindow.h"


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
    window->play(rect);

    return a.exec();
}

void MainWindow::createRooms()
{

    testCharacter = new Character("Bob",100);
    displayHealth();
    ui->lbl_Villian->setVisible(false);
    ui->btn_HealthPack->setVisible(false);

    /*Create Doors***********************************************************************************************************************/
    obsrvDoor = new Door("ObservationDoor",true,"right");
    btlDoor = new Door ("BattleDoor", true, "right");
    hallwayDoor = new Door ("HallwayDoor",true,"right");
    //stairs = new Door ("Stairwell_Level_1Door", true, "left");
    //armDoor = new Door("ArmouryDoor",true,"down");

    // Create rooms
    prison = new Room("Prison",0);
    prison->addItem(new Item("ObservationDoorKeycard"));
    prison->addDoor(obsrvDoor);

    observation = new Room("Observation_Room",0);
    observation->addDoor(btlDoor);
    observation->addItem(new Item("Stairwell_Level_1DoorKeycard"));

    battle = new Room("Battle",0);

    mainStairwell = new Room("Stairwell_Level_1",0);
    //mainStairwell->addDoor(stairs);
    mainStairwell->addDoor(hallwayDoor);

    sickbay = new Room("SickBay",0);
    sickbay->addItem(new Item("Health_Pack"));
    sickbay->addItem(new Item("BattleDoorKeycard"));

    hallway = new Room("Hallway_of_Something",0);
    //hallway->addDoor(stairs);

    cockpit = new Room("Cockpit",0);

    /*secondaryStairwell = new Room("Stairwell_Level_2",0);
    secondaryStairwell->addDoor(armDoor);

    riddle = new Room("Riddle_Room",0);
    //riddle->addToList(new Item("ArmouryDoorKeycard"));//ADD AFTER RIDDLE IS COMPLETED

    armoury = new Room("Armoury",0);
    armoury->addItem(new Item("Gun"));*/

//                  (Up, Right, Down, Left)
    prison->setExits(NULL, observation, NULL, NULL);
    observation->setExits(NULL, battle, mainStairwell, prison);
    battle->setExits(NULL, NULL, hallway, observation);
    mainStairwell->setExits(observation, hallway, sickbay, NULL);//, secondaryStairwell); //secondaryStairwell);
    sickbay->setExits(mainStairwell, NULL, NULL, NULL);
    hallway->setExits(battle, cockpit, NULL, mainStairwell);
    cockpit->setExits(NULL, NULL, NULL, hallway);
    //secondaryStairwell->setExits(NULL, riddle, armoury, mainStairwell);
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
    //Secondary Stariwell - 		x(320) y(190)
   /* secondaryStairwell->setCharacterPosition(320, 190);
    //Riddle Room -			x(520) y(190)
    riddle->setCharacterPosition(520, 190);
    //Armoury -			x(350) y(360)
    armoury->setCharacterPosition(350, 360);*/

    currentRoom = prison;

    rooms.push_back(prison);
    rooms.push_back(observation);
    rooms.push_back(battle);
    rooms.push_back(mainStairwell);
    rooms.push_back(sickbay);
    rooms.push_back(hallway);
    rooms.push_back(cockpit);
    /*rooms.push_back(*secondaryStairwell);
    rooms.push_back(*riddle);
    rooms.push_back(*armoury);*/
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


   else if (commandWord.compare("teleport") == 0){
        clearListView();
        int roomNumber = rand() % rooms.size();
        Room *randomRoom = rooms.at(roomNumber);
        currentRoom = randomRoom;
        QString qstr = QString::fromStdString(randomRoom->longDescription());
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
        stringList.append("Where you going???");
        setListViewText();
    }
    else if (currentRoom == battle)
    {
        ui->lbl_Villian->setVisible(true);
        bool fight = testCharacter->getItem("Gun");
        if (fight == false || testCharacter->getHealth() < 250)
        {
            currentRoom = sickbay;
            testCharacter->setHealth(-200);
            displayHealth();
            QString description1 = QString::fromStdString(currentRoom->longDescription());
            stringList.append(description1);
            setListViewText();
        }

        else
            stringList.append("Enemy has been shot down and freedom is within reach");
            setListViewText();

    }

    else
    {
        /*Change to downstairs view and move room.
        if(currentRoom == secondaryStairwell)
        {
                ui->centralMap->setStyleSheet("background-image: url(:/SecondLevel.png);");
                changeLevelDisplay();
        }


        //Change to upstairs view and move room.
        if(currentRoom == secondaryStairwell && nextRoom == mainStairwell)
        {
            changeLevelDisplay();
            ui->centralMap->setStyleSheet("background-image: url(:/mainLevel2.png);");
        }*/


        //Move room.
        currentRoom = nextRoom;
        clearListView();
        QString description2 = QString::fromStdString(currentRoom->longDescription());
        stringList.append(description2);
        setListViewText();

        if(currentRoom == observation && currentRoom->getFlag()==0)
            delete ui->btn_ObservationDoorKeycard;

        if(currentRoom == battle && currentRoom->getFlag()==0)
            delete ui->btn_BattleDoorKeycard;

        if(currentRoom == sickbay)
        {
            //sickbay->addItem(new Item("Health_Pack"));
            ui->btn_HealthPack->setVisible(true);
        }

        if(currentRoom->getFlag() == 0)
            currentRoom->setFlag(1);



        /*Delete buttons when used.
        if(currentRoom == observation)
            delete ui->btn_ObservationDoorKeycard;*/



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




void MainWindow::on_btn_Items_clicked()
{
    QString qstr1 = QString::fromStdString(testCharacter->displayItems());
    stringList.append(qstr1);
    setListViewText();
}


void MainWindow::on_btn_ObservationDoorKeycard_clicked()
{
    string item = "ObservationDoorKeycard";
    int itemInRoom = currentRoom->isItemInRoom(item);

       if (false == itemInRoom )
       {
           stringList.append("\nItem is not in room");
           setListViewText();
       }
       else
       {
           stringList.append("\nItem is in room");
           testCharacter->addItems(currentRoom->getItem(item));
           stringList.append("You have taken the ");
           QString qstr1 = QString::fromStdString(item);
           stringList.append(qstr1);
           setListViewText();
           ui->btn_ObservationDoorKeycard->setVisible(false);

       }
}

void MainWindow::on_btn_MainStairwellDoorKeycard_clicked()
{
    string item = "Stairwell_Level_1DoorKeycard";
    int itemInRoom = currentRoom->isItemInRoom(item);

       if (false == itemInRoom )
       {
           stringList.append("\nItem is not in room");
           setListViewText();
       }
       else
       {
           stringList.append("\nItem is in room");
           testCharacter->addItems(currentRoom->getItem(item));
           stringList.append("You have taken the ");
           QString qstr1 = QString::fromStdString(item);
           stringList.append(qstr1);
           setListViewText();
           ui->btn_MainStairwellDoorKeycard->setVisible(false);

       }
}

void MainWindow::on_btn_BattleDoorKeycard_clicked()
{
    string item = "BattleDoorKeycard";
    int itemInRoom = currentRoom->isItemInRoom(item);

       if (false == itemInRoom)
       {
           stringList.append("\nItem is not in room");
           setListViewText();
       }
       else
       {
           stringList.append("\nItem is in room");
           testCharacter->addItems(currentRoom->getItem(item));
           stringList.append("You have taken the ");
           QString qstr1 = QString::fromStdString(item);
           stringList.append(qstr1);
           setListViewText();
           ui->btn_BattleDoorKeycard->setVisible(false);
           //delete ui->btn_BattleDoorKeycard;
       }
}

void MainWindow::on_btn_ObservationDoor_pressed()
{
    if(testCharacter->itemListSize() > 0)
    {
        //string doorLock = (currentRoom->unlockDoor(testCharacter->getItems()));
        string doorLock = (currentRoom->unlockDoor(testCharacter));
                if(!(doorLock.compare("You don`t have the key!")==0)&&!(doorLock.compare("All doors are unlocked!")==0))
                {
                    stringList.append("Door has been unlocked.\n");
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                    ui->btn_ObservationDoor->setIcon(QIcon(":/opened_door.png"));
                }

                else
                {
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                }
    }

    else
    {
          stringList.append("You don`t have the key!");
          setListViewText();
    }
}


void MainWindow::on_btn_BattleDoor_pressed()
{
    if(testCharacter->itemListSize() > 0)
    {
       // string doorLock = (currentRoom->unlockDoor(testCharacter->getItems()));
        string doorLock = (currentRoom->unlockDoor(testCharacter));
                if(!(doorLock.compare("You don`t have the key!")==0)&&!(doorLock.compare("All doors are unlocked!")==0))
                {
                    stringList.append("Door has been unlocked.\n");
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                    ui->btn_BattleDoor->setIcon(QIcon(":/opened_door.png"));
                }

                else
                {
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                }
    }

    else
    {
          stringList.append("You don`t have the key!");
          setListViewText();
    }
}


void MainWindow::on_btn_StairwellLevel1_pressed()
{
    if(testCharacter->itemListSize() > 0)
    {
        string doorLock = (currentRoom->unlockDoor(testCharacter));
                if(!(doorLock.compare("You don`t have the key!")==0)&&!(doorLock.compare("All doors are unlocked!")==0))
                {
                    stringList.append("Stairs has been unlocked.\n");
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                    ui->btn_StairwellLevel1->setIcon(QIcon(":/stairs_open.png"));
                    //ui->centralMap->setStyleSheet("background-image: url(:/SecondLevel.png);");
                }

                else
                {
                    QString description = QString::fromStdString(doorLock);
                    stringList.append(description);
                    setListViewText();
                }
    }

    else
    {
          stringList.append("You don`t have the key!");
          setListViewText();
    }
}



void MainWindow::on_btn_HealthPack_clicked()
{
    string item = "Health_Pack";
    int itemInRoom = currentRoom->isItemInRoom(item);

       if (false == itemInRoom)
       {
           stringList.append("\nItem is not in room");
           setListViewText();
       }
       else
       {
            testCharacter->setHealth(250);
            ui->btn_HealthPack->setVisible(false);
            displayHealth();
       }
}

void MainWindow::displayHealth()
{
    string hlth = valueToString(testCharacter->getHealth());
    QString qstr = QString::fromStdString(hlth);
    ui->lbl_Health->setText(qstr);
}

/*void MainWindow::changeLevelDisplay()
{
    btn_List = ui->centralMap->findChildren<QPushButton *>();
    lbl_List = ui->centralMap->findChildren<QLabel *>();

    foreach(QPushButton *l, btn_List)
    {
      if(&l->isVisible == false)
          l->setVisible(true);

      else
          l->setVisible(false);
    }

    foreach(QLabel *l, lbl_List)
    {
      if(&l->isVisible == false)
          l->setVisible(true);

      else
          l->setVisible(false);
    }
}*/



