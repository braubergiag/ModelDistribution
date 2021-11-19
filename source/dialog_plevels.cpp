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

std::vector<double> Dialog_Plevels::getD0()
{
    QString h0  = ui->txtProbs->text();
    QStringList h0_lsit = h0.split(",");
    std::vector<double> probs(h0_lsit.size());
    bool ok;
    for (size_t i = 0 ; i < h0_lsit.size(); ++i){
       double value = h0_lsit[i].toDouble(&ok);
       if (ok && value > 0) {
           probs[i] = value;
           qDebug() << probs[i] << " ";
       }

    }


    return probs;
}






void Dialog_Plevels::on_buttonBox_accepted()
{

    Generator * generator = nullptr;
    if (ui->rbTID->isChecked()) {
        qDebug() << "You choose : " << ui->rbTID->text();
        generator = new TID_Generator(getD0());
    } else if (ui->rbTIS->isChecked()) {
        qDebug() <<"You choose : " << ui->rbTIS->text();
        generator = new  TISM_Generator(getD0());
    }

    uint64_t sampleSize = 0;
    if (checkSamleSize()) {
        sampleSize = ui->lbSampleSize->text().toUInt();
    } else {
        return;
    }

    m_model->setGenerator(generator);
    m_model->setSampleSize(sampleSize);
    m_model->setD0(Distribution(getD0()));



    uint32_t plevelsSize = ui->lbPlevelsSize->text().toUInt();
    m_model->setPlevelsSize(plevelsSize);

    accept();
}





bool Dialog_Plevels::checkSamleSize() const
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


