#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtCore>
#include <QtCore/QCoreApplication>

#include <QMainWindow>
#include <QVector>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMessageBox>
#include <QPixmap>
#include <QWidget>
#include <QDebug>

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTextStream>

#include <QtCharts>
#include <QChartView>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>


#include "supervisor.h"
#include "employee.h"
#include "databasehandler.h"
#include "filters.h"
#include "graph.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();
    //void handleButton();
    QString currentUser;

private slots:
    void on_m_button_clicked();

    void on_bar_chart_button_clicked();

    void on_pie_chart_button_clicked();

    void on_line_chart_button_clicked();

    void on_workforce_button_clicked();

    void on_employee_button_clicked();

    void on_website_button_clicked();

    void on_setting_button_clicked();

    void on_hide_button_clicked();

    void on_close_button_clicked();

    void on_resize_button_clicked(bool checked);

    void on_database_button_clicked();

    void on_user_button_clicked();

    void on_category_button_clicked();

    void on_user_save_button_clicked();

    void on_user_update_button_clicked();

    void on_user_remove_button_clicked();

    void on_user_combo_box_currentTextChanged(const QString &arg1);

    void handleLogin(QString user);

    void on_employee_combo_box_currentTextChanged(const QString &arg1);

    void on_category_combo_box_currentTextChanged(QString cat);

    void on_e_bar_chart_button_clicked();

    void on_e_line_chart_button_clicked();

    void on_e_pie_chart_button_clicked();

    void on_upload_button_clicked();

    void on_browse_button_clicked();

    void on_OK_button_clicked();

    void on_w_save_button_clicked();

    void on_w_remove_button_clicked();

    void on_c_add_new_button_clicked();

    void on_c_remove_button_clicked();

private:
    Ui::MainWin *ui;

    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QParallelAnimationGroup* animationGroup;

    QSqlQueryModel *model1;
    QSqlQueryModel *model2;
    DatabaseHandler *m_dbh;

    Supervisor m_supervisor;
    Employee m_employee;
    QList<Record> m_records;
    QList<Record> m_graphData;
    Filters m_filters;

    QSqlQueryModel *c_model;

    Graph * m_graph;

    QChart *p_chart;
    QChartView *p_chartView;

    QChart *b_chart;
    QChartView *b_chartView;

    //TODO: Change this to be class with more information about the user
    int m_currentUser;
};
#endif // MAINWIN_H
