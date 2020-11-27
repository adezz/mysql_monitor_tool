#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStringListModel>
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
    QStringListModel* listmodel;
    QStandardItemModel* itemModel;
    QSqlDatabase db;
    QString logpath;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void showClick(QModelIndex index);
    void showLog();
    void init();
    void initDatabase();
    void update();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
