#include "mainwin.h"
#include "ui_mainwin.h"
#include "loginwin.h"

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    // first, user needs to login
    LoginWin * login = new LoginWin(this);
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
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("remotemysql.com");
    db.setDatabaseName("JfadHzJmgq");
    db.setUserName("JfadHzJmgq");
    db.setPassword("mpPExijexc");


    if(db.open()){
        QMessageBox::information(this,"Connection","Databse Connected.");
    }else{
        QMessageBox::information(this,"Connection","Cannnot connected to database.");
    }

    qDebug() << "hi" ;



    QSqlQuery query;
    query.prepare("SELECT emp_username FROM supervises WHERE super_username='super1';");
    query.exec();

        if(query.size()>0){
            while(query.next()){
                QString emp_username=query.value(0).toString().toUtf8().constData();
                qDebug() <<emp_username;
                qDebug() << "/ " ;

            }

        }else{

        }




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

//    model =new QSqlTableModel(this);
//    model->setQuery("SELECT * FROM user");
//    model->setHeaderData(0, Qt::Horizontal, tr("username"));
//    model->setHeaderData(1, Qt::Horizontal, tr("password"));
//    model->setHeaderData(2, Qt::Horizontal, tr("name"));
//    model->setHeaderData(3, Qt::Horizontal, tr("isAdmin"));
//    model->setHeaderData(4, Qt::Horizontal, tr("isSupervisor"));
//    ui->user_table_view->setModel(model);
//    ui->user_table_view->show();

    model =new QSqlTableModel(this);
    model->setQuery("SELECT emp_username FROM supervises WHERE super_username='super1'");
    model->setHeaderData(0, Qt::Horizontal, tr("emp_username"));
    ui->user_table_view->setModel(model);
    ui->user_table_view->show();
}

void MainWin::on_category_button_clicked()
{
    ui->setting_stack->setCurrentIndex(1);
}

