#include "dialog_model.h"
#include "ui_dialog_model.h"

Dialog_model::Dialog_model(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_model)
{
    ui->setupUi(this);
}

Dialog_model::~Dialog_model()
{
    delete ui;
}

QVector<double> Dialog_model::getD0()
{
    QString d0 = ui->txtProbs->text();
    QStringList d0_list = d0.split(",");
    QVector<double> probs(d0_list.size());
    bool ok;
    for (int i = 0 ; i < d0_list.size(); ++i){
       double value = d0_list[i].toDouble(&ok);
       if (ok) {
           probs[i] = value;
           qDebug() << probs[i] << " ";
       }

    }


    return probs;

}

QChartView * Dialog_model::createChartHistogram(Histogram &histogram)
{


              histogram.calcChi();

              QBarSet *set0 = new QBarSet("Observed");
              QBarSet *set1 = new QBarSet("Expected");


                for (size_t i = 0; i < histogram.distSize(); ++i){
                    *set0 << histogram.GetObservedAt(i);
                }
                for (size_t i = 0; i < histogram.distSize(); ++i){
                    *set1 << histogram.GetExpectedAt(i);
                }




                 QBarSeries *series = new QBarSeries();
                   series->append(set0);
                   series->append(set1);


                   QChart *chart = new QChart();
                     chart->addSeries(series);
                     chart->setTitle("Simple barchart example");
                     chart->setAnimationOptions(QChart::SeriesAnimations);


                     QStringList categories;
                     for (int i = 0; i <histogram.distSize(); ++i){
                         categories << QString::number(i);
                     }

                     QBarCategoryAxis *axisX = new QBarCategoryAxis();
                     axisX->append(categories);
                     chart->addAxis(axisX, Qt::AlignBottom);
                     series->attachAxis(axisX);

                     QValueAxis *axisY = new QValueAxis();
                     axisY->setRange(0,static_cast<int32_t>(histogram.sampleSize() / 4 + 10000));
                     chart->addAxis(axisY, Qt::AlignLeft);
                     series->attachAxis(axisY);

                     chart->legend()->setVisible(true);
                     chart->legend()->setAlignment(Qt::AlignBottom);


                      QChartView *chartView = new QChartView(chart);
                      chartView->setRenderHint(QPainter::Antialiasing);
                      return  chartView;
}



void Dialog_model::on_buttonBox_accepted()
{

    bool ok;
    int32_t sampleSize = ui->lbSampleSize->text().toInt(&ok);
    if (ok && sampleSize > 0){
        qDebug() << "ok\n";
    } else {
//        QMessageBox::Information(this,"Invalid sample size","Sample size must be an integer > 0");
          qDebug("Invalid sample size. Sample size must be an integer > 0");
    }
    QVector<double> probs = getD0();
    Generator * generator;
    if (ui->rbTID->isChecked()) {
         qDebug() << "You choose : " << ui->rbTID->text();
         generator = new TID_Generator(probs);
    } else if (ui->rbTIS->isChecked()) {
        qDebug() <<"You choose : " << ui->rbTIS->text();
        generator = new  TISM_Generator(probs);
    }
    Histogram histogram(generator,probs,sampleSize);
    m_chartHistogram = createChartHistogram(histogram);

    accept();


}



void Dialog_model::on_buttonBox_rejected()
{
    reject();
}

QChartView *Dialog_model::chartHistogram() const
{
    return m_chartHistogram;
}

