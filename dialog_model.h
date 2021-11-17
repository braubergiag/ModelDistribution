#ifndef DIALOG_MODEL_H
#define DIALOG_MODEL_H

#include <QDialog>
#include <QMessageBox>
#include <QVector>
#include <QDebug>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChartView>
#include <QChartView>

#include "Histogram.h"

#include "Generator.h"
#include "TID_Generator.h"
#include "TISM_Generator.h"
namespace Ui {
class Dialog_model;
}

class Dialog_model : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_model(QWidget *parent = nullptr);
    ~Dialog_model();
    QVector<double> getD0();
    QVector<double> getD1();

     Histogram histogram() const;



     QChartView  *createChartHistogram(Histogram& histogram);


     QChartView *chartHistogram() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:

    QChartView * m_chartHistogram;
    Ui::Dialog_model *ui;
};

#endif // DIALOG_MODEL_H
