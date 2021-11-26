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

private:
    Ui::MainWin *ui;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QParallelAnimationGroup* animationGroup;
    QSqlQueryModel *model1;
    QSqlQueryModel *model2;

    //TODO: Change this to be class with more information about the user
    int m_currentUser;
};
#endif // MAINWIN_H
