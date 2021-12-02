#ifndef FILTERS_H
#define FILTERS_H

#include <QDate>
#include <QList>

#include "record.h"
#include "employee.h"

class Filters
{
public:
    Filters();
    explicit Filters(QList<Record> records);
    Filters(QList<Record> recs, QList<QString> emps, QList<QString> cats, QList<QString> webs);

    void setStartDate(QDate date);
    void setEndDate(QDate date);
    void setCategories(QList<QString> cats);
    void setWebsites(QList<QString> webs);
    void setEmployees(QList<QString> emps);

    void clearCategories();
    void clearWebsites();
    void clearEmployees();

    QList<Record> filteredRecords();

    QList<QString> listWebsites(bool filtered);
    QList<QString> listCategories(bool filtered);
    QList<QString> listUsers(bool filtered);

    int totalTimeFor(QDate* date, QString employee, QString category, QString website);
    QDate firstDateOfRecords();
    QDate lastDateOfRecords();

private:
    QList<Record> m_allRecords;
    QDate m_startDate;
    QDate m_endDate;
    QList<QString> m_employees;
    QList<QString> m_categories;
    QList<QString> m_websites;
};

#endif // FILTERS_H
