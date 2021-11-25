#ifndef RECORD_H
#define RECORD_H

#include <QDate>

class Record
{
public:
    Record(QDate date, int seconds, QString domain);
    Record(Record * orig);
    QDate Date();
    QString Domain();
    int Seconds();

private:
    QDate m_date;
    int m_seconds;
    QString m_domain;
    QString m_user;
};

#endif // RECORD_H
