#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
//#include <QChartView>
#include "model.h"
#include "dialog_model.h"
#include "dialog_plevels.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QChartView *chartView() const;
    void load();
    void loadPlevelsChart() const;

    QChartView *chartPlevels() const;
    QChartView * createChartHistogram(Histogram * histogram);
    void clearLayout();

private slots:


    void on_actionCreate_triggered();

    void on_actionGenerate_P_Levels_triggered();

signals:
     void signalChart(QChartView * chart);
private:
    QWidget * widget = nullptr;
    QChartView * m_chartSampleHistogram = nullptr;
    QChartView * m_chartPlevels = nullptr;
    Model * model = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
