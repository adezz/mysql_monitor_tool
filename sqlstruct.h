#ifndef SQLSTRUCT_H
#define SQLSTRUCT_H
#include <QString>
#include <QRegExp>
#include <QDebug>

class Sqlstruct
{
public:
    Sqlstruct();
    Sqlstruct(QString sqlQuery);
    void sqlParse();
    QString getTime();
    QString getCommand();
    QString getPhrase();

private:
    QString sqlTime;
    QString sqlCommand;
    QString sqlPhrase;
    QString sqlQuery;
};

#endif // SQLSTRUCT_H
