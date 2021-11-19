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
    QString h0  = ui->txtProbs->text();
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

//QVector<double> Dialog_Plevels::getD1()
//{
//    QString h1 = ui->txtProbsH1->text();
//    QStringList h1_list = h1.split(",");
//    QVector<double> probs(h1_list.size());
//    bool ok;
//    for (int i = 0 ; i < h1_list.size(); ++i){
//       double value = h1_list[i].toDouble(&ok);
//       if (ok && value > 0) {
//           probs[i] = value;
//           qDebug() << probs[i] << " ";
//       }

//    }


//    return probs;
//}

QChartView *Dialog_Plevels::chartPlevels() const
{
    return m_chartPlevels;
}

QChartView *Dialog_Plevels::createPlevelsChart(Model  * model)

{


    QBarSet *set0 = new QBarSet("Observed");
    QBarSet *set1 = new QBarSet("Expected");
     const uint64_t maxYValue = 1.1;


     for (const  auto& item : model->plevelObservedCDF()){
          *set0 << item.second;
     }
     for (const  auto& item : model->plevelsInteravals()){
         *set1 << item;
     }




       QBarSeries *series = new QBarSeries();
         series->append(set0);
         series->append(set1);


         QChart *chart = new QChart();




           chart->addSeries(series);
           chart->setTitle("Plevels CDFs");
           chart->setAnimationOptions(QChart::SeriesAnimations);
            chart->setAnimationOptions(QChart::GridAxisAnimations);


           QStringList categories;

           for (const  auto& item : model->plevelsInteravals()){
               categories << QString::number(item);
           }


           QBarCategoryAxis *axisX = new QBarCategoryAxis();
           axisX->append(categories);
           chart->addAxis(axisX, Qt::AlignBottom);
           series->attachAxis(axisX);

           QValueAxis *axisY = new QValueAxis();

           axisY->setRange(0,static_cast<uint64_t>(maxYValue));
           chart->addAxis(axisY, Qt::AlignLeft);
           series->attachAxis(axisY);

           chart->legend()->setVisible(true);
           chart->legend()->setAlignment(Qt::AlignBottom);


            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            return  chartView;
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

   Model * model;
   model = new Model(generator);
   model->setSampleSize(sampleSize);
   model->setD0(Distribution(getD0()));



   uint32_t plevelsSize = ui->lbPlevelsSize->text().toUInt();
   model->setPlevelsSize(plevelsSize);
   model->InitExpectedPlevelCDF();
   model->InitHistogram();
   model->InitPlevelsIntervals();
  model->createPlevelsSample();
   model->PrintPlevels();
  m_chartPlevels = createPlevelsChart(model);
  delete model;
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


