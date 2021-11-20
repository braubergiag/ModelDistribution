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
    if (!dialogHandler.checkSamleSize(ui->lbSampleSize)) return;
    sampleSize = ui->lbSampleSize->text().toUInt();
    Generator * generator;
    std::vector<double> d0 = dialogHandler.parseTxtToVector(ui->txtProbs);
    if (ui->rbTID->isChecked()) {;
         generator = new TID_Generator(Distribution(d0));
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(Distribution(d0));
    }

    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setD0(Distribution(d0));



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



