#include "mainwindow.h"
#include "ui_mainwindow.h"


//Constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameSetup();

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
    rect->setBrush(* new QBrush(Qt::green));


    QGraphicsScene *scene = new QGraphicsScene();
    scene->addWidget(window);
    scene->addItem(rect);

    QGraphicsView *view = new QGraphicsView(scene);

    view->show();
    view->size();
    window->play(rect);

    return a.exec();
}

void MainWindow::gameSetup()
{
    testHero = new Hero("Hero", 100);
    testVillian = new Character("Villian", 300.0);
    displayHealth(testHero);

        //UI Attributes Setup
        uiSetup();

        //Create Doors
        doorSetup();

        //Create Rooms
        roomSetup();

        remainder = TIME_LEFT;
        timer = new QTimer();
        timer->setInterval(1000);
        timer->setSingleShot(false);
        connect(timer,SIGNAL(timeout()),this,SLOT(clock()));


}

void MainWindow::clock()
{
    remainder = remainder - 1;
    //remainder = ((remainder % (1000*60*60))%(1000*60)) / 1000;
    QString qstr = QString::fromStdString(valueToString(remainder));
    ui->lbl_Clock->setText(qstr);


    if(remainder <= 0)
    {
        gameSetup();
        positionCharacter();
    }

}


void MainWindow:: uiSetup()
{
    ui->btn_ObservationDoor->setIcon(QIcon(":/closed_door.png"));
    ui->btn_ObservationDoor->setEnabled(true);
    ui->btn_ObservationDoorKeycard->setVisible(true);
    ui->btn_BattleDoor->setIcon(QIcon(":/closed_door.png"));
    ui->btn_BattleDoor->setEnabled(true);
    ui->btn_BattleDoorKeycard->setVisible(true);
    ui->btn_Villian->setVisible(false);
    ui->btn_HealthPack->setVisible(false);
    ui->btn_Gun->setVisible(false);
    ui->lbl_Villian_2->setVisible(false);
    ui->lbl_Health_Villian->setVisible(false);
    ui->lbl_Character_Health_Villian->setVisible(false);
    ui->btn_Riddle->setVisible(false);
    ui->lbl_Clock->setStyleSheet("QLabel{color : blue;}");
}


/*Create Doors***********************************************************************************************************************/
void MainWindow:: doorSetup()
{

    obsrvDoor = new Door("ObservationDoor",true,"right");
    btlDoor = new Door ("BattleDoor", true, "right");
    hallwayDoor = new Door ("HallwayDoor",true,"right");
    cockpitDoor = new Door("CockpitDoor", true, "right");
}


// Create rooms********************************************************************************************************************/
void MainWindow:: roomSetup()
{

    prison = new Room("Prison",0);
    prison->addItem(new Item("ObservationDoorKeycard"));
    prison->addDoor(obsrvDoor);

    observation = new Room("Observation_Room",0);
    observation->addDoor(btlDoor);

    battle = new Room("Battle",0);

    mainStairwell = new Room("Stairwell_Level_1",0);
    mainStairwell->addDoor(hallwayDoor);

    sickbay = new Room("SickBay",0);
    sickbay->addItem(new Item("Health_Pack"));
    sickbay->addItem(new Item("BattleDoorKeycard"));
    sickbay->addItem(new Item("Gun"));

    hallway = new Room("Hallway",0);
    hallway->addDoor(cockpitDoor);

    cockpit = new Room("Cockpit",0);


//                  (Up, Right, Down, Left)
    prison->setExits(NULL, observation, NULL, NULL);
    observation->setExits(NULL, battle, mainStairwell, prison);
    battle->setExits(NULL, NULL, hallway, observation);
    mainStairwell->setExits(observation, hallway, sickbay, NULL);
    sickbay->setExits(mainStairwell, NULL, NULL, NULL);
    hallway->setExits(battle, cockpit, NULL, NULL);
    cockpit->setExits(NULL, NULL, NULL, hallway);


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
    //positionCharacter();

    rooms.push_back(prison);
    rooms.push_back(observation);
    rooms.push_back(battle);
    rooms.push_back(mainStairwell);
    rooms.push_back(sickbay);
    rooms.push_back(hallway);
    rooms.push_back(cockpit);
}

