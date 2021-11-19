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

    dlg->exec();
    clearLayout();
    widget = new QWidget(this);
    m_chartView = dlg->chartHistogram();
    if (m_chartView){
        load();
    }

    delete dlg;




}

QChartView *MainWindow::chartView() const
{
    return m_chartView;
}

void MainWindow::load()
{


    ui->verticalLayout_2->addWidget(m_chartView);
}

void MainWindow::loadPlevelsChart() const
{
    ui->verticalLayout_2->addWidget(m_chartPlevels);
}


void MainWindow::on_actionGenerate_P_Levels_triggered()
{

    Dialog_Plevels * dlg = new Dialog_Plevels(this);

    dlg->exec();
    clearLayout();
    m_chartPlevels = dlg->chartPlevels();
    if (m_chartPlevels){
         loadPlevelsChart();
    }


    delete dlg;
}

QChartView *MainWindow::chartPlevels() const
{
    return m_chartPlevels;
}

void MainWindow::clearLayout()
{
    if (m_chartPlevels) {
        ui->verticalLayout_2->removeWidget(m_chartPlevels);
        m_chartPlevels = nullptr;

    } else if (m_chartView) {
        ui->verticalLayout_2->removeWidget(m_chartView);
        m_chartView =  nullptr;
    }

    qDebug() << ui->verticalLayout_2->isEmpty();
    ui->verticalLayout_2->update();
}

