#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>

#include <QtCharts>
#include <QChartView>
#include <QLineSeries>
#include "qcustomplot.h"
#include "model.h"
#include "dialog_model.h"
#include "dialog_plevels.h"
#include "dialog_power.h"
#include "dialog_poweranalysis.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    QChartView * createChartHistogram(Histogram * histogram);
    QChartView * createPlevelsChart(Model  * model);
    QCustomPlot * createPowerChart(Model * model);
    QCustomPlot * createPowerDependencyChart(Model * model);

    void clearLayout();

private slots:


    void on_actionCreate_triggered();

    void on_actionGenerate_P_Levels_triggered();

    void on_actionPower_triggered();

    void on_actionPower_Analysis_triggered();

signals:
     void signalChart(QChartView * chart);
private:
    QChartView * m_chartSampleHistogram = nullptr;
    QChartView * m_chartPlevels = nullptr;
    QCustomPlot * m_chartPower = nullptr;
    QCustomPlot * m_chartPowerDependency = nullptr;
    Model * m_model = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
