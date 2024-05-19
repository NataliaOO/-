#ifndef CREDIT_H
#define CREDIT_H

#include <QMainWindow>

extern "C" {
#include "../Backend/credit_c.h"
}

namespace Ui {
class Credit;
}

class Credit : public QMainWindow {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();
  CreditInput input;
  CreditOutput output;

 private slots:

  void on_pushButton_calculate_credit_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
