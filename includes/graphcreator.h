#ifndef GRAPHCREATOR_H
#define GRAPHCREATOR_H



#include "qcustomplot.h"
#include "model.h"
class GraphCreator
{
public:
    QCustomPlot * createChartHistogram(Model * model);
    QCustomPlot * createPowerGraph(Model * model);
    QCustomPlot * createPowerDependencyGraph(Model * model);
    GraphCreator();
};

#endif // GRAPHCREATOR_H
