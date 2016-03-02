#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>

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

using namespace std;
using std::vector;
class Character;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ZorkUL();
    void play(QGraphicsRectItem *rectItem);
    string go(string direction);

private slots:
    void on_okBtn_clicked();

    void on_upBtn_clicked();

    void on_rightBtn_clicked();

    void on_downBtn_clicked();

    void on_leftBtn_clicked();

private:
    Ui::MainWindow *ui;
    QStringListModel *model;
    QStringList stringList;
    Parser parser;
    Room *currentRoom;
    vector <Room> rooms;
    QGraphicsRectItem *rect;
    Room *prison, *observation, *battle, *mainStairwell, *hallway, *cockpit, *sickbay, *riddle, *secondaryStairwell, *armoury;
    Door *obsrvDoor, *btlDoor, *hallwayDoor,*armDoor, *stairs ;
    Character *testCharacter;

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

    //inline method for clearing the QStringList used to display text to the UI TextListView
    inline void clearListView(){
        stringList.clear();
    }
};

#endif // MAINWINDOW_H
