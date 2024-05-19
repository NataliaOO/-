#ifndef PLOT_H
#define PLOT_H

#include <QVector>
#include <QWidget>

#include "QtWidgets/qwidget.h"

extern "C" {
#include "../Backend/rpn.h"
}

namespace Ui {
class Plot;
}

class Plot : public QWidget {
  Q_OBJECT

 public:
  explicit Plot(QWidget *parent = nullptr);
  ~Plot();
  void set_data(QString input);
  double xBegin;  ///< Start point for x variable
  double xEnd;    ///< End point for x variable
  double h;       ///< Step
  double X;       ///< Temp value for x variable

 private:
  Ui::Plot *ui;
};

#endif  // PLOT_H
