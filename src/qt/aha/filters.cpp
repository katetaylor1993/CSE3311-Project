#include "filters.h"

Filters::Filters(){}

//no filters
Filters::Filters(QList<Record> records):
    m_allRecords{records}
{
    foreach(Record r, m_allRecords)
    {
        if(!m_employees.contains(r.User()))
        {
            m_employees.append(r.User());
        }
        if(!m_categories.contains(r.Category()))
        {
            m_categories.append(r.Category());
        }
        if(!m_websites.contains(r.Domain()))
        {
            m_websites.append(r.Domain());
        }
        m_startDate = firstDateOfRecords();
        m_endDate = lastDateOfRecords();
    }
}

Filters::Filters(QList<Record> recs, QList<QString> emps, QList<QString> cats, QList<QString> webs) :
    m_allRecords{recs},
    m_employees{emps},
    m_categories{cats},
    m_websites{webs}
{

}

QDate Filters::firstDateOfRecords()
{
    QDate start = QDate::currentDate();
    foreach(Record r, m_allRecords)
    {
        if(r.Date()<start)
        {
            start = r.Date();
        }
    }
    return start;
}

QDate Filters::lastDateOfRecords()
{
    QDate end = QDate(1990,1,1);
    foreach(Record r, m_allRecords)
    {
        if(r.Date()>end)
        {
            end = r.Date();
        }
    }
    return end;
}


QList<QString> Filters::listWebsites(bool filtered)
{
    QList<Record> forHere;
    if(filtered)
        forHere = filteredRecords();
    else
        forHere = m_allRecords;
    QList<QString> ret;
    foreach(Record r, forHere)
    {
        if(!ret.contains(r.Domain()))
        {
            ret.append(r.Domain());
        }
    }
    return ret;
}

//TODO: add filtered boolean
QList<QString> Filters::listCategories(bool filtered)
{
    QList<Record> forHere;
    if(filtered)
        forHere = filteredRecords();
    else
        forHere = m_allRecords;
    QList<QString> ret;
    foreach(Record r, forHere)
    {
        if(!ret.contains(r.Category()))
        {
            ret.append(r.Category());
        }
    }
    return ret;
}

QList<QString> Filters::listUsers(bool filtered)
{
    QList<Record> forHere;
    if(filtered)
        forHere = filteredRecords();
    else
        forHere = m_allRecords;
    QList<QString> ret;
    foreach(Record r, forHere)
    {
        if(!ret.contains(r.User()))
        {
            ret.append(r.User());
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
        if((r.Date() > m_endDate) && (r.Date() < m_startDate)) continue;

        ret.append(r);
    }
    return ret;
}

void Filters::setStartDate(QDate date) {m_startDate = date;}
void Filters::setEndDate(QDate date) {m_endDate = date;}

int Filters::totalTimeFor(QDate* date, QString employee, QString category, QString website)
{
    if(date!=nullptr && (*date < m_startDate || *date > m_endDate))
        return -1;
    QList<Record> filtered = filteredRecords();
    int ret = 0;
    foreach(Record r, filtered)
    {
        bool addThis = true;
        if((date!=nullptr) && (r.Date()!=*date))
            addThis = false;
        if((employee!=nullptr) && (r.User()!=employee))
            addThis = false;
        if((category!=nullptr) && (r.Category()!=category))
            addThis = false;
        if((website!=nullptr) && (r.Category()!=category))
            addThis=false;

        if(addThis)
            ret += r.Seconds();
    }
    return ret;
}
