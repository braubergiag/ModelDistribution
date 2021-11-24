#include "graphcreator.h"

GraphCreator::GraphCreator()
{

}


QCustomPlot * GraphCreator::createChartHistogram(Model * model)
{

    // Prepare model

    model->InitHistogram();
    model->histogram()->calcChi();


    // Chart stuff

     QVector<double> x_observed,y_observed,x_expected,y_expected;
    uint64_t maxYValue = model->histogram()->MaxFrequency() + (0.3 *  model->histogram()->MaxFrequency());
    uint32_t maxXValue;


    for (const  auto & item :  model->histogram()->observedMerged()){
       x_observed.push_back(item.first); // value
       y_observed.push_back(item.second); // frequency
    }
    for (const  auto & item :  model->histogram()->expectedMerged()){
        x_expected.push_back(item.first); // value
        y_expected.push_back(item.second); // frequency
    }
    maxXValue = x_expected.back();


    QCustomPlot * customPlot = new QCustomPlot();
    customPlot->yAxis->setRange(0, maxYValue );
    QCPBars *expected = new QCPBars(customPlot->xAxis, customPlot->yAxis);
    QCPBars *observed = new QCPBars(customPlot->xAxis, customPlot->yAxis);


     observed->setName("Observed");
     observed->setPen(QPen(Qt::blue));
     observed->setBrush(QBrush(QColor(54, 98, 186)));

     expected->setPen(QPen(QColor(232, 74, 74)));
     expected->setBrush(QBrush(QColor(232, 74, 74,100)));
     observed->setWidth(0.5);
     expected->setWidth(0.8);
     expected->setName("Expected");


     QVector<double> ticks;
     QVector<QString> labels;
     for (const auto & value: x_observed){
         ticks << value;
         labels << QString::number(value);
     }
     QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
     textTicker->addTicks(ticks, labels);
     customPlot->xAxis->setTicker(textTicker);
     customPlot->xAxis->setRange(-1, maxXValue + 1);

     expected->setData(x_expected,y_expected);
     observed->setData(x_observed,y_observed);


     customPlot->legend->setVisible(true);
     customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     customPlot->legend->setBrush(QColor(255, 255, 255, 100));
     customPlot->legend->setBorderPen(Qt::NoPen);
//     QFont legendFont = font();
//     legendFont.setPointSize(10);
//     customPlot->legend->setFont(legendFont);
     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);





    QString info = "Sample size: " + QString::number(model->histogram()->sampleSize())
            +   "\t Chi-sqaure: " + QString::number(model->histogram()->chi())
            +   "\t Degrees of freedom: "
            +   QString::number(model->histogram()->df())
            +   "\t P-value: " + QString::number(model->histogram()->pvalue())
            +   "\t Method: " + QString::fromStdString(model->generatorMethod());


    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, info, QFont("sans", 10, QFont::Normal)));

    customPlot->replot();
    return customPlot;

}

QCustomPlot *GraphCreator::createPlevelsGraph(Model  * model)

{
    // Prepare model
    model->InitHistogram();
    model->InitPlevelsIntervals();
    model->createPlevelsSample();

    QCustomPlot * customPlot = new QCustomPlot();


    QVector<double> x_observedCDF = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
    QVector<double> y_observedCDF  = QVector<double>(model->plevelObservedCDFNormalized().begin(),model->plevelObservedCDFNormalized().end());


    QVector<double> x_empiricalCDF = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
    QVector<double> y_empiricalCDF  = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());

    x_observedCDF.insert(0,0);
    y_observedCDF.insert(0,0);

    x_empiricalCDF.insert(0,0);
    y_empiricalCDF.insert(0,0);


    customPlot->addGraph();
    customPlot->graph(0)->setData(x_observedCDF,y_observedCDF);
    customPlot->graph(0)->setName("Observed Plevels CDF");
    //customPlot->graph(0)->setPen(QPen(QColor(227, 27, 27).lighter(500)));
    customPlot->graph(0)->setPen(QPen(Qt::blue));

    customPlot->addGraph();
    customPlot->graph(1)->setData(x_empiricalCDF,y_empiricalCDF);
    customPlot->graph(1)->setName("Empirical Plevels CDF");
    customPlot->graph(1)->setPen(QPen(Qt::red));
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("Plevels CDFs \t F(x)");



    QVector<double> ticks;
    QVector<QString> labels;


    for (qsizetype i = 0; i < x_empiricalCDF.size(); ++i){
        ticks << x_empiricalCDF[i];
        labels << QString::number(x_empiricalCDF[i]);
    }


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setRange(0,1.05);
    customPlot->yAxis->setTicker(textTicker);
    customPlot->yAxis->setRange(0,1.05);




    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
