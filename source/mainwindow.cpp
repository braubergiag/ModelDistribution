#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
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
    m_chartSampleHistogram = createChartHistogram(m_model);
    ui->verticalLayout_2->addWidget(m_chartSampleHistogram);
    m_isSampleConfigReady = true;

}

MainWindow::~MainWindow()

{
    delete m_model;
    delete m_chartPlevels;
    delete m_chartSampleHistogram;
    delete ui;
}

void MainWindow::loadChart(QCustomPlot *customPlot)
{
    if (customPlot){
        ui->verticalLayout_2->addWidget(customPlot);
    }
}

QCustomPlot * MainWindow::createChartHistogram(Model * model)
{

    // Prepare model
    clearLayout();
    m_model->InitHistogram();
    model->histogram()->calcChi();


    // Chart stuff

     QVector<double> x_observed,y_observed,x_expected,y_expected;
    uint64_t maxYValue = model->histogram()->MaxFrequency() + (0.2 *  model->histogram()->MaxFrequency());
    uint32_t maxXValue;


    for (const  auto & item :  model->histogram()->observedMerged()){
       x_observed.push_back(item.first); // value
       y_observed.push_back(item.second); // frequency
    }
    for (const  auto & item :  model->histogram()->expectedMerged()){
        x_expected.push_back(item.first); // value
        y_expected.push_back(item.second); // frequency
    }
    maxXValue = x_expected.back();


    QCustomPlot * customPlot = new QCustomPlot();
    customPlot->yAxis->setRange(0, maxYValue );
    QCPBars *expected = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *observed = new QCPBars(customPlot->xAxis, customPlot->yAxis);


     observed->setName("Observed");
     observed->setPen(QPen(Qt::blue));
     observed->setBrush(QBrush(QColor(54, 98, 186)));

     expected->setPen(QPen(QColor(232, 74, 74)));
     expected->setBrush(QBrush(QColor(232, 74, 74,100)));
     observed->setWidth(0.5);
     expected->setWidth(0.8);
     expected->setName("Expected");


     QVector<double> ticks;
     QVector<QString> labels;
     for (const auto & value: x_observed){
         ticks << value;
         labels << QString::number(value);
     }
     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
     textTicker->addTicks(ticks, labels);
     customPlot->xAxis->setTicker(textTicker);
     customPlot->xAxis->setRange(-1, maxXValue + 1);
    // customPlot->setName("Discrete Distribution Sample");

    expected->setData(x_expected,y_expected);
     observed->setData(x_observed,y_observed);


     customPlot->legend->setVisible(true);
     customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     customPlot->legend->setBrush(QColor(255, 255, 255, 100));
     customPlot->legend->setBorderPen(Qt::NoPen);
     QFont legendFont = font();
     legendFont.setPointSize(10);
     customPlot->legend->setFont(legendFont);
     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);





    QString info = "Sample size: " + QString::number(model->histogram()->sampleSize()) +
            "\t Chi-sqaure: " + QString::number(model->histogram()->chi()) + "\t Degrees of freedom: " +
            QString::number(model->histogram()->df()) + "\t P-value: " + QString::number(model->histogram()->pvalue());

    ui->txtDistributionInfo->setText(info);


    return customPlot;

}

QCustomPlot *MainWindow::createPlevelsGraph(Model  * model)

