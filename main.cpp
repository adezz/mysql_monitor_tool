#include "widget.h"
#include <QApplication>
//#include <QSqlDatabase>
//#include <QDebug>
//#include <QStringList>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

// 打印驱动类型
//    qDebug()<<"Avaliable drivers;";
//    QStringList drivers = QSqlDatabase::drivers();
//    foreach(QString driver,drivers)
//    qDebug()<<driver;


    Widget w;
    w.show();

    return a.exec();
}
