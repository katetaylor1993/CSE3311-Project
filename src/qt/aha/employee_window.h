#ifndef EMPLOYEE_WINDOW_H
#define EMPLOYEE_WINDOW_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class employee_window;
}

class employee_window : public QDialog
{
    Q_OBJECT

public:
    explicit employee_window(Employee e, QWidget *parent = nullptr);
    ~employee_window();

private slots:
    void on_browse_button_clicked();

    void on_OK_button_clicked();

    void on_hide_button_clicked();

    void on_resize_button_clicked(bool checked);

    void on_close_button_clicked();

private:
    Ui::employee_window *ui;
    Employee m_employee;
};

#endif // EMPLOYEE_WINDOW_H
