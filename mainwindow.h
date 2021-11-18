#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
//#include <QChartView>
#include "dialog_model.h"
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

private slots:


    void on_actionCreate_triggered();

signals:
     void signalChart(QChartView * chart);
private:
    QWidget * widget = nullptr;
    QChartView * m_chartView = nullptr;
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
