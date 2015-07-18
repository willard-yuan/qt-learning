#include <QCoreApplication>
#include <iostream>
#include <QDebug>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //QList<int> list = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; //不能按cpp的这种方式初始化
    QList<int> list;
    for(int j = 0; j < 10; j++)
        list.insert(list.end(), j);
    QList<int>::iterator i;
    for(i = list.begin(); i != list.end(); ++i){
        cout << *i << " ";
        //qDebug() << (*i);
        *i = (*i) * 10;
    }

    cout << endl;

    QList<int>::const_iterator ci;
    for(ci = list.begin(); ci != list.end(); ++ci)
        cout << *ci << " ";
        //qDebug() << *ci;
    cout << endl;

    return a.exec();
}
