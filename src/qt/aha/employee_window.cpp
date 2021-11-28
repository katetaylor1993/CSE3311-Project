#include "employee_window.h"
#include "ui_employee_window.h"
#include <QFileDialog>
#include <QMessageBox>

employee_window::employee_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employee_window)
{
    ui->setupUi(this);
}

employee_window::~employee_window()
{
    delete ui;
}

void employee_window::on_browse_button_clicked()
{
    QString filter ="All Filer (*.*)";
    QString file_name=QFileDialog::getOpenFileName(this,"Open a file","C://",filter);
    ui->file_name_line_edit->setText(file_name);
}


void employee_window::on_OK_button_clicked()
{

}

//header navigation functions
void employee_window::on_hide_button_clicked()
{
    this->hide();
}

void employee_window::on_resize_button_clicked(bool checked)
{
    if(checked){
        this->resize(1080,720);
    }
    else{
        this->showMaximized();
    }
}

void employee_window::on_close_button_clicked()
{
    this->close();
}



