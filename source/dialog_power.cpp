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

void Dialog_Power::on_buttonBox_accepted()
{

    uint64_t sampleSize = 0;
    uint64_t plevelsSize = 0;
    if (!dialogHandler.checkSamleSize(ui->lbSampleSize)) {
        reject();
        return;
    }
    sampleSize = ui->lbSampleSize->text().toUInt();
    plevelsSize = ui->lbPlevelsSize->text().toUInt();


    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtD0Probs);
    std::vector<double> p1 = dialogHandler.parseTxtToVector(ui->txtD1Probs);
    if (p0.size() == 0 || p1.size() == 0) {
        reject();
        return;
    }
    Generator * generator = nullptr;
    Distribution d0(p0),d1;



    // Если H0 и H1 совпадают (выбрана данная опция)
    if (ui->rbCheckEq->isChecked()){
        d1.setP(p0);
         m_model->setIsPowerEstimate(false);
    } else {
        d1.setP(p1);
        m_model->setIsPowerEstimate(true);
    }

    if (ui->rbTID->isChecked()) {
        generator = new TID_Generator(d1);
         m_model->setGeneratorMethod(ui->rbTID->text().toStdString());

    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d1);
         m_model->setGeneratorMethod(ui->rbTIS->text().toStdString());
    }


    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setPlevelsSize(plevelsSize);
    m_model->InitPlevelsIntervals();
    m_model->setD0(d0);
    m_model->setD1(d1);

    accept();

}


void Dialog_Power::on_rbCheckEq_clicked()
{
    if (ui->rbCheckEq->isChecked()){
        ui->txtD1Probs->setDisabled(true);
    } else {
        ui->txtD1Probs->setDisabled(false);
    }
}


void Dialog_Power::on_buttonBox_rejected()
{
    reject();
}

