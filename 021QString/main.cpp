#include <QCoreApplication>
#include <stdio.h>
#include <iostream>
#include <qdebug.h>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString str1 = "Welcome ";
    str1 = str1  + "to you";

    QString str2 = "hello ";
    QString str3 = "Qt";
    str2.append(str3);

    QString str4;
    str4.sprintf("%s", "Cpp world");

    QString strArg = QString("%1 was born in %2.").arg("John").arg(1982);

    QString str5 = "Welcome to qt";
    bool result = str5.startsWith("Welcome", Qt::CaseSensitive);

    QString str6 = "124";
    bool ok;
    int dec = str6.toInt(&ok, 10);

    QByteArray ba = str5.toLocal8Bit();

    //测试QList
    QList<QString> list;
    list << str5;

    //qDebug() << str1;
    cout << qPrintable(str1) << endl;
    cout << qPrintable(str2) << endl;
    qDebug() << strArg; //打印出来有双引号
    cout << qPrintable(strArg) << endl;
    cout << result << endl;
    cout << dec << endl;
    qDebug() << ba;
    cout << qPrintable(list[0]) << ", How are you" << endl;

    return a.exec();
}
