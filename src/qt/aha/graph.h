#ifndef GRAPH_H
#define GRAPH_H

#include <QChart>
#include "filters.h"

class Graph
{
public:
    Graph(QObject* gp);
    ~Graph();
    QChart * pieChart(Filters filters);
    QChart * barChart(Filters filters);

private:
    QObject * graphParent;
};

#endif // GRAPH_H
