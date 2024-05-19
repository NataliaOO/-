#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QMainWindow>

extern "C" {
#include "../Backend/deposit_c.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QMainWindow {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();
  DepositInput input;
  DepositOutput output;
  DepositPayment w1, w2, w3, w4, w5;
  DepositPayment r1, r2, r3, r4, r5;

 private slots:

  void on_pushButton_calculate_deposit_clicked();

 private:
  Ui::Deposit *ui;
};

#endif  // DEPOSIT_H
