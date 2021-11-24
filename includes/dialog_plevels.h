#ifndef DIALOG_PLEVELS_H
#define DIALOG_PLEVELS_H

#include <QDialog>
#include <QMessageBox>
#include <model.h>
#include "TID_Generator.h"
#include "TISM_Generator.h"
#include "dialoghandler.h"
#include "Histogram.h"
namespace Ui {
class Dialog_Plevels;
}

class Dialog_Plevels : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Plevels(QWidget *parent = nullptr, Model * model = nullptr);
    ~Dialog_Plevels();


private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:

    void loadModelConfig(Model * model);


    bool checkSamleSize() const;
    Ui::Dialog_Plevels *ui;
    Model * m_model = nullptr;
    DialogHandler dialogHandler;

};

#endif // DIALOG_PLEVELS_H
