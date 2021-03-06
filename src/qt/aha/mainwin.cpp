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
      m_supervisor(Supervisor()),
      m_employee(Employee())
{
    m_dbh = DatabaseHandler::getInstance();

    connect(m_dbh,SIGNAL(loggedIn(QString)),this,SLOT(handleLogin(QString)));

    //m_dbh->exportData("C:\\Users\\kathe\\Downloads\\domains.csv","emp4");

    // first, user needs to login
    LoginWin * login = new LoginWin(m_dbh, this);

    //TODO: make connections between database and mainwin for employe and sup login
    m_currentUser = login->exec();

    if(m_currentUser==1)
    {
        ui->setupUi(this);

        //feeding infomation into comboboxes
        m_records = m_dbh->getAllRecords(m_supervisor.m_employees);
        m_filters = Filters(m_records);
        m_graph = new Graph(this);

        connect(ui->m_button, &QPushButton::clicked, this, &MainWin::on_m_button_clicked);

        QString all = QString("Select All");
        this->ui->e_employee_combo_box->addItem(all);
        foreach(Employee e, m_supervisor.m_employees)
        {
            this->ui->e_employee_combo_box->addItem(e.Name());
        }
        this->ui->e_employee_combo_box->setCurrentIndex(this->ui->e_employee_combo_box->findData(all));

        this->ui->website_combo_box->addItem(all);
        QList<QString> websites = m_filters.listWebsites(false);
        foreach(QString w, websites)
        {
            this->ui->website_combo_box->addItem(w);
            this->ui->e_website_combo_box->addItem(w);
            //this->ui->domain_combo_box->addItem(w);
        }
        this->ui->website_combo_box->setCurrentIndex(this->ui->website_combo_box->findData(all));

        this->ui->category_combo_box->addItem(all);
        QList<QString> categories = m_filters.listCategories(false);
        foreach(QString c, categories)
        {
            this->ui->category_combo_box->addItem(c);
            this->ui->e_category_combo_box->addItem(c);
            //this->ui->w_category_combo_box->addItem(c);
        }
        this->ui->category_combo_box->setCurrentIndex(this->ui->category_combo_box->findData(all));


        //barchart
        b_chart = m_graph->barChart(m_filters);
        b_chartView = new QChartView(b_chart);
        b_chartView->setRenderHint(QPainter::Antialiasing);
        b_chartView->setParent(ui->bar_frame);
        //chartView->setParent(ui->e_bar_table_view);

        //pie chart
        p_chart = m_graph->pieChart(m_filters);
        p_chartView = new QChartView(p_chart);
        p_chartView->setRenderHint(QPainter::Antialiasing);
        p_chart->layout()->setContentsMargins(0,0,0,0);
        p_chartView->setParent(ui->pie_frame);

        //table on workforce > bar chart page
        QStandardItemModel *model = new QStandardItemModel();
        QStringList hHeader;
        hHeader.append("Employee Name");
        hHeader.append("Website Category");
        hHeader.append("Website");
        hHeader.append("Time (Seconds)");
        hHeader.append("Date");
        model->setHorizontalHeaderLabels(hHeader);
        foreach(Record r, m_filters.filteredRecords())
        {
            QList<QStandardItem*> row;
            row << new QStandardItem(r.User())
                << new QStandardItem(r.Category())
                << new QStandardItem(r.Domain())
                << new QStandardItem(QString::number(r.Seconds()))
                << new QStandardItem(r.Date().toString());
            model->appendRow(row);
        }
        ui->bar_chart_table_view->setModel(model);
        ui->bar_chart_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //table on pie chart page
        QStandardItemModel *model2 = new QStandardItemModel();
        QStringList hHeader2;
        hHeader2.append("Employee");
        hHeader2.append("Website");
        hHeader2.append("Time (Seconds)");
        model2->setHorizontalHeaderLabels(hHeader2);
        foreach(QString e, m_filters.listUsers(true))
        {
            foreach(QString w, m_filters.listWebsites(true))
            {
                QList<QStandardItem*> row;
                row << new QStandardItem(e)
                    << new QStandardItem(w)
                    << new QStandardItem(QString::number(m_filters.totalTimeFor(nullptr,e,nullptr,w)));
                model2->appendRow(row);
            }
        }
        ui->pie_chart_table_view->setModel(model2);
        ui->pie_chart_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

        //line chart
        QVector <double> dataX={1,2,3,4,5},dataY={0,9,18,5,30};
        //QVector<double> dataX;
        //QVector<double> dataY;
        QDate start = m_filters.firstDateOfRecords();
        QDate end = m_filters.lastDateOfRecords();
        int numDays = start.daysTo(end);
        ui->line_chart->addGraph();
        ui->line_chart->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        ui->line_chart->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->line_chart->xAxis->setLabel("Day");
        ui->line_chart->yAxis->setLabel("Time (Seconds)");
        ui->line_chart->xAxis->setRange(0,1000);
        ui->line_chart->yAxis->setRange(0,1000);
        ui->line_chart->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);
        ui->line_chart->graph(0)->setData(dataX,dataY);
        ui->line_chart->rescaleAxes();
        ui->line_chart->replot();
        ui->line_chart->update();

        ui->line_chart_2->addGraph();
        ui->line_chart_2->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
        ui->line_chart_2->graph(0)->setLineStyle(QCPGraph::lsLine);
        ui->line_chart_2->xAxis->setLabel("X");
        ui->line_chart_2->yAxis->setLabel("Y");
        ui->line_chart_2->xAxis->setRange(0,1000);
        ui->line_chart_2->yAxis->setRange(0,1000);
        ui->line_chart_2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);
        ui->line_chart_2->graph(0)->setData(dataX,dataY);
        ui->line_chart_2->rescaleAxes();
        ui->line_chart_2->replot();
        ui->line_chart_2->update();

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        QValueAxis *axisY = new QValueAxis();
        //percentbarchart
        QBarSet *eb_set0 = new QBarSet("Jane");
        QBarSet *eb_set1 = new QBarSet("John");
        QBarSet *eb_set2 = new QBarSet("Axel");
        QBarSet *eb_set3 = new QBarSet("Mary");
        QBarSet *eb_set4 = new QBarSet("Samantha");

        *eb_set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *eb_set1 << 5 << 0 << 0 << 4 << 0 << 7;
        *eb_set2 << 3 << 5 << 8 << 13 << 8 << 5;
        *eb_set3 << 5 << 6 << 7 << 3 << 4 << 5;
        *eb_set4 << 9 << 7 << 5 << 3 << 1 << 2;

        QPercentBarSeries *eb_series = new QPercentBarSeries();
        eb_series->append(eb_set0);
        eb_series->append(eb_set1);
        eb_series->append(eb_set2);
        eb_series->append(eb_set3);
        eb_series->append(eb_set4);

        QChart *eb_chart = new QChart();
        eb_chart->addSeries(eb_series);
        eb_chart->setTitle("Percentbarchart placeholder");
        eb_chart->setAnimationOptions(QChart::SeriesAnimations);

        QStringList eb_categories;
        eb_categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
        QBarCategoryAxis *eb_axisX = new QBarCategoryAxis();
        axisX->append(eb_categories);
        eb_chart->addAxis(eb_axisX, Qt::AlignBottom);
        eb_series->attachAxis(eb_axisX);
        QValueAxis *eb_axisY = new QValueAxis();
        b_chart->addAxis(eb_axisY, Qt::AlignLeft);
        eb_series->attachAxis(eb_axisY);

        eb_chart->legend()->setVisible(true);
        eb_chart->legend()->setAlignment(Qt::AlignBottom);

        QChartView *eb_chartView = new QChartView(eb_chart);
        eb_chartView->setRenderHint(QPainter::Antialiasing);
        eb_chartView->setParent(ui->e_bar_frame);


        //donuts
        QPieSeries *dc_series = new QPieSeries();
        dc_series->setHoleSize(0.35);
        dc_series->append("Protein 4.2%", 4.2);
        QPieSlice *dc_slice = dc_series->append("Fat 15.6%", 15.6);
        dc_slice->setExploded();
        dc_slice->setLabelVisible();
        dc_series->append("Other 23.8%", 23.8);
        dc_series->append("Carbs 56.4%", 56.4);
        QChart *dc_chart = new QChart();
        dc_chart->setAnimationOptions(QChart::SeriesAnimations);
        QChartView *dc_chartView = new QChartView();
        dc_chartView->setRenderHint(QPainter::Antialiasing);
        dc_chartView->chart()->setTitle("Donut with a lemon glaze (100g)");
        dc_chartView->chart()->addSeries(dc_series);
        dc_chartView->chart()->legend()->setAlignment(Qt::AlignBottom);
        dc_chartView->setParent(ui->e_pie_frame);

        //connect(this->ui->category_combo_box,SIGNAL(currentTextChanged(QString)),this,SLOT(on_category_combo_box_currentTextChanged(Qstring)));
        connect(this->ui->database_button,SIGNAL(clicked()),this,SLOT(on_database_button_clicked()));
    }
    else
    {
        //showing the employee window
        employee_window emp_win = employee_window(m_employee,this);
        emp_win.exec();
        this->close();
    }
}

