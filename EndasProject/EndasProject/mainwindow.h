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

#include "Room.h"
#include "item.h"
#include "door.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include "hero.h"
#include "riddledialog.h"


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


private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList stringList;
    Room *currentRoom, *nextRoom;
    vector <Room*> rooms;
    QGraphicsRectItem *rect;
    Room *prison, *observation, *battle, *mainStairwell, *hallway, *cockpit, *sickbay;
    Door *obsrvDoor, *btlDoor, *hallwayDoor, *cockpitDoor, *hallwayDoor2;
    Hero *testHero;
    Character *testVillian;
    QString str;
    QTimer *timer;
    int inventory, remainder;
    string *itemName;

private slots:
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

    void on_btn_ID_clicked();

    void on_btn_VillianID_clicked();

    void on_btn_Friends_clicked();


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void play(QGraphicsRectItem*);



    /**
     * Function Template to get string values.
     * @brief valueToString
     * @param value
     * @return
     */
    template <typename T> string valueToString (const T value){
        ostringstream temp;
        temp<<value;
        return temp.str();
    }



    void gameSetup();
    void uiSetup();
    void doorSetup();
    void roomSetup();
    void printWelcome();
    void goRoom(const string &);

    void setListViewText();
    int addItems(const string &);

    void positionCharacter();
    int openDoor();
    void displayHealth(Character*);


    /**
     * inline method for clearing the QStringList used to display text to the UI TextListView
     * @brief clearListView
     */
    inline void clearListView(){
        stringList.clear();
    }
};

#endif // MAINWINDOW_H