//    QFont legendFont = font();
//    legendFont.setPointSize(10);
//    customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);



    QString info =  "Sample size: " + QString::number(model->histogram()->sampleSize())
            + "\t Plevels sample size: " + QString::number(model->plevelsSize())
            + "\t Method: " + QString::fromStdString(model->generatorMethod());

    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, info, QFont("sans", 10, QFont::Normal)));
     customPlot->replot();
     return customPlot;

}

QCustomPlot *GraphCreator::createPowerGraph(Model *model)
{

     model->InitHistogram();
     model->createPlevelsDistribution();

     QCustomPlot * customPlot = new QCustomPlot();
     QString title = model->isPowerEstimate() ? "Power Estimate" : "Type 1 Error Estimate";
     QVector<double> x = QVector<double>(model->plevelsInteravals().begin(),model->plevelsInteravals().end());
     QVector<double> y  = QVector<double>(model->plevelDistributionNormalized().begin(),model->plevelDistributionNormalized().end());
     x.insert(0,0);
     y.insert(0,0);
     customPlot->addGraph();
     customPlot->graph(0)->setData(x,y);
     customPlot->graph(0)->setName(title);



     customPlot->xAxis->setLabel("Alpha");
     customPlot->yAxis->setLabel("PLevel \t rate");
     customPlot->xAxis->setRange(0,1);
     customPlot->yAxis->setRange(0,1);






     customPlot->legend->setVisible(true);
     customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
     customPlot->legend->setBrush(QColor(255, 255, 255, 100));
     customPlot->legend->setBorderPen(Qt::NoPen);
//     QFont legendFont = font();
//     legendFont.setPointSize(10);
//     customPlot->legend->setFont(legendFont);
     customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

     QString info = "Sample size: " + QString::number(model->histogram()->sampleSize())
             +  "\t Plevels sample size: " + QString::number(model->plevelsSize())
             +  "\t Method: " + QString::fromStdString(model->generatorMethod());


     customPlot->plotLayout()->insertRow(0);
     customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, info, QFont("sans", 10, QFont::Normal)));
     customPlot->replot();
     return customPlot;
}

QCustomPlot *GraphCreator::createPowerDependencyGraph(Model *model)
{

    // Prepare model
    model->InitHistogram();
    model->createPowerDependencyTable();

    QCustomPlot * customPlot = new QCustomPlot();

    QVector<double> x = QVector<double>(model->sampleSizeInterval().begin(),model->sampleSizeInterval().end());
    QVector<double> y  = QVector<double>(model->powerDependencyNormalized().begin(),model->powerDependencyNormalized().end());
    customPlot->addGraph();
    customPlot->graph(0)->setData(x,y);
    QString graphTitle = QString("Power vs.sample size");
    customPlot->graph(0)->setName(graphTitle);

    customPlot->xAxis->setLabel("Sample Size");
    customPlot->yAxis->setLabel("Power \t  rate");
    customPlot->xAxis->setRange(0, model->sampleSizeInterval().back() + model->sampleSizeInterval().back() * 0.1);


    customPlot->yAxis->setRange(0, model->maxPowerLevel() + model->maxPowerLevel() * 0.1);


    QVector<double> ticks;
    QVector<QString> labels;
    for (const auto & value: model->sampleSizeInterval()){
        ticks << value;
        labels << QString::number(value);
    }


    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customPlot->xAxis->setTicker(textTicker);
    customPlot->xAxis->setTickLabelRotation(60);

    customPlot->legend->setVisible(true);
    customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    customPlot->legend->setBorderPen(Qt::NoPen);
//     QFont legendFont = font();
//     legendFont.setPointSize(10);
//     customPlot->legend->setFont(legendFont);
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);



    QString info = "Plevels sample size: " + QString::number(model->plevelsSize())
            +   "\t Method: " + QString::fromStdString(model->generatorMethod());
            +  "\t [ alpha = " + QString::number(model->significaneLevel()) + "]";
    customPlot->plotLayout()->insertRow(0);
    customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, info, QFont("sans", 10, QFont::Normal)));
    customPlot->replot();
    return customPlot;
}
