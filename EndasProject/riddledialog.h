#ifndef RIDDLEDIALOG_H
#define RIDDLEDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class RiddleDialog;
}

class RiddleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RiddleDialog(QWidget *parent = 0);
    ~RiddleDialog();
    bool getAnswer();

private slots:
    void on_radioButton_1_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

private:
    Ui::RiddleDialog *ui;
    bool answer;
    void setAnswer(bool possibleAnswer);
};

#endif // RIDDLEDIALOG_H
