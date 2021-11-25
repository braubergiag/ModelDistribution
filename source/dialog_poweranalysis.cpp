#include "dialog_poweranalysis.h"
#include "ui_dialog_poweranalysis.h"

Dialog_PowerAnalysis::Dialog_PowerAnalysis(QWidget *parent,Model * model) :
    QDialog(parent),ui(new Ui::Dialog_PowerAnalysis),m_model(model)
{


    ui->setupUi(this);
    loadModelConfig(model);
}

Dialog_PowerAnalysis::~Dialog_PowerAnalysis()
{
    delete ui;
}

void Dialog_PowerAnalysis::on_buttonBox_accepted()
{

    uint64_t plevelsSize = 0;
    plevelsSize = ui->lbPlevelsSize->text().toUInt();


    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtD0Probs);
    std::vector<double> p1 = dialogHandler.parseTxtToVector(ui->txtD1Probs);
    std::vector<double> sampleSizesInterval = dialogHandler.parseTxtToVector(ui->txtSampleSizes);
    if (p0.size() == 0 || p1.size() == 0 || plevelsSize <= 0) {
        reject();
        return;
    }
    Generator * generator = nullptr;
    Distribution d0(p0),d1(p1);

    if (ui->rbTID->isChecked()) {
        generator = new TID_Generator(d1);
         m_model->setGeneratorMethod(ui->rbTID->text().toStdString());
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d1);
         m_model->setGeneratorMethod(ui->rbTIS->text().toStdString());
    }


    m_model->setGenerator(generator);
    m_model->setSampleSize(plevelsSize);
    m_model->setD0(d0);
    m_model->setD0String(ui->txtD0Probs->text().toStdString());
    m_model->setD1String(ui->txtD1Probs->text().toStdString());
    m_model->setSignificaneLevel(ui->cbSignLevel->currentText().toDouble());
    m_model->setSignificanceLevelString(ui->cbSignLevel->currentText().toStdString());
    m_model->setSampleSizeInterval(sampleSizesInterval);
    m_model->setSampleSizesString(ui->txtSampleSizes->text().toStdString());
    m_model->setPlevelsSize(plevelsSize);
    qDebug() << "Significance Level " << m_model->significaneLevel();


    accept();

}


void Dialog_PowerAnalysis::on_buttonBox_rejected()
{
    reject();

}

void Dialog_PowerAnalysis::loadModelConfig(Model *model)
{

    ui->txtD0Probs->setText(QString::fromStdString(model->d0String()));
    ui->txtD1Probs->setText(QString::fromStdString(model->d1String()));
    ui->lbPlevelsSize->setText(QString::number(model->plevelsSize()));
    if (model->generatorMethod() == ui->rbTID->text().toStdString()){
        ui->rbTID->setChecked(true);
    } else if (model->generatorMethod() == ui->rbTIS->text().toStdString()){
        ui->rbTIS->setChecked(true);
    }


    ui->txtSampleSizes->setText(QString::fromStdString(model->sampleSizesString()));
    int index = ui->cbSignLevel->findText(QString::fromStdString(model->significanceLevelString()));

    if (index != -1){
         ui->cbSignLevel->setCurrentIndex(index);
    }



  }




