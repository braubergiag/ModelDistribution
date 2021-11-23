#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H



#include "qcustomplot.h"
#include "model.h"
class GraphCreator
{
public:
    QCustomPlot * createChartHistogram(Model * model,QString & info);
    QCustomPlot * createPlevelsGraph(Model  * model,QString & info);
    QCustomPlot * createPowerGraph(Model * model,QString & info);
    QCustomPlot * createPowerDependencyGraph(Model * model,QString & info);
    GraphCreator();
};

#endif // GRAPHCREATOR_H
