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
    if (!dialogHandler.checkSamleSize(ui->lbSampleSize)) return;
    sampleSize = ui->lbSampleSize->text().toUInt();
    plevelsSize = ui->lbSampleSize->text().toUInt();

    Generator * generator = nullptr;
    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtD0Probs);
    std::vector<double> p1 = dialogHandler.parseTxtToVector(ui->txtD1Probs);
    Distribution d0(p0),d1(p1);

    if (ui->rbTID->isChecked()) {
        generator = new TID_Generator(d1);
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d1);
    }
    std::cout << d0;
    std:: cout << d1;


    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
     m_model->setPlevelsSize(plevelsSize);
    m_model->setD0(d0);

    accept();

}

