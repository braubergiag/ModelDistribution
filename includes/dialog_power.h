#ifndef DIALOG_POWER_H
#define DIALOG_POWER_H

#include <QDialog>
#include "model.h"
#include "dialoghandler.h"
namespace Ui {
class Dialog_Power;
}

class Dialog_Power : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Power(QWidget *parent = nullptr,Model * model = nullptr);
    ~Dialog_Power();

private slots:
    void on_buttonBox_accepted();

    void on_rbCheckEq_clicked();

    void on_buttonBox_rejected();

private:
    Ui::Dialog_Power *ui;
    DialogHandler dialogHandler;
    Model * m_model = nullptr;
};

#endif // DIALOG_POWER_H
