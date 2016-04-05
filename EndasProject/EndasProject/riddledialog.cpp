#include "riddledialog.h"
#include "ui_riddledialog.h"

/**
 * @brief RiddleDialog::RiddleDialog
 * @param parent
 */
RiddleDialog::RiddleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RiddleDialog)
{
    ui->setupUi(this);
    ui->riddleTextEdit->setText("As I was going to St. Ives, I met a man with seven wives.\nEach wife had seven sacks, "
                                    "each sack had seven cats, each cat had seven kits. \nKits, cats, sacks, wives, how many were going to St. Ives?");
}

/**
 * @brief RiddleDialog::~RiddleDialog
 */
RiddleDialog::~RiddleDialog(){
    delete ui;
}

/**
 * @brief RiddleDialog::on_radioButton_4_clicked
 */
void RiddleDialog::on_radioButton_4_clicked(){
    answer = true;
}
