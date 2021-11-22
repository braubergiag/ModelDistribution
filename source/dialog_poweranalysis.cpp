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

    uint64_t plevelsSize = 0;
    plevelsSize = ui->lbPlevelsSize->text().toUInt();

    Generator * generator = nullptr;
    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtD0Probs);
    std::vector<double> p1 = dialogHandler.parseTxtToVector(ui->txtD1Probs);
    Distribution d0(p0),d1(p1);

    if (ui->rbTID->isChecked()) {
        generator = new TID_Generator(d1);
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d1);
    }


    m_model->setGenerator(generator);
    m_model->setPlevelsSize(plevelsSize);
    m_model->setD0(d0);
    m_model->setSignificaneLevel(ui->cbSignLevel->currentText().toDouble());
    qDebug() << "Significance Level " << m_model->significaneLevel();


    accept();

}


void Dialog_PowerAnalysis::on_buttonBox_rejected()
{
    reject();

}

