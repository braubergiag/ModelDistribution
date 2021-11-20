#ifndef DIALOG_POWERANALYSIS_H
#define DIALOG_POWERANALYSIS_H

#include <QDialog>
#include "model.h"
#include "dialoghandler.h"
namespace Ui {
class Dialog_PowerAnalysis;
}

class Dialog_PowerAnalysis : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_PowerAnalysis(QWidget *parent = nullptr, Model * model = nullptr);
    ~Dialog_PowerAnalysis();

private slots:
    void on_buttonBox_accepted();

private:
    Model * m_model = nullptr;
    DialogHandler dialogHandler;
    Ui::Dialog_PowerAnalysis *ui;
};

#endif // DIALOG_POWERANALYSIS_H
