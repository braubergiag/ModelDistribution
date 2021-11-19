#include "dialog_model.h"
#include "ui_dialog_model.h"
#include "model.h"

Dialog_model::Dialog_model(QWidget *parent, Model * model) :
    QDialog(parent),
    ui(new Ui::Dialog_model)
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

QChartView * Dialog_model::createChartHistogram(Histogram * histogram)
{


    histogram->calcChi();
    QBarSet *set0 = new QBarSet("Observed");
    QBarSet *set1 = new QBarSet("Expected");
    uint64_t maxYValue = histogram->MaxFrequency() + (0.1 *  histogram->MaxFrequency());


    for (const  auto& item : histogram->observedMerged()){
        *set0 << item.second;
    }
    for (const  auto& item : histogram->expectedMerged()){
        *set1 << item.second;
    }







    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);


    QChart *chart = new QChart();
    QString info = "Sample size: " + QString::number(histogram->sampleSize()) +
            "\t Chi-sqaure: " + QString::number(histogram->chi()) + " Degrees of freedom:" +
            QString::number(histogram->df()) + "\t P-value:" + QString::number(histogram->pvalue());




    chart->addSeries(series);
    chart->setTitle("Discrete Distribution Sample " + info);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setAnimationOptions(QChart::GridAxisAnimations);


    QStringList categories;

    for (const  auto& item : histogram->observedMerged()){
        categories << QString::number(item.first);
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
    Model * model = new Model(generator);
    model->setSampleSize(sampleSize);
    model->setD0(Distribution(getD0()));
    model->InitHistogram();
    m_chartHistogram = createChartHistogram(model->histogram());

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

