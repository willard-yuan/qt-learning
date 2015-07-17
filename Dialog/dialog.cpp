#include "dialog.h"
#include "ui_dialog.h"

const static double PI = 3.1415926;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("圆面积计算器");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_countBtn_clicked()
{
    bool ok;
    QString tempStr;
    QString valueStr = ui->radiusLineEdit->text();
    int valueInt = valueStr.toInt(&ok);
    double area = valueInt*valueInt*PI;
    ui->radiusLabel->setText(tempStr.setNum(area));
}
