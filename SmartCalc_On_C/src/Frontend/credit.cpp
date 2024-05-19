#include "credit.h"
#include "ui_credit.h"

Credit::Credit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Credit)
{
    ui->setupUi(this);

    this->setFixedSize(560, 280);
}

Credit::~Credit()
{
    delete ui;
}

void Credit::on_pushButton_calculate_credit_clicked()
{
    Credit::input.loan_amount = ui->lineEdit_loan_amount->text().toDouble();
    Credit::input.term = ui->lineEdit_term->text().toDouble();
    Credit::input.is_monthly_frequency = ui->radioButton_months->isChecked();
    Credit::input.is_yearly_frequency = ui->radioButton_years->isChecked();
    Credit::input.interest_rate = ui->lineEdit_interest_rate->text().toDouble();
    Credit::input.is_annuity = ui->radioButton_annuity->isChecked();
    Credit::input.is_differentiated = ui->radioButton_differentiated->isChecked();

    Credit::output = calculate_credit(Credit::input);

    ui->label_monthly_payment_output->setText(
        QString::number(Credit::output.monthly_payment, 'f', 2));
    ui->label_last_month_output->setText(
        QString::number(Credit::output.monthly_payment_last, 'f', 2));
    ui->label_overpayment_output->setText(
        QString::number(Credit::output.overpayment, 'f', 2));
    ui->label_total_output->setText(
        QString::number(Credit::output.total, 'f', 2));
}
