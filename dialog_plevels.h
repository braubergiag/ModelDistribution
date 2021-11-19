#ifndef DIALOG_PLEVELS_H
#define DIALOG_PLEVELS_H

#include <QDialog>
#include <QMessageBox>
#include <QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QChartView>
#include <model.h>
#include "TID_Generator.h"
#include "TISM_Generator.h"

#include "Histogram.h"
namespace Ui {
class Dialog_Plevels;
}

class Dialog_Plevels : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Plevels(QWidget *parent = nullptr);
    ~Dialog_Plevels();

    QVector<double> getD0();
//    QVector<double> getD1();

    QChartView * chartPlevels() const;
    QChartView * createPlevelsChart(Model * model);

private slots:
    void on_buttonBox_accepted();

private:
    bool checkSamleSize() const;
    QChartView * m_chartPlevels = nullptr;
    Ui::Dialog_Plevels *ui;
};

#endif // DIALOG_PLEVELS_H