void MainWindow::play(QGraphicsRectItem *rectItem)
{
    rect = rectItem;
    model = new QStringListModel(this);
    printWelcome();
}

void MainWindow::setListViewText(){
    model->setStringList(stringList);
    ui->textListView->setModel(model);
}

void MainWindow::printWelcome() {
    QString str = QString::fromStdString(currentRoom->longDescription());
    stringList.append(str);
    setListViewText();
}

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


void MainWindow::printHelp() {
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
        stringList.append("Where are you going???");
        setListViewText();
    }

    else
    {
        //Text display change
        if(currentRoom != sickbay && currentRoom != battle && currentRoom->getFlag() == 0)
        {
            currentRoom->setFlag(1);
        }

        //Move room.
        currentRoom = nextRoom;
        clearListView();
        QString description2 = QString::fromStdString(currentRoom->longDescription());
        stringList.append(description2);
        setListViewText();

        if(currentRoom == sickbay)
        {
            ui->btn_HealthPack->setVisible(true);
        }

        if (currentRoom == battle && currentRoom->getFlag() != 2)
        {
            ui->btn_Villian->setVisible(true);
            ui->lbl_Villian_2->setVisible(true);
            ui->lbl_Health_Villian->setVisible(true);
            ui->lbl_Character_Health_Villian->setVisible(true);
            displayHealth(testVillian);
        }

        if(currentRoom == hallway)
        {
            ui->btn_Riddle->setVisible(true);
        }

        if(currentRoom == cockpit)
        {
            timer->stop();
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
    processCommand(*command);
    delete command;
    positionCharacter();

}

void MainWindow::positionCharacter()
{
    vector<int> temp = currentRoom->getCharacterPosition();
    int x = temp.at(0);
    int y = temp.at(1);
    rect->setRect(x, y, 20, 20);
}




void MainWindow::on_btn_Items_clicked()
{
    QString qstr1 = QString::fromStdString(testHero->displayItems());
    stringList.append(qstr1);
    setListViewText();
}


void MainWindow::on_btn_ObservationDoorKeycard_clicked()
{
    timer->start();
    inventory = addItems("ObservationDoorKeycard");

    if(inventory != 0)
    ui->btn_ObservationDoorKeycard->setVisible(false);


}


void MainWindow::on_btn_BattleDoorKeycard_clicked()
{

    inventory = addItems("BattleDoorKeycard");

    if(inventory != 0)
    ui->btn_BattleDoorKeycard->setVisible(false);

}

void MainWindow::on_btn_ObservationDoor_pressed()
{
   int key = openDoor();

   if(key == 0)
   {
       ui->btn_ObservationDoor->setIcon(QIcon(":/opened_door.png"));
       ui->btn_ObservationDoor->setEnabled(false);
   }
}


void MainWindow::on_btn_BattleDoor_pressed()
{
    int key = openDoor();

    if(key == 0)
    {
        ui->btn_BattleDoor->setIcon(QIcon(":/opened_door.png"));
        ui->btn_BattleDoor->setEnabled(false);
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
            testHero->setHealth(250);
            ui->btn_HealthPack->setVisible(false);
            displayHealth(testHero);
       }
}

void MainWindow::displayHealth(Character* c)
{
    string hlth = valueToString(c->getHealth());
    QString qstr = QString::fromStdString(hlth);

    if(c->getDescription()=="Hero")
        ui->lbl_Health->setText(qstr);

    else
        ui->lbl_Health_Villian->setText(qstr);
}



void MainWindow::on_btn_Gun_clicked()
{
    inventory = addItems("Gun");

    if(inventory != 0)
    {
        ui->btn_Gun->setVisible(false);
    }
    battle->setFlag(2);
}

int MainWindow::addItems(string item)
{
    int itemInRoom = currentRoom->isItemInRoom(item);

    if (false == itemInRoom)
    {
       stringList.append("\nItem is not in room");
       setListViewText();
       return 0;
    }

    stringList.append("\nItem is in room");
    testHero->addItems(currentRoom->getItem(item));
    stringList.append("You have taken the ");
    QString qstr1 = QString::fromStdString(item);
    stringList.append(qstr1);
    setListViewText();
    return 1;

}

int MainWindow::openDoor()
{
    if(testHero->itemListSize() > 0)
    {
        string doorLock = (currentRoom->unlockDoor(testHero));
        if(!(doorLock.compare("You don`t have the key!")==0)&&!(doorLock.compare("All doors are unlocked!")==0))
        {
            stringList.append("Door has been unlocked.\n");
            QString description = QString::fromStdString(doorLock);
            stringList.append(description);
            setListViewText();
            return 0;

        }

        else
        {
            QString description = QString::fromStdString(doorLock);
            stringList.append(description);
            setListViewText();
            return 1;
        }
    }
    else
    {
          stringList.append("You don`t have the key!");
          setListViewText();
          return 1;
    }
}

void MainWindow::on_btn_Riddle_clicked()
{
    RiddleDialog *rd = new RiddleDialog;

    if(rd->exec())
    {
        setRiddleAnswer(rd->getAnswer());
    }
}

void MainWindow::on_btn_Villian_pressed()
{
    if(currentRoom == battle)
    {
        bool fight = testHero->getItem("Gun");

        /*Cast Hero to Character type to execute Operator overload -.
        Character *score = dynamic_cast<Character*>(testHero);
        Character *x = score-testVillian;
        cout<<x->getHealth()<<endl;
        //cout<<"Hero:"<<score->getHealth()<<"||"<<x<<"||"<<testVillian->getHealth()<<":Villian\n"<<endl;
        if (fight == false || x->getHealth()>0)//score-testVillian > 0)//testHero->getHealth() < 250)*/


        if (fight == false || testHero->getHealth() < 250)
        {
            if(sickbay->getFlag() == 0)
            {
                ui->btn_Gun->setVisible(true);
                sickbay->setFlag(2);
            }

            currentRoom = sickbay;
            positionCharacter();
            testHero->setHealth(-200);
            displayHealth(testHero);
            clearListView();
            QString description1 = QString::fromStdString(currentRoom->longDescription());
            stringList.append(description1);
            setListViewText();
            ui->btn_HealthPack->setVisible(true);
        }
        else
        {
            currentRoom->setFlag(2);
            clearListView();
            QString description1 = QString::fromStdString(currentRoom->longDescription());
            stringList.append(description1);
            setListViewText();
            ui->btn_Gun->setVisible(false);
            ui->lbl_Villian_2->setVisible(false);
            ui->lbl_Health_Villian->setVisible(false);
            ui->lbl_Character_Health_Villian->setVisible(false);
            ui->btn_Villian->setVisible(false);
            //ui->btn_Riddle->setVisible(true);
        }
    }
    else
    {
        stringList.append("Enemy is out of reach.");
        setListViewText();
    }

}


//Quit Program
void MainWindow::on_btn_Quit_pressed()
{
    QApplication::quit();
}



void MainWindow::on_btn_Reset_pressed()
{
    gameSetup();
    positionCharacter();
}

void MainWindow::setRiddleAnswer(bool answer)
{
    riddleCorrect = answer;
}

void MainWindow::on_btn_CockpitDoor_clicked()
{
    if(riddleCorrect)
    {
        ui->btn_CockpitDoor->setIcon(QIcon(":/opened_door.png"));
        ui->btn_CockpitDoor->setEnabled(false);
        cockpitDoor->setLock(false);
    }
}
