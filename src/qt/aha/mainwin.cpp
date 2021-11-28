#include "mainwin.h"
#include "ui_mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"
#include "employee_window.h"

#include <QMessageBox>
#include <QPixmap>
#include <QThread>
#include <QHBoxLayout>


MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin),
      m_supervisor(Supervisor())
{
    m_dbh = DatabaseHandler::getInstance();

    connect(m_dbh,SIGNAL(loggedIn(QString)),this,SLOT(handleLogin(QString)));

    m_dbh->exportData("C:\\Users\\kathe\\Downloads\\domains.csv","emp4");

    // first, user needs to login
    LoginWin * login = new LoginWin(m_dbh, this);

    //TODO: make connections between database and mainwin for employe and sup login
    m_currentUser = login->exec();

    if(m_currentUser==1)
    {
        ui->setupUi(this);


        QBarSet *set0 = new QBarSet("Bob");
        QBarSet *set1 = new QBarSet("Tom");
        QBarSet *set2 = new QBarSet("John");
        QBarSet *set3 = new QBarSet("Doe");
        QBarSet *set4 = new QBarSet("Ahmad");

        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;
        *set3 << 5 << 6 << 7 << 3 << 4 << 5;
        *set4 << 9 << 7 << 5 << 3 << 1 << 2;

        QBarSeries *series= new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->append(set3);
        series->append(set4);

        QChart *chart=new QChart();
        chart->addSeries(series);
        chart->setTitle("Bar Chart");
        chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList type;
        type << "Jan" << "Feb" << "Mar" << "Apr"<<"May"<< "Jun";
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(type);
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0,15);
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *chartView=new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setParent(ui->bar_frame);



        QString random="Joe";
        double x=2;
        p_series = new QPieSeries(this);
        p_series->append("Jane", 1);
        p_series->append(random,x);
        p_series->append("Andy", 3);
        p_series->append("Barbara", 4);
        p_series->append("Axel", 5);

        QPieSlice *slice0 = p_series->slices().at(0);
        slice0->setLabelVisible();
        QPieSlice *slice1 = p_series->slices().at(1);
        slice1->setExploded(true);
        slice1->setLabelVisible();
        slice1->setPen(QPen(Qt::darkGreen, 2));
        slice1->setBrush(Qt::green);
        QPieSlice *slice2 = p_series->slices().at(2);
        slice2->setLabelVisible();
        QPieSlice *slice3 = p_series->slices().at(3);
        slice3->setLabelVisible();
        QPieSlice *slice4 = p_series->slices().at(4);
        slice4->setLabelVisible();

        p_chart = new QChart();
        p_chart->addSeries(p_series);
        p_chart->setAnimationOptions(QChart::AllAnimations);
        p_chart->setTitle("Piechart example");
        p_chart->legend()->hide();

        p_chartView = new QChartView(p_chart);
        p_chartView->mapToScene(ui->pie_frame->x(),ui->pie_frame->y(),ui->pie_frame->width(),ui->pie_frame->height());
        p_chartView->setRenderHint(QPainter::Antialiasing);
        p_chartView->setParent(ui->pie_frame);






//        ui->line_chart->addGraph();
//        ui->line_chart->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
//        ui->line_chart->graph(0)->setLineStyle(QCPGraph::lsLine);
//        ui->line_chart->xAxis->setLabel("X");
//        ui->line_chart->yAxis->setLabel("Y");
//        ui->line_chart->xAxis->setRange(0,1000);
//        ui->line_chart->yAxis->setRange(0,1000);
//        ui->line_chart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

//        QVector <double> x={1,2,3,4,5},y={0,9,18,5,30};
//        ui->line_chart->graph(0)->setData(x,y);
//        ui->line_chart->rescaleAxes();
//        ui->line_chart->replot();
//        ui->line_chart->update();

        connect(ui->m_button, &QPushButton::clicked, this, &MainWin::on_m_button_clicked);

        foreach(Employee e, m_supervisor.m_employees)
        {
            this->ui->e_employee_combo_box->addItem(e.Name());
        }

        m_records = m_dbh->getAllRecords(m_supervisor.m_employees);
        m_filters = Filters(m_records);

        QList<QString> websites = m_filters.listWebsites();
        foreach(QString w, websites)
        {
            this->ui->website_combo_box->addItem(w);
            this->ui->e_website_combo_box->addItem(w);
        }

        QList<QString> categories = m_filters.listCategories();
        foreach(QString c, categories)
        {
            this->ui->category_combo_box->addItem(c);
        }
    }
    else
    {
        hide();
        employee_window employee_window;
        employee_window.show();

    }
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::handleLogin(QString user)
{
    User * thisUser = m_dbh->getUserInfo(user);
    if(thisUser->isSupervisor())
    {
        m_supervisor = *reinterpret_cast<Supervisor *>(thisUser);
    }
}



void MainWin::on_database_button_clicked()
{


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

void MainWin::on_close_button_clicked()
{
    this->close();
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

    p_model =new QSqlTableModel(this);
    p_model->setQuery("SELECT * FROM category");
    p_model->setHeaderData(0, Qt::Horizontal, tr("category"));
    p_model->setHeaderData(1, Qt::Horizontal, tr("count"));

    ui->pie_chart_table_view->setModel(p_model);
    ui->pie_chart_table_view->show();

}

void MainWin::on_line_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(1);
}


void MainWin::on_pie_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(2);

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



void MainWin::on_employee_combo_box_currentTextChanged(const QString &arg1)
{

}


void MainWin::on_category_combo_box_currentTextChanged(const QString &arg1)
{

}



//employee ui buttons
void MainWin::on_e_bar_chart_button_clicked()
{
    ui->e_plot_stack->setCurrentIndex(0);
}

void MainWin::on_e_line_chart_button_clicked()
{
    ui->e_plot_stack->setCurrentIndex(1);
}

void MainWin::on_e_pie_chart_button_clicked()
{
    ui->e_plot_stack->setCurrentIndex(2);
}

void MainWin::on_upload_button_clicked()
{
    ui->e_plot_stack->setCurrentIndex(3);
}

