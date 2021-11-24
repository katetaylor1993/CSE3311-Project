#ifndef FILTERS_H
#define FILTERS_H

#include <QDate>
#include <QList>

#include "employee.h"

class Filters
{
public:
    explicit Filters();

private:
    QDate m_startDate;
    QDate m_endDate;
    QList<Employee> m_employees;
    QList<QString> m_categories;
    QList<QString> m_websites;
};

#endif // FILTERS_H
