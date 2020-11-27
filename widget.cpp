#include "widget.h"
#include "ui_widget.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTimer>


Widget::Widget(QWidget *parent) :QWidget(parent),ui(new Ui::Widget)
{
    ui->setupUi(this);
    init();
}

void Widget::showClick(QModelIndex index)
{
    return;
}

void Widget::update()
{
    if(!db.isOpen()){
        ui->pushButton->setDisabled(false);
        ui->pushButton->setText("连接");
    }else{
        showLog();
        qDebug()<<"database is connecting...";
    }
    return;
}


Widget::~Widget()
{
    qDebug()<<"~Widget";
    if(db.isOpen())
    {
        qDebug()<<"db close...";
        db.close();
    }
    delete ui;
}

void Widget::init()
{
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(3000);
}

void Widget::initDatabase()
{
    qDebug()<<"initDatabase!";
    QString host_txt = ui->host_->text();
    QString user_txt = ui->user_->text();
    QString pass_txt = ui->pass_->text();

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host_txt.toLatin1());
//    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("mysql");
    db.setUserName(user_txt.toLatin1());
    db.setPassword(pass_txt.toLatin1());
    if(db.open())
        qDebug()<<"Hi mysql!";
    else
        qDebug()<<"fail to connect mysql!";

    if(!db.isOpen())
    {
        qDebug()<<"db inot isOpen!";
        db.close();
        return;
    }


}

void Widget::on_pushButton_clicked()
{

    QSqlQuery query;
    QString name;
    QString value;
    QFile file;

    initDatabase();
    query = QSqlQuery(db);
    query.exec("SET GLOBAL general_log = 'ON';");
    query.exec("show global variables like '%general%';");
    while(query.next())
    {
        name = query.value(0).toString();
        value = query.value(1).toString();
        if(strcmp(name.toLatin1(), "general_log_file") == 0)
        {
            logpath = value;
            qDebug()<<logpath;
            file.setFileName(logpath);
        }
    }

    if(!file.exists()){
        qDebug()<<"file is not exists!";
        db.close();
        return;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"fail to read file!";
        db.close();
        return;
    }

    file.close();
    ui->pushButton->setDisabled(true);
    ui->pushButton->setText("已连接");
}

void Widget::on_pushButton_2_clicked()
{
    showLog();
}

void Widget::showLog()
{
    qDebug()<<"showLog...";

    if(!db.isOpen()){
        qDebug()<<"db is not open!";
        return;
    }

    QFile file(logpath);
    if(!file.exists()){
        qDebug()<<"file is not exists!";
        db.close();
        return;
    }

    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"fail to read file!";
        db.close();
        return;
    }


    QStringList strList;
    QTextStream aStream(&file); //用文本流读取文件
    aStream.seek(0);
    aStream.setAutoDetectUnicode(true); //自动检测Unicode,才能正常显示文档内的汉字
    while (!aStream.atEnd())
    {
        strList.append(aStream.readLine());//读取文件的一行
    }

    itemModel = new QStandardItemModel(this);
    for(int i = 0; i < strList.size(); i++)
    {
        QString string = static_cast<QString>(strList.at(i));
        QStandardItem* item = new QStandardItem(string);
        itemModel->appendRow(item);
    }

    ui->listView->setModel(itemModel);
    ui->listView->scrollToBottom();
    connect(ui->listView,SIGNAL(clicked(QModelIndex)),this,SLOT(showClick(QModelIndex)));
    file.close();
}
