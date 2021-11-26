#include "mainwin.h"
#include "ui_mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"
#include <QMessageBox>
#include <QPixmap>


MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    DatabaseHandler * dbHandler = DatabaseHandler::getInstance();
    // first, user needs to login
    LoginWin * login = new LoginWin(dbHandler, this);
    m_currentUser = login->exec();

    //check that user is valid before launching the window
    if(m_currentUser == 1)
    {
        ui->setupUi(this);
        ui->line_chart->addGraph();
        ui->line_chart->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        ui->line_chart->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->line_chart->xAxis->setLabel("X");
        ui->line_chart->yAxis->setLabel("Y");
        ui->line_chart->xAxis->setRange(0,1000);
        ui->line_chart->yAxis->setRange(0,1000);
        ui->line_chart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        QVector <double> x={1,2,3,4,5},y={0,9,18,5,30};
        ui->line_chart->graph(0)->setData(x,y);
        ui->line_chart->rescaleAxes();
        ui->line_chart->replot();
        ui->line_chart->update();





        connect(ui->m_button, &QPushButton::clicked, this, &MainWin::on_m_button_clicked);

    }
    else
    {
        // since this is the top-level window, closing it will cause
        // app to quit
        this->close();
    }
}

MainWin::~MainWin()
{
    delete ui;
}


void MainWin::on_database_button_clicked()
{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("remotemysql.com");
//    db.setDatabaseName("JfadHzJmgq");
//    db.setUserName("JfadHzJmgq");
//    db.setPassword("mpPExijexc");


//    if(db.open()){
//        QMessageBox::information(this,"Connection","Databse Connected.");
//    }else{
//        QMessageBox::information(this,"Connection","Cannnot connected to database.");
//    }


//    QSqlQuery query;
//    query.prepare("SELECT emp_username FROM supervises WHERE super_username='super1';");
//    query.exec();

//        if(query.size()>0){
//            while(query.next()){
//                QString emp_username=query.value(0).toString().toUtf8().constData();
//                qDebug() <<emp_username;
//                qDebug() << "/ " ;

//            }

//        }else{

//        }




}

//menu animation
void MainWin::on_m_button_clicked()
{
    int px=ui->menu->x();

    if(px==0){
        px=-203;
    }
    else if(px==(-203)){
        px=203;
    }
    else{
        px=0;
    }

    animation1= new QPropertyAnimation(ui->menu, "geometry");
    animation1->setDuration(900);
    QRect startRect1(ui->menu->geometry());
    QRect endRect1(ui->menu->geometry().translated(px, 0));
    animation1->setStartValue(startRect1);//QPoint(btnRight,btnBottom));//QPoint(0,0));
    animation1->setEndValue(endRect1);//QPoint(100,100))
    animation1->setEasingCurve(QEasingCurve::InOutQuad);


    animation2= new QPropertyAnimation(ui->ui_panel, "geometry");
    animation2->setDuration(900);
    QRect startRect2(ui->ui_panel->geometry());
    QRect endRect2(ui->ui_panel->x()+px,ui->ui_panel->y(),ui->ui_panel->width()-px,ui->ui_panel->height());
    animation2->setStartValue(startRect2);//QPoint(btnRight,btnBottom));//QPoint(0,0));
    animation2->setEndValue(endRect2);//QPoint(100,100))
    animation2->setEasingCurve(QEasingCurve::InOutQuad);

    animationGroup = new QParallelAnimationGroup(this);
    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);

    animationGroup->start();
}

//header navigation functions
void MainWin::on_hide_button_clicked()
{
    this->hide();
}

void MainWin::on_resize_button_clicked(bool checked)
{
    if(checked){
        this->resize(1080,720);
    }
    else{
        this->showMaximized();
    }

}


//ui stack functions for buttons in the menu
void MainWin::on_workforce_button_clicked()
{
    ui->ui_stack->setCurrentIndex(0);
    ui->ui_title->setText("<h1>Workforce</h1>");
}

void MainWin::on_employee_button_clicked()
{
    ui->ui_stack->setCurrentIndex(1);
    ui->ui_title->setText("<h1>Employee</h1>");
}

void MainWin::on_website_button_clicked()
{
    ui->ui_stack->setCurrentIndex(2);
    ui->ui_title->setText("<h1>Website</h1>");
}

void MainWin::on_setting_button_clicked()
{
    ui->ui_stack->setCurrentIndex(3);
    ui->ui_title->setText("<h1>Setting</h1>");
}

