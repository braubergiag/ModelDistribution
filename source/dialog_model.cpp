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

std::vector<double> Dialog_model::getD0()
{
    QString d0 = ui->txtProbs->text();
    QStringList d0_list = d0.split(",");
    std::vector<double> probs(d0_list.size());
    bool ok;
    for (size_t i = 0 ; i < d0_list.size(); ++i){
       double value = d0_list[i].toDouble(&ok);
       if (ok && value > 0) {
           probs[i] = value;
           qDebug() << probs[i] << " ";
       }

    }


    return probs;

}




void Dialog_model::on_buttonBox_accepted()
{
    uint64_t sampleSize = 0;
    if (checkSamleSize()) {
        sampleSize = ui->lbSampleSize->text().toUInt();
    } else {
        return;
    }


    Generator * generator;
    if (ui->rbTID->isChecked()) {;
         generator = new TID_Generator(Distribution(getD0()));
    } else if (ui->rbTIS->isChecked()) {
        generator = new  TISM_Generator(Distribution(getD0()));
    }

    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setD0(Distribution(getD0()));



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
    checkSamleSize();
}

bool Dialog_model::checkSamleSize() const
{
    bool ok;
    QMessageBox msgBox;
    const uint64_t SAMPLE_MAX_SIZE = 10e8;
    const uint64_t SAMPLE_BASE_SIZE = 10e4;
    int64_t sampleSize = ui->lbSampleSize->text().toUInt(&ok);
    if (!ok ) {

        msgBox.setText("Объём выборки должен быть целым положительным числом.");
        ui->lbSampleSize->setText(QString::number(SAMPLE_BASE_SIZE));
        msgBox.exec();

    } else if (sampleSize > SAMPLE_MAX_SIZE) {

        msgBox.setText("\n Максимальный размер выборки:" + QString::number(SAMPLE_MAX_SIZE));
        ui->lbSampleSize->setText(QString::number(SAMPLE_BASE_SIZE));
        msgBox.exec();
    }

    else {
        return true;
    }
}

