#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    uint64_t demoSampleSize = 10000;
    Distribution d0({0.1,0.2,0.3,0.4});


    // Cоздаём заготовки для моделей
    m_modelSample = new Model();
    m_modelPlevels = new Model();
    m_modelPower = new Model();
    m_modelPowerAnalysis = new Model();
    m_graphCreator = new GraphCreator();

    Generator * generator = new TID_Generator(d0);
    m_modelSample->setGenerator(generator);
    m_modelSample->setSampleSize(demoSampleSize);
    m_modelSample->setD0(d0);
    m_modelSample->setGeneratorMethod("Table Inverse Dichatomy");
    m_chartSampleHistogram = m_graphCreator->createChartHistogram(m_modelSample);
    loadChart(m_chartSampleHistogram);
    m_isSampleConfigReady = true;

}

MainWindow::~MainWindow()

{

    delete m_modelSample;
    delete m_modelPlevels;
    delete m_modelPower;
    delete m_modelPowerAnalysis;
    delete m_chartPlevels;
    delete m_chartSampleHistogram;
    delete m_chartPowerDependency;
    delete m_chartPower;
    delete m_graphCreator;
    delete ui;
}

void MainWindow::loadChart(QCustomPlot *customPlot)

{

    if (customPlot){

        ui->verticalLayout_2->addWidget(customPlot);
    }
}


// Нажатие кнопки Generate Sample
void MainWindow::on_actionCreateSampleChart_triggered()
{
    if (m_isSampleConfigReady){
          clearLayout();
        m_chartSampleHistogram = m_graphCreator->createChartHistogram(m_modelSample);
        loadChart(m_chartSampleHistogram);
    } else {
        on_actionSetSample_triggered();
    }
}


// Нажатие кнопки Generate P-Levels
void MainWindow::on_actionGenerate_P_Levels_triggered()
{
    if (m_isPlevelConfigReady) {
          clearLayout();
        m_chartPlevels = m_graphCreator->createPlevelsGraph(m_modelPlevels);
        loadChart(m_chartPlevels);
    } else {
        on_actionSetPlevels_triggered();
    }
}



// Нажатие кнопки Power
void MainWindow::on_actionPower_triggered()
{
    if (m_isPowerConfigReady){
          clearLayout();
        m_chartPower = m_graphCreator->createPowerGraph(m_modelPower);
        loadChart(m_chartPower);
    } else {
       on_actionSetPower_triggered();
    }
}

void MainWindow::on_actionGenPower_Analysis_triggered()
{

     if (m_isPowerAnalisysConfigReady) {
           clearLayout();
         m_chartPowerDependency = m_graphCreator->createPowerDependencyGraph(m_modelPowerAnalysis);
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

    Dialog_model * dlg = new Dialog_model(this,m_modelSample);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isSampleConfigReady = true;
          clearLayout();

        m_chartSampleHistogram = m_graphCreator->createChartHistogram(m_modelSample);
        loadChart(m_chartSampleHistogram);
    } else if (dlg->result() == QDialog::Rejected){
        qDebug() << "Rejected.\n";
    }
    delete dlg;

}

// Задание конфигурации для генерирования выборки P-levels
void MainWindow::on_actionSetPlevels_triggered()
{
    Dialog_Plevels * dlg = new Dialog_Plevels(this,m_modelPlevels);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isPlevelConfigReady = true;
          clearLayout();
        m_chartPlevels = m_graphCreator->createPlevelsGraph(m_modelPlevels);;
        loadChart(m_chartPlevels);
    } else if (dlg->result() == QDialog::Rejected){
        qDebug() << "Rejected.\n";
    }
    delete dlg;
}


void MainWindow::on_actionSetPower_triggered()
{
    Dialog_Power * dlg = new Dialog_Power(this,m_modelPower);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
        m_isPowerConfigReady = true;
        clearLayout();
        m_chartPower = m_graphCreator->createPowerGraph(m_modelPower);
        loadChart(m_chartPower);
    } else if (dlg->result() == QDialog::Rejected){
        qDebug() << "Rejected.\n";
    }
    delete dlg;
}


void MainWindow::on_actionSetPower_Analysis_triggered()
{
    Dialog_PowerAnalysis * dlg = new Dialog_PowerAnalysis(this,m_modelPowerAnalysis);
    dlg->exec();
    if (dlg->result() == QDialog::Accepted) {
         m_isPowerAnalisysConfigReady = true;
          clearLayout();
         m_chartPowerDependency = m_graphCreator->createPowerDependencyGraph(m_modelPowerAnalysis);
         loadChart(m_chartPowerDependency);

     } else if (dlg->result() == QDialog::Rejected){
        qDebug() << "Rejected.\n";
    }
    delete dlg;
}


void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

