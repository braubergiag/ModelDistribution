#ifndef DIALOG_POWER_H
#define DIALOG_POWER_H

#include <QDialog>
#include "model.h"
namespace Ui {
class Dialog_Power;
}

class Dialog_Power : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Power(QWidget *parent = nullptr,Model * model = nullptr);
    ~Dialog_Power();

private:
    Ui::Dialog_Power *ui;
    Model * m_model = nullptr;
};

#endif // DIALOG_POWER_H
