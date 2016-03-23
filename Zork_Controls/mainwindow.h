#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define TIME_LEFT 60

#include <QtDebug>

#include <QMainWindow>
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QTimer>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

//#include "Character.h"
#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include "door.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <QButtonGroup>
#include "hero.h"


using namespace std;
using std::vector;
class Character;
class Room;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //ZorkUL();
    void play(QGraphicsRectItem *rectItem);
    string go(string direction);    

    //Function Template to get string values.
    template <typename T> string valueToString (const T value){
        T strValue = value;
        ostringstream temp;
        temp<<strValue;
        return temp.str();
    }


private slots:
    void on_okBtn_clicked();

    void on_upBtn_clicked();

    void on_rightBtn_clicked();

    void on_downBtn_clicked();

    void on_leftBtn_clicked();

    void on_btn_Items_clicked();

    void on_btn_ObservationDoorKeycard_clicked();

    void on_btn_BattleDoorKeycard_clicked();

    void on_btn_ObservationDoor_pressed();

    void on_btn_BattleDoor_pressed();

    void on_btn_HealthPack_clicked();

    void on_btn_Gun_clicked();

    void on_btn_Riddle_clicked();

    void on_btn_Villian_pressed();

    void on_btn_Quit_pressed();

    void on_btn_Reset_pressed();

    void clock();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList stringList;
    Parser parser;
    Room *currentRoom;
    vector <Room*> rooms;
    QGraphicsRectItem *rect;
    Room *prison, *observation, *battle, *mainStairwell, *hallway, *cockpit, *sickbay;
    Door *obsrvDoor, *btlDoor, *hallwayDoor, *cockpitDoor;
    Hero *testHero;
    Character *testVillian;
    QString *str;
    QTimer *timer;
    bool finished;
    int inventory, remainder;

    /*For visibility control of  QPushButtons/QLabels
    QList<QPushButton *> btn_List;
    QList<QLabel *> lbl_List;*/


    void gameSetup();
    void uiSetup();
    void doorSetup();
    void roomSetup();
    //void clock();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);


    void createItems();
    void displayItems();
    void teleport();
    void setListViewText();
    void addToListView(QString s);
    int addItems(string item);


    void buttonCommand(string s);
    void positionCharacter();
    void openLock();
    int openDoor();
    void checkLock();
    void displayCharacterItems();
    string intToString(int value);

    void displayHealth(Character* c);

    //inline method for clearing the QStringList used to display text to the UI TextListView
    inline void clearListView(){
        stringList.clear();
    }
};

#endif // MAINWINDOW_H
