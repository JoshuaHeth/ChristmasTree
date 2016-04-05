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

private:
    Ui::RiddleDialog *ui;
    bool answer;


private slots:
    void on_radioButton_4_clicked();


public:
    explicit RiddleDialog(QWidget *parent = 0);
    ~RiddleDialog();

    /**
     * @brief getAnswer
     * @return
     */
    inline bool getAnswer(){
        return answer;
    }
};

#endif // RIDDLEDIALOG_H
