#include "dialog_plevels.h"
#include "ui_dialog_plevels.h"

Dialog_Plevels::Dialog_Plevels(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Plevels)
{
    ui->setupUi(this);
}

Dialog_Plevels::~Dialog_Plevels()
{
    delete ui;
}

QVector<double> Dialog_Plevels::getD0()
{
    QString h0 = ui->txtProbsH0->text();
    QStringList h0_lsit = h0.split(",");
    QVector<double> probs(h0_lsit.size());
    bool ok;
    for (int i = 0 ; i < h0_lsit.size(); ++i){
       double value = h0_lsit[i].toDouble(&ok);
       if (ok && value > 0) {
           probs[i] = value;
           qDebug() << probs[i] << " ";
       }

    }


    return probs;
}

QVector<double> Dialog_Plevels::getD1()
{
    QString h1 = ui->txtProbsH1->text();
    QStringList h1_list = h1.split(",");
    QVector<double> probs(h1_list.size());
    bool ok;
    for (int i = 0 ; i < h1_list.size(); ++i){
       double value = h1_list[i].toDouble(&ok);
       if (ok && value > 0) {
           probs[i] = value;
           qDebug() << probs[i] << " ";
       }

    }


    return probs;
}

QChartView *Dialog_Plevels::chartPlevels() const
{
    return m_chartPlevels;
}

QChartView *Dialog_Plevels::createPlevelsChart(Histogram &histogram)
{
    return m_chartPlevels;
}

void Dialog_Plevels::on_buttonBox_accepted()
{

    Generator * generator;
    if (ui->rbTID->isChecked()) {
         qDebug() << "You choose : " << ui->rbTID->text();
         generator = new TID_Generator(getD1());
    } else if (ui->rbTIS->isChecked()) {
        qDebug() <<"You choose : " << ui->rbTIS->text();
        generator = new  TISM_Generator(getD1());
    }

    uint64_t sampleSize = 0;
    if (checkSamleSize()) {
        sampleSize = ui->lbSampleSize->text().toUInt();
    } else {
        return;
    }

   Model * model;
   model = new Model(generator);
   model->setSampleSize(sampleSize);
   model->setD0(Distribution(getD0()));
   model->setD1(Distribution(getD1()));


   uint32_t plevelsSize = ui->lbPlevelsSize->text().toUInt();
   model->setPlevelsSize(plevelsSize);
   model->Init();
   model->InitHistogram();
   model->createPlevelsSample();
//    m_chartPlevels = createPlevelsChart(hist);
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