//plot stack functions
void MainWin::on_bar_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(0);
}

void MainWin::on_pie_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(1);
}

void MainWin::on_line_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(2);
}




void MainWin::on_close_button_clicked()
{
    this->close();
}




//setting stack functions
void MainWin::on_user_button_clicked()
{
    ui->setting_stack->setCurrentIndex(0);

    model1 =new QSqlTableModel(this);
    model1->setQuery("SELECT * FROM user");
    model1->setHeaderData(0, Qt::Horizontal, tr("username"));
    model1->setHeaderData(1, Qt::Horizontal, tr("password"));
    model1->setHeaderData(2, Qt::Horizontal, tr("name"));
    model1->setHeaderData(3, Qt::Horizontal, tr("isAdmin"));
    model1->setHeaderData(4, Qt::Horizontal, tr("isSupervisor"));
    ui->user_table_view->setModel(model1);
    ui->user_table_view->show();

    model2 =new QSqlTableModel(this);
    model2->setQuery("SELECT username FROM user");
    ui->user_list_view->setModel(model2);
    ui->user_combo_box->setModel(model2);

}

void MainWin::on_category_button_clicked()
{
    ui->setting_stack->setCurrentIndex(1);
}

//edit user functions
void MainWin::on_user_save_button_clicked()
{
    QString username,password,name;
    int  is_admin,is_supervisor;
    username=ui->username_line_edit->text();
    password=ui->password_line_edit->text();
    name=ui->real_name_line_edit->text();

    if(ui->admin_check_box->isChecked()){
        is_admin=1;
    }else{
        is_admin=0;
    }

    if(ui->supervisor_check_box->isChecked()){
        is_supervisor=1;
    }else{
        is_supervisor=0;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO user(username,password,name,is_admin,is_supervisor)" "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(name);
    query.addBindValue(is_admin);
    query.addBindValue(is_supervisor);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Save","New user saved.");
        }else{
            QMessageBox::information(this,"Save","No user founded.");
        }

    }else{
        QMessageBox::information(this,"Save","Cannnot save to database.");
    }
}


void MainWin::on_user_update_button_clicked()
{
    QSqlQuery query;
    QString username,password,name;
    int  is_admin,is_supervisor;
    username=ui->username_line_edit->text();
    password=ui->password_line_edit->text();
    name=ui->real_name_line_edit->text();

    if(ui->admin_check_box->isChecked()){
        is_admin=1;
    }else{
        is_admin=0;
    }

    if(ui->supervisor_check_box->isChecked()){
        is_supervisor=1;
    }else{
        is_supervisor=0;
    }

    query.prepare("UPDATE user SET password=:password,name=:name,is_admin=:is_admin,is_supervisor=:is_supervisor WHERE username=:username");
    query.bindValue(":username",username);
    query.bindValue(":password",password);
    query.bindValue(":name",name);
    query.bindValue(":is_admin",is_admin);
    query.bindValue(":is_supervisor",is_supervisor);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Update","Updated user.");
        }else{
            QMessageBox::information(this,"Update","No user founded.");
        }
    }else{
        QMessageBox::information(this,"Update","Cannnot update database.");
    }
}


void MainWin::on_user_remove_button_clicked()
{
    QSqlQuery query;
    QString username;
    username=ui->username_line_edit->text();
    query.prepare("DELETE FROM user WHERE username = ?");
    query.addBindValue(username);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Remove","Removed user.");
        }else{
            QMessageBox::information(this,"Remove","No user founded.");
        }
    }else{
        QMessageBox::information(this,"Remove","Cannnot remove item in database.");
    }
}


void MainWin::on_user_combo_box_currentTextChanged(const QString &arg1)
{
    QString username=ui->user_combo_box->currentText();
    QSqlQuery query;
    qDebug() <<username;
    query.prepare("SELECT * FROM user WHERE username=:username ");
    query.bindValue(":username",username);
    if(query.exec()){
        while(query.next()){
            ui->username_line_edit->setText(query.value(0).toString());
            ui->password_line_edit->setText(query.value(1).toString());
            ui->real_name_line_edit->setText(query.value(2).toString());

            if(query.value(3).toInt()==1){
                ui->admin_check_box->setChecked(true);
            }

            if(query.value(4).toInt()==1){
                ui->supervisor_check_box->setChecked(true);
            }

        }
    }else{
        QMessageBox::information(this,"Display","Cannnot populate the fields.");
    }

}


