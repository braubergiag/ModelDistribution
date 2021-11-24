#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QDialog>


#include "graphcreator.h"
#include "qcustomplot.h"
#include "model.h"
#include "dialog_model.h"
#include "dialog_plevels.h"
#include "dialog_power.h"
#include "dialog_poweranalysis.h"

#include "Distribution.h"
#include "Generator.h"
#include "Histogram.h"
#include "TID_Generator.h"
#include "TISM_Generator.h"
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

    void clearLayout();

private slots:


    void on_actionCreateSampleChart_triggered();

    void on_actionGenerate_P_Levels_triggered();

    void on_actionPower_triggered();

    void on_actionGenPower_Analysis_triggered();

    void on_actionSetSample_triggered();

    void on_actionSetPlevels_triggered();

    void on_actionSetPower_triggered();

    void on_actionSetPower_Analysis_triggered();


    void on_actionQuit_triggered();

private:


    void Init();
    void InitDemo();

    GraphCreator * m_graphCreator = nullptr;

    QCustomPlot * m_chartSampleHistogram = nullptr;
    QCustomPlot * m_chartPlevels = nullptr;
    QCustomPlot * m_chartPower = nullptr;
    QCustomPlot * m_chartPowerDependency = nullptr;

    Model * m_model = nullptr; // Модель для моделирования plevels
    Model * m_modelSample = nullptr; // Модель для моделирования выборки
    Model * m_modelPlevels = nullptr;
    Model * m_modelPower = nullptr;
    Model * m_modelPowerAnalysis = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
