#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QFile>
#include <QSqlDatabase>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QStandardItemModel* itemModel;
    QSqlDatabase db;
    QString logpath;

public:
    void showLog();
    void init();
    void initDatabase();
    void verifyFileOpen(QFile& file);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void showClick(QModelIndex index);
    void update();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
