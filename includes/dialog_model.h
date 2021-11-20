#ifndef DIALOG_MODEL_H
#define DIALOG_MODEL_H

#include <QDialog>
#include <QMessageBox>
#include <QVector>
#include <QDebug>
#include <vector>
#include "model.h"
#include "dialoghandler.h"
#include "Histogram.h"
#include "Distribution.h"
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
    explicit Dialog_model(QWidget *parent = nullptr, Model * model = nullptr);
    ~Dialog_model();
    std::vector<double> getD0();


     Histogram histogram() const;

     void loadModelConfig(Model * model);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_lbSampleSize_editingFinished();

private:
    bool checkSamleSize() const;
    Model * m_model = nullptr;
    DialogHandler dialogHandler;

    Ui::Dialog_model *ui;
};

#endif // DIALOG_MODEL_H