MainWin::~MainWin()
{
    delete ui;
     delete m_graph;
}

void MainWin::handleLogin(QString user)
{
    User * thisUser = m_dbh->getUserInfo(user);
    if(thisUser->isSupervisor())
    {
        m_supervisor = *reinterpret_cast<Supervisor *>(thisUser);
    }
    else
    {
        m_employee = *reinterpret_cast<Employee *>(thisUser);
    }
}



void MainWin::on_database_button_clicked()
{
    QString cat = this->ui->category_combo_box->currentText();
    QString web = this->ui->website_combo_box->currentText();
    qDebug() << "On DB Clicked: "+cat+", "+web;
    QList<QString> cfilt;
    QList<QString> wfilt;
    if(cat != "Select All" && cat != "")
    {
        cfilt.append(cat);
        m_filters.setCategories(cfilt);
    }
    else
        m_filters.clearCategories();

    if(web != "Select All" && cat != "")
    {
        wfilt.append(web);
        m_filters.setWebsites(wfilt);
    }
    else
        m_filters.clearWebsites();

    //barchart
    b_chart = m_graph->barChart(m_filters);
    b_chartView->setChart(m_graph->barChart(m_filters));

    //pie chart
    p_chart = m_graph->pieChart(m_filters);
    p_chartView->setChart(m_graph->pieChart(m_filters));


    QStandardItemModel *model = new QStandardItemModel();
    QStringList hHeader;
    hHeader.append("Employee Name");
    hHeader.append("Website Category");
    hHeader.append("Website");
    hHeader.append("Time (Seconds)");
    hHeader.append("Date");
    model->setHorizontalHeaderLabels(hHeader);
    foreach(Record r, m_filters.filteredRecords())
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(r.User())
            << new QStandardItem(r.Category())
            << new QStandardItem(r.Domain())
            << new QStandardItem(QString::number(r.Seconds()))
            << new QStandardItem(r.Date().toString());
        model->appendRow(row);
    }
    ui->bar_chart_table_view->setModel(model);

    //table on pie chart page
    QStandardItemModel *model2 = new QStandardItemModel();
    QStringList hHeader2;
    hHeader2.append("Employee");
    hHeader2.append("Website");
    hHeader2.append("Time (Seconds)");
    model2->setHorizontalHeaderLabels(hHeader2);
    foreach(QString e, m_filters.listUsers(true))
    {
        foreach(QString w, m_filters.listWebsites(true))
        {
            QList<QStandardItem*> row;
            row << new QStandardItem(e)
                << new QStandardItem(w)
                << new QStandardItem(QString::number(m_filters.totalTimeFor(nullptr,e,nullptr,w)));
            model2->appendRow(row);
        }
    }
    ui->pie_chart_table_view->setModel(model2);

    if(ui->bar_chart_table_view->isVisible())
        ui->bar_chart_table_view->repaint();
    if(ui->pie_chart_table_view->isVisible())
        ui->pie_chart_table_view->repaint();
    b_chartView->repaint();
    p_chartView->repaint();
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

    QStandardItemModel *model = new QStandardItemModel();
    QStringList hHeader;
    hHeader.append("Website");
    hHeader.append("Category");
    QMap<QString, QString>::iterator i;
    for(i=m_dbh->m_catMap.begin(); i!=m_dbh->m_catMap.end(); ++i)
    {
        QList<QStandardItem*> row;
        row << new QStandardItem(i.key())
            << new QStandardItem(i.value());
        model->appendRow(row);
    }
    ui->website_table_view->setModel(model);
    ui->website_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->website_table_view->show();
}

