#include "dialog_poweranalysis.h"
#include "ui_dialog_poweranalysis.h"

Dialog_PowerAnalysis::Dialog_PowerAnalysis(QWidget *parent,Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_PowerAnalysis),
    m_model(model)
{
    ui->setupUi(this);
}

Dialog_PowerAnalysis::~Dialog_PowerAnalysis()
{
    delete ui;
}

void Dialog_PowerAnalysis::on_buttonBox_accepted()
{

}

