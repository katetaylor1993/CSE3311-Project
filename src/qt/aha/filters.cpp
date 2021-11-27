#include "filters.h"

Filters::Filters(){}

Filters::Filters(QList<Record> records):
    m_allRecords{records}
{}

Filters::Filters(QList<Record> recs, QList<QString> emps, QList<QString> cats, QList<QString> webs) :
    m_allRecords{recs},
    m_employees{emps},
    m_categories{cats},
    m_websites{webs}
{}

QList<QString> Filters::listWebsites()
{
    QList<QString> ret;
    foreach(Record r, m_allRecords)
    {
        if(!ret.contains(r.Domain()))
        {
            ret.append(r.Domain());
        }
    }
    return ret;
}

QList<QString> Filters::listCategories()
{
    QList<QString> ret;
    foreach(Record r, m_allRecords)
    {
        if(!ret.contains(r.Category()))
        {
            ret.append(r.Category());
        }
    }
    return ret;
}

QList<Record> Filters::filteredRecords()
{
    QList<Record> ret;

    foreach(Record r, m_allRecords)
    {
        if(!(m_employees.contains(r.User()))) continue;
        if(!(m_categories.contains(r.Category()))) continue;
        if(!(m_websites.contains(r.Domain()))) continue;
        if(r.Date() > m_endDate) continue;
        if(r.Date() < m_startDate) continue;

        ret.append(r);
    }
    return ret;
}

void Filters::setStartDate(QDate date) {m_startDate = date;}
void Filters::setEndDate(QDate date) {m_endDate = date;}
