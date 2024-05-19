#include "calculator.h"
#include "ui_calculator.h"

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_multiply, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_devide, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_pow, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_open, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_close, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_ctan, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this,
            SLOT(get_content_from_button()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::get_content_from_button() {
    if (Calculator::input_len <= Calculator::max_len &&
        !ui->lineEdit_io->text().contains("Error")) {
        if (!Calculator::has_input) ui->lineEdit_io->setText("");

        QPushButton *button = (QPushButton *)sender();
        Calculator::prev_input = ui->lineEdit_io->text();
        QString output = (Calculator::prev_input + button->text());
        ui->lineEdit_io->setText(output);
        Calculator::has_input = true;
    } else if (ui->lineEdit_io->text().contains("Error"))
        Calculator::on_pushButton_clear_clicked();
    else
        ui->lineEdit_io->setText("Error");

    Calculator::input_len = ui->lineEdit_io->text().length();
    Calculator::input = (char *)ui->lineEdit_io;
}

void Calculator::on_action_triggered()
{
    Calculator::credit.show();
}

void Calculator::on_action_2_triggered()
{
    Calculator::deposit.show();
}

void Calculator::on_pushButton_equal_clicked()
{
    Calculator::prev_input = ui->lineEdit_io->text();
    Calculator::x = ui->lineEdit_x->text();
    float x = Calculator::x.toFloat();

    char *str;
    std::string std_str = Calculator::prev_input.toStdString();
    str = new char[std_str.size() + 1];
    strcpy(str, std_str.c_str());
    Data *top = (Data *)malloc(2 * strlen(str) * sizeof(Data));
    int res = to_rpn(str, &top);

    if (!res) {
        double ev = evaluate(top, x);
        QString result = QString::number(ev);
        ui->lineEdit_io->setText(result);
        Calculator::has_input = true;
        Calculator::input_len = ui->lineEdit_io->text().length();
        Calculator::input = (char *)ui->lineEdit_io;
    } else
        ui->lineEdit_io->setText("Error");

    free(top);
    delete str;
}

void Calculator::on_pushButton_clear_clicked()
{
    ui->lineEdit_io->setText("0.");
    Calculator::has_input = false;
    Calculator::has_dot = false;
    Calculator::has_unary_minus = false;
}

void Calculator::on_pushButton_2ndf_clicked()
{
    Calculator::is_2ndf = !Calculator::is_2ndf;

    if (Calculator::is_2ndf) {
        ui->pushButton_sin->setText("Asin");
        ui->pushButton_cos->setText("Acos");
        ui->pushButton_tan->setText("Atan");
        ui->pushButton_ctan->setText("Actan");
    } else {
        ui->pushButton_sin->setText("Sin");
        ui->pushButton_cos->setText("Cos");
        ui->pushButton_tan->setText("Tan");
        ui->pushButton_ctan->setText("Ctan");
    }
}

void Calculator::on_pushButton_bs_clicked()
{
    QString output = ui->lineEdit_io->text();
    output.chop(1);
    ui->lineEdit_io->setText(output);
}

void Calculator::on_pushButton_dot_clicked()
{
    if (!ui->lineEdit_io->text().contains(".")) {
        ui->lineEdit_io->setText(ui->lineEdit_io->text() + ".");
        Calculator::has_dot = true;
    }
}

void Calculator::on_pushButton_unary_clicked()
{
    QString input = ui->lineEdit_io->text();

    if (!Calculator::has_unary_minus) {
        ui->lineEdit_io->setText("-" + input);
        Calculator::has_unary_minus = true;
    } else {
        ui->lineEdit_io->setText(input.remove(0, 1));
        Calculator::has_unary_minus = false;
    }
}


void Calculator::on_pushButton_plot_clicked()
{
    Calculator::plot.set_data(ui->lineEdit_io->text());
    Calculator::plot.show();
}

