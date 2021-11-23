#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>


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

    void loadChart (QCustomPlot * customPlot);

    QCustomPlot * createChartHistogram(Model * model);
    QCustomPlot * createPlevelsGraph(Model  * model);
    QCustomPlot * createPowerGraph(Model * model);
    QCustomPlot * createPowerDependencyGraph(Model * model);

    void clearLayout();

private slots:


    void on_actionCreate_triggered();

    void on_actionGenerate_P_Levels_triggered();

    void on_actionPower_triggered();

    void on_actionGenPower_Analysis_triggered();

    void on_actionSetSample_triggered();

    void on_actionSetPlevels_triggered();

    void on_actionSetPower_triggered();

    void on_actionSetPower_Analysis_triggered();


private:

    bool m_isSampleConfigReady = false;
    bool m_isPowerConfigReady = false;
    bool m_isPlevelConfigReady = false;
    bool m_isPowerAnalisysConfigReady = false;


    QCustomPlot * m_chartSampleHistogram = nullptr;
    QCustomPlot * m_chartPlevels = nullptr;
    QCustomPlot * m_chartPower = nullptr;
    QCustomPlot * m_chartPowerDependency = nullptr;
    Model * m_model = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
