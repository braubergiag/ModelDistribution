#ifndef DIALOG_PLEVELS_H
#define DIALOG_PLEVELS_H

#include <QDialog>
#include <QMessageBox>
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
    explicit Dialog_Plevels(QWidget *parent = nullptr, Model * model = nullptr);
    ~Dialog_Plevels();

    std::vector<double> getD0();


private slots:
    void on_buttonBox_accepted();

private:
    bool checkSamleSize() const;
    Model * m_model = nullptr;
    Ui::Dialog_Plevels *ui;
};

#endif // DIALOG_PLEVELS_H
