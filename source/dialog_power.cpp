#include "dialog_power.h"
#include "ui_dialog_power.h"

Dialog_Power::Dialog_Power(QWidget *parent, Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_Power),
    m_model(model)
{
    ui->setupUi(this);
}

Dialog_Power::~Dialog_Power()
{
    delete ui;
}
