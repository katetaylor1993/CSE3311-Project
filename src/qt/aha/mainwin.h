#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QVector>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QMessageBox>
#include <QPixmap>
#include <QWidget>

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

private:
    Ui::MainWin *ui;
    QPropertyAnimation *animation1;
    QPropertyAnimation *animation2;
    QParallelAnimationGroup* animationGroup;

    //TODO: Change this to be class with more information about the user
    int m_currentUser;
};
#endif // MAINWIN_H
