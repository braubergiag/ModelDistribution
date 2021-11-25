#include "dialog_model.h"
#include "ui_dialog_model.h"
#include "model.h"

Dialog_model::Dialog_model(QWidget *parent, Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_model),
    m_model(model)
{
    ui->setupUi(this);


    loadModelConfig(model);


}

Dialog_model::~Dialog_model()
{
    delete ui;
}




void Dialog_model::on_buttonBox_accepted()
{
    uint64_t sampleSize = 0;
    sampleSize = ui->lbSampleSize->text().toUInt();
    std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtProbs);
    if (p0.size() == 0 || !dialogHandler.checkSamleSize(ui->lbSampleSize) ) {
        reject();
        return;

    }

    Generator * generator = nullptr;
    Distribution d0(p0);
    if (ui->rbTID->isChecked()) {;
         generator = new TID_Generator(d0);
         m_model->setGeneratorMethod(ui->rbTID->text().toStdString());
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(d0);
        m_model->setGeneratorMethod(ui->rbTIS->text().toStdString());

    }

    m_model->setD0String(ui->txtProbs->text().toStdString());
    m_model->setD1String(ui->txtProbs->text().toStdString());
    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setD0(d0);




    accept();


}



void Dialog_model::on_buttonBox_rejected()
{
    reject();
}



void Dialog_model::loadModelConfig(Model *model)
{
    ui->lbSampleSize->setText(QString::number(model->sampleSize()));
    ui->txtProbs->setText(QString::fromStdString(model->d0String()));

    if (model->generatorMethod() == ui->rbTID->text().toStdString()){
        ui->rbTID->setChecked(true);
    } else if (model->generatorMethod() == ui->rbTIS->text().toStdString()){
        ui->rbTIS->setChecked(true);
    }

}




void Dialog_model::on_lbSampleSize_editingFinished()
{
    dialogHandler.checkSamleSize(ui->lbSampleSize);
}



