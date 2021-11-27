#include "record.h"

// constructor
Record::Record(QDate date, int seconds, QString domain, QString domainCategory) :
    m_date{date},
    m_seconds{seconds},
    m_domain{domain},
    m_domainCategory{domainCategory}
{}

// copy constructor
Record::Record(Record * orig) :
    Record(orig->Date(),orig->Seconds(),orig->Domain(),orig->Category()) {}

QDate Record::Date() {return m_date;}
int Record::Seconds() {return m_seconds;}
QString Record::Domain() {return m_domain;}
QString Record::Category() {return m_domainCategory;}
QString Record::User() {return m_user;}
