#include "sqlstruct.h"

Sqlstruct::Sqlstruct()
{

}

Sqlstruct::Sqlstruct(QString sqlQuery)
{
    this->sqlQuery = sqlQuery;
    this->sqlParse();
}

void Sqlstruct::sqlParse()
{
    // (\\d{6}\\s\\d{2}:\\d{2}:\\d{2})?
    int pos = 0;
    QRegExp sqlRegExp__("(\\d+\\s\\d{2}:\\d{2}:\\d{2})[\\t\\s]+\\d+\\s+([^\\s]+)\\s+(.*)"); //带有时间的正则匹配
    pos = sqlRegExp__.indexIn(this->sqlQuery);
    if(pos > -1){
        this->sqlTime = sqlRegExp__.cap(1);
        this->sqlCommand = sqlRegExp__.cap(2);
        this->sqlPhrase = sqlRegExp__.cap(3);
        qDebug()<<sqlRegExp__.cap(1);
        qDebug()<<sqlRegExp__.cap(2);
        qDebug()<<sqlRegExp__.cap(3);
        return;
    }

    pos = 0;
    QRegExp sqlRegExp_("\\t\\t\\s+\\d+\\s(\\w+)\\t(.*)");//无时间的正则匹配
    pos = sqlRegExp_.indexIn(this->sqlQuery);
    if(pos > -1){
        this->sqlTime = "";
        this->sqlCommand = sqlRegExp_.cap(1);
        this->sqlPhrase = sqlRegExp_.cap(2);
        return;
    }

    this->sqlTime = "";
    this->sqlCommand = "";
    this->sqlPhrase = "";
}

QString Sqlstruct::getTime()
{
    return this->sqlTime;
}

QString Sqlstruct::getCommand()
{
    return this->sqlCommand;
}

QString Sqlstruct::getPhrase()
{
    return this->sqlPhrase;
}

