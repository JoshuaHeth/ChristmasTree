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

    inline bool getAnswer(){
        return answer;
    }


private slots:
    void on_radioButton_4_clicked();

private:
    Ui::RiddleDialog *ui;
    bool answer;
};

#endif // RIDDLEDIALOG_H
