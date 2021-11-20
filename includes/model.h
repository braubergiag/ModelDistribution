#ifndef MODEL_H
#define MODEL_H

#include "Histogram.h"
#include "Generator.h"
#include "Distribution.h"

#include <QDebug>


class Model
{
public:
    Model(Generator * generator);
    ~Model();

     Distribution getD0() const;
    void setD0(const Distribution &newD0);

     Distribution getD1() const;
    void setD1(const Distribution &newD1);

    uint32_t plevelsSize() const;
    void setPlevelsSize(uint32_t newPlevelsSize);

    Histogram *histogram() const;
    uint64_t sampleSize() const;
    void setSampleSize(uint64_t newSampleSize);


    void createPlevelsSample();
    void createPlevelsDistribution();
    void InitPlevelsIntervals();
    void InitModel();
    void InitHistogram();
    void PrintPlevels() const;

    uint32_t distSize() const;
    void setDistSize(uint32_t newDistSize);



    const std::vector<double> &plevelsInteravals() const;

    const std::vector<double> &plevelObservedCDF() const;

    void setGenerator(Generator *newGenerator);

    const std::vector<double> &plevelDistribution() const;

    uint32_t plevelsInteravalsSize() const;

private:


    Distribution d0,d1;
    Generator * m_generator = nullptr;
    Histogram * m_histogram = nullptr;
    double m_currentPvalue = 0;
    uint64_t m_sampleSize = 0;
    uint32_t m_distSize = 0;
    uint32_t m_plevelsSize = 0;
    uint32_t m_plevelsInteravalsSize = 20; // Количество интервалов для разбиения

    std::vector<double> m_plevelsInteravals;
    std::vector<double> m_plevelObservedCDF;
    std::vector<double> m_plevelDistribution;



};

#endif // MODEL_H
