#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QtCharts>
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
    ui->verticalLayout_2->addWidget(m_chartSampleHistogram);

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
    //series->append(set1);
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
   //series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();

    axisY->setRange(0,static_cast<uint64_t>(maxYValue));
    chart->addAxis(axisY, Qt::AlignLeft);
    //series->attachAxis(axisY);






    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    return  chartView;
}

QChartView *MainWindow::createPlevelsChart(Model  * model)

{

    QLineSeries *set0 = new QLineSeries();

    QLineSeries *set1 = new QLineSeries();

    set0->setName("Observed Plevel");
    set1->setName("Expected Plevel");

     const double maxYValue = 1.0, maxXValue = 1.0;


     *set0 << QPointF(0,0);
     *set1 << QPointF(0,0);
     for (size_t i = 0; i < model->plevelObservedCDF().size(); ++i){
         *set0 << QPointF(model->plevelsInteravals().at(i),model->plevelObservedCDF().at(i));
     }


     for (size_t i = 0; i < model->plevelsInteravals().size(); ++i){
         *set1 << QPointF(model->plevelsInteravals().at(i),model->plevelsInteravals().at(i));
     }



     QChart *chart = new QChart();


     chart->addSeries(set0);
     chart->addSeries(set1);
     chart->setTitle("Plevels CDFs");
     ui->txtDistributionInfo->setText("");
     chart->setAnimationOptions(QChart::SeriesAnimations);
     chart->setAnimationOptions(QChart::GridAxisAnimations);

     QValueAxis *axisX = new QValueAxis();
     QValueAxis *axisY = new QValueAxis();



     qreal tickInterval = model->plevelsInteravals().at(0);
     axisX->setTickCount(model->plevelsInteravalsSize() + 1);
     axisY->setTickCount(model->plevelsInteravalsSize() + 1);

     axisX->setTickInterval(tickInterval);

      axisX->setRange(0.0,maxXValue);
     axisY->setRange(0.0l,maxYValue);

     chart->addAxis(axisX, Qt::AlignBottom);
     chart->addAxis(axisY, Qt::AlignLeft);



     chart->legend()->setVisible(true);
     chart->legend()->setAlignment(Qt::AlignBottom);


     QChartView *chartView = new QChartView(chart);
     chartView->setRenderHint(QPainter::Antialiasing);
     return  chartView;
}

QCustomPlot *MainWindow::createPowerChart(Model *model)
{



     QCustomPlot * customPlot = new QCustomPlot();

     QVector<double> x = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
     QVector<double> y  = QVector<double>(model->plevelDistribution().begin(),model->plevelDistribution().end());
     x.insert(0,0);
     y.insert(0,0);
     customPlot->addGraph();
     customPlot->graph(0)->setData(x,y);
     customPlot->xAxis->setLabel("Alpha");
     customPlot->yAxis->setLabel("PLevel \t rate");
     customPlot->xAxis->setRange(0,1);
     customPlot->yAxis->setRange(0,1);
     customPlot->replot();

     return customPlot;







}

QCustomPlot *MainWindow::createPowerDependencyChart(Model *model)
{



    QCustomPlot * customPlot = new QCustomPlot();
    QVector<double> x = QVector<double>(model->sampleSizeInterval().begin(),model->sampleSizeInterval().end());
    QVector<double> y  = QVector<double>(model->powerDependency().begin(),model->powerDependency().end());
    customPlot->addGraph();
    customPlot->graph(0)->setData(x,y);
    customPlot->xAxis->setLabel("Sample Size");
    customPlot->yAxis->setLabel("Power \t  rate");
    customPlot->xAxis->setRange(0, model->sampleSize());
    customPlot->yAxis->setRange(0, model->maxPowerLevel() + model->maxPowerLevel() * 0.1);
    customPlot->replot();

    return customPlot;




}





void MainWindow::on_actionCreate_triggered()
{

    Dialog_model * dlg = new Dialog_model(this,m_model);

    dlg->exec();

    if (dlg->result() == QDialog::Accepted) {
        clearLayout();
        m_model->InitHistogram();
        m_model->InitPlevelsIntervals();
        m_chartSampleHistogram = createChartHistogram(m_model->histogram());
        if (m_chartSampleHistogram){
            ui->verticalLayout_2->addWidget(m_chartSampleHistogram);
        }
    }



    delete dlg;




}



void MainWindow::on_actionGenerate_P_Levels_triggered()
{

    Dialog_Plevels * dlg = new Dialog_Plevels(this,m_model);

    dlg->exec();

    if (dlg->result() == QDialog::Accepted) {
        clearLayout();
        m_model->InitHistogram();
        m_model->InitPlevelsIntervals();
        m_model->createPlevelsSample();
        m_chartPlevels = createPlevelsChart(m_model);
        if (m_chartPlevels){
            ui->verticalLayout_2->addWidget(m_chartPlevels);
        }
    }



    delete dlg;
}




void MainWindow::on_actionPower_triggered()
{

    Dialog_Power * dlg = new Dialog_Power(this,m_model);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        clearLayout();
        m_model->InitHistogram();
        m_model->InitPlevelsIntervals();
        m_model->createPlevelsDistribution();
        m_chartPower = createPowerChart(m_model);

        if (m_chartPower){

             ui->verticalLayout_2->addWidget(m_chartPower);
        }
    }



    delete dlg;
}


void MainWindow::on_actionPower_Analysis_triggered()
{
    Dialog_PowerAnalysis * dlg = new Dialog_PowerAnalysis(this,m_model);

    dlg->exec();

     if (dlg->result() == QDialog::Accepted) {
         clearLayout();
         m_model->InitHistogram();
         m_model->createPowerDependencyTable();
         m_chartPowerDependency = createPowerDependencyChart(m_model);

         if (m_chartPowerDependency){
              ui->verticalLayout_2->addWidget(m_chartPowerDependency);
         }

     }

    delete dlg;

}



void MainWindow::clearLayout()
{
    if (m_chartPlevels) {
        ui->verticalLayout_2->removeWidget(m_chartPlevels);
        m_chartPlevels = nullptr;

    } else if (m_chartSampleHistogram) {
        ui->verticalLayout_2->removeWidget(m_chartSampleHistogram);
        m_chartSampleHistogram =  nullptr;
    } else if (m_chartPower) {
        ui->verticalLayout_2->removeWidget(m_chartPower);
        m_chartPower = nullptr;
    } else if (m_chartPowerDependency) {
        ui->verticalLayout_2->removeWidget(m_chartPowerDependency);
        m_chartPowerDependency = nullptr;
    }
    ui->verticalLayout_2->update();
}





