#include "graph.h"

#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QPieSeries>

Graph::Graph(QObject* gp):
    graphParent{gp}
{

}

Graph::~Graph()
{

}

QChart * Graph::pieChart(Filters filters)
{
    int num=0;
    QPieSeries * p_series = new QPieSeries(graphParent);
    foreach(Record r, filters.filteredRecords())
    {
        //qDebug() << r.User();
        p_series->append(r.User(),r.Seconds());
        QString webName = r.Domain().split('.').at(1);
        p_series->slices().at(num)->setLabel(r.User()+", "+webName);
        p_series->slices().at(num)->setLabelVisible(true);
        num++;
    }

    QChart * p_chart = new QChart();
    p_chart->addSeries(p_series);
    p_chart->setAnimationOptions(QChart::AllAnimations);
    //p_chart->setTitle("Piechart placeholder");
    p_chart->legend()->setAlignment(Qt::AlignBottom);

    return p_chart;
}

QChart * Graph::barChart(Filters filters)
{
    QStringList groups(filters.listUsers(true));
    QBarSeries *series= new QBarSeries();
    int high = 0;

    foreach(QString cat, filters.listCategories(true))
    {
        QBarSet * set = new QBarSet(cat);
        foreach(QString emp, filters.listUsers(true))
        {
            int totalTime = filters.totalTimeFor(nullptr,emp,cat,nullptr);
            *set << totalTime;
            if(high < totalTime)
                high = totalTime;
        }
        series->append(set);
    }

    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Bar Chart");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(groups);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0,high);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    return chart;
}
