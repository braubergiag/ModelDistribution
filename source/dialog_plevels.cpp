#include "dialog_plevels.h"
#include "ui_dialog_plevels.h"

Dialog_Plevels::Dialog_Plevels(QWidget *parent,Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_Plevels),
  m_model(model)
{
    ui->setupUi(this);
}

Dialog_Plevels::~Dialog_Plevels()
{
    delete ui;
}






void Dialog_Plevels::on_buttonBox_accepted()
{


    uint64_t sampleSize = 0;
    uint64_t plevelsSize = 0;
    if (!dialogHandler.checkSamleSize(ui->lbSampleSize)) reject();
    sampleSize = ui->lbSampleSize->text().toUInt();
    plevelsSize = ui->lbPlevelsSize->text().toUInt();


    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtProbs);
    if (p0.size() == 0) {
        reject();
        return;
    }
    Generator * generator = nullptr;
    Distribution d0(p0);



    if (ui->rbTID->isChecked()) {
        generator = new TID_Generator(d0);
         m_model->setGeneratorMethod(ui->rbTID->text().toStdString());
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d0);
        m_model->setGeneratorMethod(ui->rbTIS->text().toStdString());
    }


    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
     m_model->setPlevelsSize(plevelsSize);
    m_model->setD0(d0);

    accept();
}









void Dialog_Plevels::on_buttonBox_rejected()
{
    reject();
}