{
    // Prepare model
    clearLayout();
    m_model->InitHistogram();
    m_model->InitPlevelsIntervals();
    m_model->createPlevelsSample();

    QCustomPlot * customPlot = new QCustomPlot();


    QVector<double> x_observedCDF = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
    QVector<double> y_observedCDF  = QVector<double>(model->plevelObservedCDF().begin(),model->plevelObservedCDF().end());


    QVector<double> x_empiricalCDF = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
    QVector<double> y_empiricalCDF  = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());

    x_observedCDF.insert(0,0);
    y_observedCDF.insert(0,0);

    x_empiricalCDF.insert(0,0);
    y_empiricalCDF.insert(0,0);


    customPlot->addGraph();
    customPlot->graph(0)->setData(x_observedCDF,y_observedCDF);
    customPlot->graph(0)->setName("Observed Plevels CDF");
    //customPlot->graph(0)->setPen(QPen(QColor(227, 27, 27).lighter(500)));
    customPlot->graph(0)->setPen(QPen(Qt::blue));

    customPlot->addGraph();
    customPlot->graph(1)->setData(x_empiricalCDF,y_empiricalCDF);
    customPlot->graph(1)->setName("Empirical Plevels CDF");
    customPlot->graph(1)->setPen(QPen(Qt::red));

    customPlot->xAxis->setLabel("Plevels CDFs F(x)");
    customPlot->yAxis->setLabel("x");


    QVector<double> ticks;
    QVector<QString> labels;
    for (const auto & value: x_empiricalCDF){
        ticks << value;
        labels << QString::number(value);
    }


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setRange(0,1.05);
    customPlot->yAxis->setTicker(textTicker);
    customPlot->yAxis->setRange(0,1.05);

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);


    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     customPlot->replot();


     ui->txtDistributionInfo->setText("");
     return customPlot;

}

QCustomPlot *MainWindow::createPowerGraph(Model *model)
{

     clearLayout();
     m_model->InitHistogram();
     m_model->createPlevelsDistribution();
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

QCustomPlot *MainWindow::createPowerDependencyGraph(Model *model)
{

    // Prepare model
    clearLayout();
    m_model->InitHistogram();
    m_model->createPowerDependencyTable();

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
//    ui->txtDistributionInfo->setText("Power vs. sample size analisys");
    return customPlot;
}
// Нажатие кнопки Generate Sample
void MainWindow::on_actionCreate_triggered()
{
    if (m_isSampleConfigReady){
        m_chartSampleHistogram = createChartHistogram(m_model);
        loadChart(m_chartSampleHistogram);
    } else {
        on_actionSetSample_triggered();
    }
}


// Нажатие кнопки Generate P-Levels
void MainWindow::on_actionGenerate_P_Levels_triggered()
{
    if (m_isPlevelConfigReady) {
        m_chartPlevels = createPlevelsGraph(m_model);
        loadChart(m_chartPlevels);
    } else {
        on_actionSetPlevels_triggered();
    }
}



// Нажатие кнопки Power
void MainWindow::on_actionPower_triggered()
{
    if (m_isPowerConfigReady){
        m_chartPower = createPowerGraph(m_model);
        loadChart(m_chartPower);
    } else {
       on_actionSetPower_triggered();
    }
}

void MainWindow::on_actionGenPower_Analysis_triggered()
{

     if (m_isPowerAnalisysConfigReady) {
         m_chartPowerDependency = createPowerDependencyGraph(m_model);
         loadChart(m_chartPowerDependency);

     } else {
         on_actionSetPower_Analysis_triggered();
     }

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

// Задание конфигурации для генерирования выборки
void MainWindow::on_actionSetSample_triggered()
{

    Dialog_model * dlg = new Dialog_model(this,m_model);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isSampleConfigReady = true;
        m_chartSampleHistogram = createChartHistogram(m_model);
        loadChart(m_chartSampleHistogram);
    }
    delete dlg;

}

// Задание конфигурации для генерирования выборки P-levels
void MainWindow::on_actionSetPlevels_triggered()
{
    Dialog_Plevels * dlg = new Dialog_Plevels(this,m_model);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isPlevelConfigReady = true;
        m_chartPlevels = createPlevelsGraph(m_model);
        loadChart(m_chartPlevels);
    }
    delete dlg;
}


void MainWindow::on_actionSetPower_triggered()
{
    Dialog_Power * dlg = new Dialog_Power(this,m_model);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isPowerConfigReady = true;
        m_chartPower = createPowerGraph(m_model);
        loadChart(m_chartPower);
    }
    delete dlg;
}


void MainWindow::on_actionSetPower_Analysis_triggered()
{
    Dialog_PowerAnalysis * dlg = new Dialog_PowerAnalysis(this,m_model);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
         m_isPowerAnalisysConfigReady = true;
         m_chartPowerDependency = createPowerDependencyGraph(m_model);
         loadChart(m_chartPowerDependency);

     }
    delete dlg;
}

