#include "mainwin.h"
#include "loginwin.h"
#include "databasehandler.h"

#include <iostream>
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QStyleOptionTitleBar>
#include<QDebug>


DatabaseHandler * DatabaseHandler::obj;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DatabaseHandler::getInstance()->connectToDB();


    MainWin w;


    w.setWindowState(Qt::WindowMaximized);
    w.setWindowTitle("Aha");
    w.show();

//    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("remotemysql.com");
//    db.setDatabaseName("JfadHzJmgq");
//    db.setUserName("JfadHzJmgq");
//    db.setPassword("mpPExijexc");


//    if(db.open()){
//        qDebug("Databse Connected!");
//        //QMessageBox::information(this,"Connection","Databse Connected.");
//    }else{
//        qDebug("Cannnot connected to database.");
//        //QMessageBox::information(this,"Connection","Cannnot connected to database.");
//    }

//    QString emp_username;
//    QSqlQuery query;
//    query.prepare("SELECT emp_username FROM supervises WHERE super_username='super1';");
//    query.exec();
//    if(query.size()>0){
//        while(query.next()){
//            emp_username=query.value("emp_username").toString().toUtf8().constData();
//            qDebug() << emp_username;

//        }

//    }else{

//    }

    return app.exec();
}
