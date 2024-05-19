#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

#include "credit.h"
#include "deposit.h"
#include "plot.h"

extern "C" {
#include "../Backend/rpn.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  Calculator(QWidget *parent = nullptr);
  ~Calculator();
  bool has_input = false;        ///< Has input value
  bool has_dot = false;          ///< Has input dot char
  bool has_unary_minus = false;  ///< Has input unary char
  unsigned int max_len = 255;    ///< Max allowed input length
  unsigned int input_len = 0;    ///< Current input length
  QString prev_input;            ///< Input buffer
  QString x = "1";               ///< Value of x variable
  char *input;                   ///< Input pointer
  Deposit deposit;               ///< Deposit calculator window
  Credit credit;                 ///< Credit calculator window
  Plot plot;                     ///< Plot window
  bool is_2ndf = false;          ///< Is enebled 2nd function view

 private slots:
  void on_action_triggered();          // credit
  void on_action_2_triggered();        // deposit
  void on_pushButton_equal_clicked();  // =
  void get_content_from_button();      // ???
  void on_pushButton_clear_clicked();  // AC
  void on_pushButton_2ndf_clicked();
  /*
      void on_pushButton_dot_clicked();
      void on_pushButton_unary_clicked();
      void on_pushButton_bs_clicked();
      void on_actionCredit_triggered();
      void on_pushButton_plot_clicked();
  */

  void on_pushButton_bs_clicked();

  void on_pushButton_dot_clicked();

  void on_pushButton_unary_clicked();

  void on_pushButton_plot_clicked();

 private:
  Ui::Calculator *ui;
};
#endif  // CALCULATOR_H
