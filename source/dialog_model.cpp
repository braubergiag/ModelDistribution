#include "dialog_model.h"
#include "ui_dialog_model.h"
#include "model.h"

Dialog_model::Dialog_model(QWidget *parent, Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_model),
    m_model(model)
{
    ui->setupUi(this);

//    loadModelConfig(model);


}

Dialog_model::~Dialog_model()
{
    delete ui;
}




void Dialog_model::on_buttonBox_accepted()
{
    uint64_t sampleSize = 0;
    if (!dialogHandler.checkSamleSize(ui->lbSampleSize)) reject();
    sampleSize = ui->lbSampleSize->text().toUInt();
     std::vector<double> p0 = dialogHandler.parseTxtToVector(ui->txtProbs);
    if (p0.size() == 0) {
        reject();
        return;

    }
    Generator * generator;

    if (ui->rbTID->isChecked()) {;
         generator = new TID_Generator(Distribution(p0));
         m_model->setGeneratorMethod(ui->rbTID->text().toStdString());
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(Distribution(p0));
        m_model->setGeneratorMethod(ui->rbTIS->text().toStdString());

    }

    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setD0(Distribution(p0));




    accept();


}



void Dialog_model::on_buttonBox_rejected()
{
    reject();
}



//void Dialog_model::loadModelConfig(Model *model)
//{
//    ui->lbSampleSize->setText(QString::number(model->sampleSize()));
//    QString d0 = "";
//    for (const auto & p : model->getD0().p()){
//        qDebug() << p << " ";
//        d0.append(QString::fromStdString(std::to_string()));
//        d0.append(",");
//    }
//    ui->txtProbs->setText(d0);
//}




void Dialog_model::on_lbSampleSize_editingFinished()
{
    dialogHandler.checkSamleSize(ui->lbSampleSize);
}



