#include "plot.h"
#include "ui_plot.h"

Plot::Plot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Plot)
{
    ui->setupUi(this);
    this->setFixedSize(800, 800);

    h = 0.001;
    xBegin = -5;
    xEnd = 5 + h;

    ui->widget->xAxis->setRange(-5, 5);
    ui->widget->yAxis->setRange(-5, 5);
    ui->widget->addGraph();
    ui->widget->graph(0)->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(
        QCPScatterStyle(QCPScatterStyle::ssDisc, 3));
}

Plot::~Plot()
{
    delete ui;
}

void Plot::set_data(QString input) {
    ui->widget->graph(0)->data().data()->clear();
    ui->widget->replot();

    char *str;
    std::string std_str = input.toStdString();
    str = new char[std_str.size() + 1];
    strcpy(str, std_str.c_str());
    Data *top = (Data *)malloc(2 * strlen(str) * sizeof(Data));
    int res = 1;
    if (str) res = to_rpn(str, &top);
    QVector<double> x, y;

    if (!res) {
        for (X = xBegin; abs(X - xEnd) > 1E-6; X += h) {
            x.push_back(X);
            y.push_back(evaluate(top, X));
        }
    }

    delete str;
    free(top);

    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
}