void MainWin::on_setting_button_clicked()
{
    ui->ui_stack->setCurrentIndex(3);
    ui->ui_title->setText("<h1>Setting</h1>");
    on_user_button_clicked();
}

//plot stack functions
void MainWin::on_bar_chart_button_clicked()
{
    ui->plot_stack->setCurrentIndex(0);
    ui->bar_chart_table_view->show();
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
    ui->user_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //ui->user_table_view->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->user_table_view->show();

    model2 =new QSqlTableModel(this);
    model2->setQuery("SELECT username FROM user");
    ui->user_combo_box->setModel(model2);

}

void MainWin::on_category_button_clicked()
{
    ui->setting_stack->setCurrentIndex(1);
    c_model =new QSqlTableModel(this);
    c_model->setQuery("SELECT * FROM category");
    c_model->setHeaderData(0, Qt::Horizontal, tr("category"));
    c_model->setHeaderData(1, Qt::Horizontal, tr("description"));

    ui->category_table_view->setModel(c_model);
    ui->category_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->category_table_view->show();
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
    on_user_button_clicked();
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
    on_user_button_clicked();
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
    on_user_button_clicked();
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


void MainWin::on_category_combo_box_currentTextChanged(QString cat)
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


void MainWin::on_browse_button_clicked()
{
    QString filter ="All Filer (*.*)";
    QString file_name=QFileDialog::getOpenFileName(this,"Open a file","C://",filter);
    ui->file_name_line_edit->setText(file_name);
}


void MainWin::on_OK_button_clicked()
{
    int ret = DatabaseHandler::getInstance()->exportData(ui->file_name_line_edit->text(),m_employee.Username());
    if(ret == 1)
    {
        ui->file_name_line_edit->setText("There was an issue with file.");
    }

}


void MainWin::on_w_save_button_clicked()
{
    QString site_name,category;
    site_name=ui->domain_line_edit->text();
    category=ui->w_category_line_edit->text();

    m_dbh->setCategory(site_name, category);

    /*
    QSqlQuery query;
    query.prepare("INSERT INTO website (site_name,category)" "VALUES (?, ?)");
    query.addBindValue(site_name);
    query.addBindValue(category);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Website","New website saved.");
        }else{
            QMessageBox::information(this,"Website","No website founded.");
        }

    }else{
        QMessageBox::information(this,"Website","Cannnot save to database.");
    }
    on_website_button_clicked();
    */

}


void MainWin::on_w_remove_button_clicked()
{
    QString site_name;
    site_name=ui->domain_line_edit->text();
    QSqlQuery query;
    query.prepare("DELETE FROM website WHERE site_name = ?");
    query.addBindValue(site_name);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Website","Website removed.");
        }else{
            QMessageBox::information(this,"Website","No website founded.");
        }
    }else{
        QMessageBox::information(this,"Website","Cannnot remove item in database.");
    }
    on_website_button_clicked();
}


void MainWin::on_c_add_new_button_clicked()
{
    QString category,description;
    category=ui->categoty_line_edit->text();
    description=ui->description_line_edit->text();

    QSqlQuery query;
    query.prepare("INSERT INTO category (category,description)" "VALUES (?, ?)");
    query.addBindValue(category);
    query.addBindValue(description);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Category","New category saved.");
        }else{
            QMessageBox::information(this,"Category","No category founded.");
        }

    }else{
        QMessageBox::information(this,"Category","Cannnot save to database.");
    }
    on_category_button_clicked();
}


void MainWin::on_c_remove_button_clicked()
{
    QString category;
    category=ui->domain_line_edit->text();
    QSqlQuery query;
    query.prepare("DELETE FROM category WHERE category = ?");
    query.addBindValue(category);

    if(query.exec()){
        if(query.numRowsAffected()>0){
            QMessageBox::information(this,"Category","Category removed.");
        }else{
            QMessageBox::information(this,"Category","No category founded.");
        }
    }else{
        QMessageBox::information(this,"Category","Cannnot remove item in database.");
    }
    on_category_button_clicked();
}

