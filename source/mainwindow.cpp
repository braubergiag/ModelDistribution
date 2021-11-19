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

    uint64_t demoSampleSize = 10000;
    Distribution d0({0.1,0.2,0.3,0.4});
    Generator * generator = new TID_Generator(d0);
    m_model = new Model(generator);
    m_model->setSampleSize(demoSampleSize);
    m_model->setD0(d0);
    m_model->InitHistogram();
    m_chartSampleHistogram = createChartHistogram(m_model->histogram());
    load();

}

MainWindow::~MainWindow()

{
    delete m_model;
    delete m_chartPlevels;
    delete m_chartSampleHistogram;
    delete ui;
}


QChartView * MainWindow::createChartHistogram(Histogram * histogram)
{


    histogram->calcChi();
    QBarSet *set0 = new QBarSet("Observed");
    QBarSet *set1 = new QBarSet("Expected");
    uint64_t maxYValue = histogram->MaxFrequency() + (0.1 *  histogram->MaxFrequency());


    for (const  auto& item : histogram->observedMerged()){
        *set0 << item.second;
    }
    for (const  auto& item : histogram->expectedMerged()){
        *set1 << item.second;
    }


    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);


    QChart *chart = new QChart();
    QString info = "Sample size: " + QString::number(histogram->sampleSize()) +
            "\t Chi-sqaure: " + QString::number(histogram->chi()) + "\t Degrees of freedom: " +
            QString::number(histogram->df()) + "\t P-value: " + QString::number(histogram->pvalue());



    ui->txtDistributionInfo->setText(info);
    chart->addSeries(series);
    chart->setTitle("Discrete Distribution Sample");

    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationOptions(QChart::GridAxisAnimations);


    QStringList categories;

    for (const  auto& item : histogram->observedMerged()){
        categories << QString::number(item.first);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();

    axisY->setRange(0,static_cast<uint64_t>(maxYValue));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return  chartView;
}

QChartView *MainWindow::createPlevelsChart(Model  * model)

{


    QBarSet *set0 = new QBarSet("Observed Plevel");
    QBarSet *set1 = new QBarSet("Expected Plevel");
     const uint64_t maxYValue = 1.1;


     for (const  auto& observedPlevel : model->plevelObservedCDF()){
         *set0 << observedPlevel;
     }

     for (const  auto& expectedPlevel : model->plevelsInteravals()){
         *set1 << expectedPlevel;
     }





     QBarSeries *series = new QBarSeries();
     series->append(set0);
     series->append(set1);



     QChart *chart = new QChart();





     chart->addSeries(series);
     chart->setTitle("Plevels CDFs");
     ui->txtDistributionInfo->setText("");
     chart->setAnimationOptions(QChart::SeriesAnimations);
     chart->setAnimationOptions(QChart::GridAxisAnimations);


     QStringList categories;

     for (const  auto& item : model->plevelsInteravals()){
         categories << QString::number(item);
     }


     QBarCategoryAxis *axisX = new QBarCategoryAxis();
     axisX->append(categories);
     chart->addAxis(axisX, Qt::AlignBottom);
     series->attachAxis(axisX);

     QValueAxis *axisY = new QValueAxis();

     axisY->setRange(0,static_cast<uint64_t>(maxYValue));
     chart->addAxis(axisY, Qt::AlignLeft);
     series->attachAxis(axisY);

     chart->legend()->setVisible(true);
     chart->legend()->setAlignment(Qt::AlignBottom);


     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     return  chartView;
}

void MainWindow::on_actionCreate_triggered()
{

    Dialog_model * dlg = new Dialog_model(this,m_model);

    dlg->exec();
    clearLayout();
    m_model->InitHistogram();
    m_chartSampleHistogram = createChartHistogram(m_model->histogram());
    if (m_chartSampleHistogram){
        load();
    }

    delete dlg;




}

QChartView *MainWindow::chartView() const
{
    return m_chartSampleHistogram;
}

void MainWindow::load()
{


    ui->verticalLayout_2->addWidget(m_chartSampleHistogram);
}

void MainWindow::loadPlevelsChart() const
{
    ui->verticalLayout_2->addWidget(m_chartPlevels);
}


void MainWindow::on_actionGenerate_P_Levels_triggered()
{

    Dialog_Plevels * dlg = new Dialog_Plevels(this,m_model);

    dlg->exec();
    clearLayout();
    m_model->InitHistogram();
    m_model->InitPlevelsIntervals();
    m_model->createPlevelsSample();
    m_chartPlevels = createPlevelsChart(m_model);
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

    } else if (m_chartSampleHistogram) {
        ui->verticalLayout_2->removeWidget(m_chartSampleHistogram);
        m_chartSampleHistogram =  nullptr;
    }

    qDebug() << ui->verticalLayout_2->isEmpty();
    ui->verticalLayout_2->update();
}

