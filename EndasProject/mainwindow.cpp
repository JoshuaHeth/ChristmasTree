#include "mainwindow.h"
#include "ui_mainwindow.h"

string getList(Hero* h, Item* i)
{
    return (h->description+" "+i->description);
}

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
    remainder--;
    str = QString::fromStdString(valueToString(remainder));
    ui->lbl_Clock->setText(str);


    if(remainder <= 0)
    {
        delete timer;
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
    ui->lbl_CockpitDoor->setPixmap(QPixmap(":/closed_door.png"));
    ui->btn_ID->setVisible(true);
    ui->btn_VillianID->setVisible(false);
    ui->lbl_HallwayDoor->setPixmap(QPixmap(":/closed_door.png"));
    ui->btn_Friends->setVisible(true);
}


/*Create Doors***********************************************************************************************************************/
void MainWindow:: doorSetup()
{
    obsrvDoor = new Door("ObservationDoor",true,"right");
    btlDoor = new Door(obsrvDoor,"BattleDoor");
    hallwayDoor = new Door (obsrvDoor, "HallwayDoor");
    cockpitDoor = new Door (obsrvDoor, "CockpitDoor");
    hallwayDoor2 = new Door ("HallwayDoor",true,"down");
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
    battle->addDoor(hallwayDoor2);

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

void MainWindow::on_btn_Quit_pressed()
{
    QApplication::quit();
}

void MainWindow::on_btn_Reset_pressed()
{
    gameSetup();
    positionCharacter();
}

void MainWindow::setListViewText(){
    model->setStringList(stringList);
    ui->textListView->setModel(model);
}

void MainWindow::printWelcome() {
    str = QString::fromStdString(currentRoom->longDescription());
    stringList.append(str);
    setListViewText();
}



void MainWindow::goRoom(string direction) {

    // Try to leave current room.
    nextRoom = currentRoom->nextRoom(direction);

    if (nextRoom == NULL){
        stringList.append("Where are you going???");
        setListViewText();
    }

    else
    {
        //If you havnt been in the room before set flag to 1.
        if(currentRoom != sickbay && currentRoom != battle && currentRoom->getFlag() == 0)
        {
            currentRoom->setFlag(1);
        }

        //Move room.
        currentRoom = nextRoom;
        positionCharacter();
        clearListView();
        str = QString::fromStdString(currentRoom->longDescription());
        stringList.append(str);
        setListViewText();

        if(currentRoom == sickbay)
        {
            ui->btn_HealthPack->setVisible(true);
        }

        if (currentRoom == battle && currentRoom->getFlag() != 2)
        {
            ui->btn_Villian->setVisible(true);
            ui->lbl_Villian_2->setVisible(true);

            if(battle->getFlag()==0)
            ui->btn_VillianID->setVisible(true);

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
    goRoom("up");
}

void MainWindow::on_rightBtn_clicked()
{
    goRoom("right");
}

void MainWindow::on_downBtn_clicked()
{
    goRoom("down");
}

void MainWindow::on_leftBtn_clicked()
{
    goRoom("left");
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
    str = QString::fromStdString(testHero->displayItems());
    stringList.append(str);
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
            testHero->setHealth(300);
            ui->btn_HealthPack->setVisible(false);
            displayHealth(testHero);
       }
}

void MainWindow::displayHealth(Character* c)
{
    string hlth = valueToString(c->getHealth());
    str = QString::fromStdString(hlth);

    if(c->getDescription()=="Hero")
        ui->lbl_Health->setText(str);

    else
        ui->lbl_Health_Villian->setText(str);
}



void MainWindow::on_btn_Gun_clicked()
{
    inventory = addItems("Gun");

    if(inventory != 0)
    {
        ui->btn_Gun->setVisible(false);
    }
    battle->setFlag(1);
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
    str = QString::fromStdString(item);
    stringList.append(str);
    setListViewText();
    return 1;

}

int MainWindow::openDoor()
{
    if(testHero->itemListSize() > 0)
    {
        string doorLock = (currentRoom->unlockDoor(testHero));
        str = QString::fromStdString(doorLock);
        stringList.append(str);
        setListViewText();

        if(!(doorLock.compare("You don`t have the key!")==0))/*&&!(doorLock.compare("All doors are unlocked!")==0))*/
            return 0;

        else
            return 1;

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
        if(rd->getAnswer())
        {
          ui->btn_Riddle->setVisible(false);
          ui->lbl_CockpitDoor->setPixmap(QPixmap(":/opened_door.png"));
          cockpitDoor->setLock(false);
        }
    }
}

void MainWindow::on_btn_Villian_pressed()
{
    if(currentRoom == battle)
    {
        bool fight = testHero->getItem("Gun");

        /*Cast Hero to Character type to execute Operator overload +...*/
        Character *score = dynamic_cast<Character*>(testHero);
        *score - *testVillian;

        if (fight == false || score->getHealth() <= 0)
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
            str = QString::fromStdString(currentRoom->longDescription());
            stringList.append(str);
            setListViewText();
            ui->btn_HealthPack->setVisible(true);
        }
        else
        {
            currentRoom->setFlag(2);
            clearListView();
            str = QString::fromStdString(currentRoom->longDescription());
            stringList.append(str);
            setListViewText();
            ui->btn_Gun->setVisible(false);
            ui->lbl_Villian_2->setVisible(false);
            ui->lbl_Health_Villian->setVisible(false);
            ui->lbl_Character_Health_Villian->setVisible(false);
            ui->btn_Villian->setVisible(false);
            hallwayDoor2->setLock(false);
            ui->lbl_HallwayDoor->setPixmap(QPixmap(":/opened_door.png"));
        }
    }
    else
    {
        stringList.append("Enemy is out of reach.");
        setListViewText();
    }

}



void MainWindow::on_btn_ID_clicked()
{
    str = QString::fromStdString(testHero->whatAmI());
    stringList.append(str);
    setListViewText();
    ui->btn_ID->setVisible(false);
}

void MainWindow::on_btn_VillianID_clicked()
{
    if(currentRoom == battle)
    {
        str = QString::fromStdString(testVillian->whatAmI());
        stringList.append(str);
        setListViewText();
        ui->btn_VillianID->setVisible(false);
    }
}

void MainWindow::on_btn_Friends_clicked()
{
     string list = ("A "+getList(testHero,new Item("doesn't need friends!!!")));
     str = QString::fromStdString(list);
     stringList.append(str);
     setListViewText();
     ui->btn_Friends->setVisible(false);
}
