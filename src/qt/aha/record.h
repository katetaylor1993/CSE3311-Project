#ifndef RECORD_H
#define RECORD_H

#include <QDate>

class Record
{
public:
    Record(QDate date, int seconds, QString domain, QString domainCategory, QString username);
    Record(Record * orig);
    QDate Date();
    QString Domain();
    int Seconds();
    QString User();
    QString Category();

private:
    QDate m_date;
    int m_seconds;
    QString m_domain;
    QString m_user;
    QString m_domainCategory;
};

#endif // RECORD_H
