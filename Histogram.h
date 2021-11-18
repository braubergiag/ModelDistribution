

#ifndef HISTOGRAM_H
#define HISTOGRAM_H


#include "Generator.h"
#include "Distribution.h"

class Histogram {
public:
    Histogram(Generator *  sampleGenerator,Distribution d0,size_t sampleSize);

    void GenerateSample();
    void calcChi();
    Generator *  m_sampleGenerator;
    Distribution m_d;

    void PrintObservedFreq();

    void PrintExpectedFreq();
    void PrintPlevels();
    void PrintObservedMergedFreq();
    void PrintExpectedMergedFreq();
    void CalculateExpectedFrequency();
    void mergeExeptectedValues();
    int32_t GetObservedAt(int i ) const {return m_observedMerged.at(i);}
    int32_t GetExpectedAt(int i ) const {return m_expectedMerged.at(i);}




    double MeanChiValue() const {return m_mean;}

    int32_t distSize() const;
     int32_t distribSizeMerged() const;
    uint64_t MaxFrequency() const;
    int32_t sampleSize() const;

    const std::map<int32_t, uint64_t> observedMerged() const;

    const std::map<int32_t, double> expectedMerged() const;

    double chi() const;

    double pvalue() const;

    int32_t df() const;

private:
    // Генератор псевдослучайных чисел
    unsigned m_seed;
    std::mt19937 m_generator;
    std::uniform_real_distribution<double> * m_uniform;


    Distribution m_distribution;

    double m_alpha = 0;
    double m_chiValue = 0;
    double m_pvalue = 0;
    double m_mean = 0;
    int32_t m_df = 0;
    int32_t m_distribSizeMerged;
    int32_t m_distSize = 0;
    int32_t m_sampleSize = 0;



    std::vector<int32_t > m_plevels;
    std::map<int32_t,double> m_expected; // Теоретические частоты
    std::map<int32_t,uint64_t> m_observed;  // Эмпирические частоты
    std::map<int32_t,uint64_t>m_observedMerged;
    std::map<int32_t,double> m_expectedMerged;



};


#endif
