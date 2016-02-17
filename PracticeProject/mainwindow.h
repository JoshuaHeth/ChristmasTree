#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGridLayout>
#include <QPushButton>

#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "item.h"
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
using std::vector;

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
    void play();
    string go(string direction);
    //QString getName() const;
    //void setName(const QString & name);

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
    void clearListView();

    //QString getName() const
    //{
       //return ui->commandInput->text();
    //}

    //void setName(const QString & name)
    //{
       // ui->commandInput->setText(name);
    //}
};

#endif // MAINWINDOW_H
