#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QChartView>
#include <QLineSeries>
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


    void load();
    void loadPlevelsChart() const;
    void loadPowerChart() const;

    QChartView *chartView() const;
    QChartView *chartPlevels() const;
    QChartView * createChartHistogram(Histogram * histogram);
    QChartView * createPlevelsChart(Model  * model);
    QChartView * createPowerChart(Model * model);
    QChartView * createPowerAnalysisChart(Model * model);
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
    QChartView * m_chartPower = nullptr;
    Model * m_model = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
