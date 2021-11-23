#include "mainwin.h"
#include "ui_mainwin.h"
#include "loginwin.h"
#include <QMessageBox>
#include <QPixmap>

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
        ui->customplot->addGraph();
        ui->customplot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        ui->customplot->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->customplot->xAxis->setLabel("X");
        ui->customplot->yAxis->setLabel("Y");
        ui->customplot->xAxis->setRange(0,1000);
        ui->customplot->yAxis->setRange(0,1000);
        ui->customplot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        QVector <double> x={1,2,3,4,5},y={0,9,18,5,30};
        ui->customplot->graph(0)->setData(x,y);
        ui->customplot->rescaleAxes();
        ui->customplot->replot();
        ui->customplot->update();

//        ui->comboBox->addItem("Career and education");
//        ui->comboBox->addItem("News and media");
//        ui->comboBox->addItem("Internet and telecom");

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

