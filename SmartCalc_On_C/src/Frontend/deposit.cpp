#include "deposit.h"
#include "ui_deposit.h"

Deposit::Deposit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Deposit)
{
    ui->setupUi(this);
}

Deposit::~Deposit()
{
    delete ui;
}

void Deposit::on_pushButton_calculate_deposit_clicked()
{
    Deposit::input.deposit_amount = ui->lineEdit_deposit->text().toDouble();
    Deposit::input.term = ui->lineEdit_term->text().toDouble();
    Deposit::input.interest_rate = ui->lineEdit_interest_rate->text().toDouble();
    Deposit::input.tax_rate = ui->lineEdit_tax->text().toDouble();
    Deposit::input.is_daily_frequency = ui->radioButton_daily->isChecked();
    Deposit::input.is_ateoft_frequency = ui->radioButton_ateoft->isChecked();
    Deposit::input.capitalization = ui->checkBox_capitalization->isChecked();

    r1.day = ui->lineEdit_replenishment_day_1->text().toDouble();
    r1.replenishment = ui->lineEdit_replenishment_amount_1->text().toDouble();
    r2.day = ui->lineEdit_replenishment_day_2->text().toDouble();
    r2.replenishment = ui->lineEdit_replenishment_amount_2->text().toDouble();
    r3.day = ui->lineEdit_replenishment_day_3->text().toDouble();
    r3.replenishment = ui->lineEdit_replenishment_amount_3->text().toDouble();
    r4.day = ui->lineEdit_replenishment_day_4->text().toDouble();
    r4.replenishment = ui->lineEdit_replenishment_amount_4->text().toDouble();
    r5.day = ui->lineEdit_replenishment_day_5->text().toDouble();
    r5.replenishment = ui->lineEdit_replenishment_amount_5->text().toDouble();

    Deposit::input.replenishments[0] = r1;
    Deposit::input.replenishments[1] = r2;
    Deposit::input.replenishments[2] = r3;
    Deposit::input.replenishments[3] = r4;
    Deposit::input.replenishments[4] = r5;

    w1.day = ui->lineEdit_withdrawl_day_1->text().toDouble();
    w1.withdrawal = ui->lineEdit_withdrawl_amount_1->text().toDouble();
    w2.day = ui->lineEdit_withdrawl_day_2->text().toDouble();
    w2.withdrawal = ui->lineEdit_withdrawl_amount_2->text().toDouble();
    w3.day = ui->lineEdit_withdrawl_day_3->text().toDouble();
    w3.withdrawal = ui->lineEdit_withdrawl_amount_3->text().toDouble();
    w4.day = ui->lineEdit_withdrawl_day_4->text().toDouble();
    w4.withdrawal = ui->lineEdit_withdrawl_amount_4->text().toDouble();
    w5.day = ui->lineEdit_withdrawl_day_5->text().toDouble();
    w5.withdrawal = ui->lineEdit_withdrawl_amount_5->text().toDouble();

    Deposit::input.withdrawals[0] = w1;
    Deposit::input.withdrawals[1] = w2;
    Deposit::input.withdrawals[2] = w3;
    Deposit::input.withdrawals[3] = w4;
    Deposit::input.withdrawals[4] = w5;

    Deposit::output = calculate_deposit(Deposit::input);

    ui->label_total_earned_output->setText(
        QString::number(Deposit::output.total_earned, 'f', 2));
    ui->label_total_amount_output->setText(
        QString::number(Deposit::output.total_amount, 'f', 2));
    ui->label_tax_amount_output->setText(
        QString::number(Deposit::output.tax_amount, 'f', 2));
}
