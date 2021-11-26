#ifndef FILTERS_H
#define FILTERS_H

#include <QDate>
#include <QList>

#include "record.h"
#include "employee.h"

class Filters
{
public:
    explicit Filters();

    void setStartDte(QDate date);
    void setEndDate(QDate date);

    QList<Record> filteredRecords;

private:
    QDate m_startDate;
    QDate m_endDate;
    QList<Employee> m_employees;
    QList<QString> m_categories;
    QList<QString> m_websites;
};

#endif // FILTERS_H
