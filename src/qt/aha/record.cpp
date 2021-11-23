#include "record.h"

// constructor
Record::Record(QDate date, int seconds, QString domain) :
    m_date{date},
    m_seconds{seconds},
    m_domain{domain}
{}

// copy constructor
Record::Record(Record * orig) :
    Record(orig->Date(),orig->Seconds(),orig->Domain()) {}

QDate Record::Date() {return m_date;}
int Record::Seconds() {return m_seconds;}
QString Record::Domain() {return m_domain;}
