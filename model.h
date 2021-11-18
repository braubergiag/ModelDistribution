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

    void createPlevelsSample();

    uint64_t sampleSize() const;
    void setSampleSize(uint64_t newSampleSize);


    void Init();
    void InitModel();
    void InitHistogram();
    void PrintPlevels() const;

    uint32_t distSize() const;
    void setDistSize(uint32_t newDistSize);

private:


    Distribution d0,d1;
    Generator * m_generator = nullptr;
    Histogram * m_histogram = nullptr;
    double m_currentPvalue = 0;
    uint64_t m_sampleSize = 0;
    uint32_t m_distSize = 0;
    uint32_t m_plevelsSize = 0;
    uint32_t m_plevelsNum = 20; // Количество интервалов для разбиения

    std::map<double, uint32_t> m_plevelExpectedCDF;
    std::map<double, uint32_t> m_plevelObservedCDF;



};

#endif // MODEL_H
