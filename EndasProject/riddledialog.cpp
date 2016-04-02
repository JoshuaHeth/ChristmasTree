#include "riddledialog.h"
#include "ui_riddledialog.h"

RiddleDialog::RiddleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RiddleDialog)
{
    ui->setupUi(this);
    ui->riddleTextEdit->setText("As I was going to St. Ives, I met a man with seven wives, each wife had seven sacks, "
                                    "each sack had seven cats, each cat had seven kits, kits, cats, sacks, wives, how many were going to St. Ives?");
}

RiddleDialog::~RiddleDialog()
{
    delete ui;
}

void RiddleDialog::setAnswer(bool possibleAnswer)
{
    answer = possibleAnswer;
}

bool RiddleDialog::getAnswer()
{
    return answer;
}

void RiddleDialog::on_radioButton_1_clicked()
{
    setAnswer(false);
}

void RiddleDialog::on_radioButton_2_clicked()
{
    setAnswer(false);
}

void RiddleDialog::on_radioButton_3_clicked()
{
    setAnswer(false);
}

void RiddleDialog::on_radioButton_4_clicked()
{
    setAnswer(true);
}
