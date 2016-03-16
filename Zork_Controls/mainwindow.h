#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsView>

#include "Character.h"
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

    void on_btn_MainStairwellDoorKeycard_clicked();

    void on_btn_BattleDoorKeycard_clicked();

    void on_btn_ObservationDoor_pressed();

    void on_btn_BattleDoor_pressed();

    void on_btn_StairwellLevel1_pressed();

    void on_btn_HealthPack_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList stringList;
    Parser parser;
    Room *currentRoom;
    vector <Room*> rooms;
    QGraphicsRectItem *rect;
    Room *prison, *observation, *battle, *mainStairwell, *hallway, *cockpit, *sickbay;//, *riddle, *secondaryStairwell, *armoury;
    Door *obsrvDoor, *btlDoor, *hallwayDoor;//,*armDoor, *stairs ;
    Character *testCharacter;
    QString *str;

    /*For visibility control of  QPushButtons/QLabels
    QList<QPushButton *> btn_List;
    QList<QLabel *> lbl_List;*/

    bool finished;
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);


    void createItems();
    void displayItems();
    void teleport();
    void setListViewText();
    void addToListView(QString s);


    void buttonCommand(string s);
    void positionCharacter();
    void openLock();
    void checkLock();
    void displayCharacterItems();
    string intToString(int value);

    void displayHealth();

    //QObject controls
    //void changeLevelDisplay();

    //inline method for clearing the QStringList used to display text to the UI TextListView
    inline void clearListView(){
        stringList.clear();
    }
};

#endif // MAINWINDOW_H
