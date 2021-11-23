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

//        ui->comboBox->addItem("Career and education");
//        ui->comboBox->addItem("News and media");
//        ui->comboBox->addItem("Internet and telecom");





        connect(ui->m_button, &QPushButton::clicked, this, &MainWin::on_m_button_clicked);

    }
    else
    {
        // since this is the top-level window, closing it will cause
        // app to quit
        this->close();
        //here's an extra test comment
    }
}

MainWin::~MainWin()
{
    delete ui;
}

//void MainWin::handleButton()
//{
////Create animation
//QPropertyAnimation *animation = new QPropertyAnimation(menu, "geometry");
//animation->setDuration(1000);
//QRect startRect(-100,50,50,200);
//QRect endRect(50,50,50,200);
//animation->setStartValue(startRect);//QPoint(btnRight,btnBottom));//QPoint(0,0));
//animation->setEndValue(endRect);//QPoint(100,100))
//animation->start();
//}


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

//    int w=ui->main_panel->width();

//    if (w==1717){
//        w=1920;
//    }
//    else if (w==1920){
//        w==1717;
//    }
//    else{
//       w=w;
//    }

    animation1= new QPropertyAnimation(ui->menu, "geometry");
    animation1->setDuration(1000);
    QRect startRect1(ui->menu->geometry());
    QRect endRect1(ui->menu->geometry().translated(px, 0));
    animation1->setStartValue(startRect1);//QPoint(btnRight,btnBottom));//QPoint(0,0));
    animation1->setEndValue(endRect1);//QPoint(100,100))
    animation1->setEasingCurve(QEasingCurve::InOutQuad);
//    animation1->start();


    animation2= new QPropertyAnimation(ui->ui_panel, "geometry");
    animation2->setDuration(1000);
    QRect startRect2(ui->ui_panel->geometry());
    QRect endRect2(ui->ui_panel->x()+px,ui->ui_panel->y(),ui->ui_panel->width()-px,ui->ui_panel->height());
    animation2->setStartValue(startRect2);//QPoint(btnRight,btnBottom));//QPoint(0,0));
    animation2->setEndValue(endRect2);//QPoint(100,100))
    animation2->setEasingCurve(QEasingCurve::InOutQuad);
//    animation2->start();

    animationGroup = new QParallelAnimationGroup(this);
    animationGroup->addAnimation(animation1);
    animationGroup->addAnimation(animation2);

    animationGroup->start();
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

//ui stack functions
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

