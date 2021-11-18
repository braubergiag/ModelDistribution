#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>

#include "Distribution.h"
#include "Generator.h"
#include "Histogram.h"
#include "TID_Generator.h"
#include "TISM_Generator.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_actionCreate_triggered()
{

    Dialog_model * dlg = new Dialog_model(this);
    if (m_chartView) {
        ui->verticalLayout_2->removeWidget(m_chartView);
    }
    dlg->exec();
    m_chartView = dlg->chartHistogram();

    load();
    //delete dlg;




}

QChartView *MainWindow::chartView() const
{
    return m_chartView;
}

void MainWindow::load()
{


    ui->verticalLayout_2->addWidget(m_chartView);
}

