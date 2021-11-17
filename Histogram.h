//
// Created by glushkov on 06.11.2021.
//

#ifndef COUSERASPECYELLOW_HISTOGRAM_H
#define COUSERASPECYELLOW_HISTOGRAM_H


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
    int32_t GetObservedAt(int i ) const {return m_observed.at(i);}
    int32_t GetExpectedAt(int i ) const {return m_expected.at(i);}
    double GetMean()const {return m_mean;}
    double m_alpha = 0;
    int32_t distSize() const;

    int32_t sampleSize() const;

private:
    // Генератор псевдослучайных чисел
    unsigned m_seed;
    std::mt19937 m_generator;
    std::uniform_real_distribution<double> * m_uniform;

    double m_mean = 0;
    int32_t m_distribSizeMerged;
    Distribution m_distribution;
    int32_t m_distSize = 0;
    int32_t m_sampleSize = 0;
    std::vector<int32_t > m_plevels;
    std::map<int32_t,double> m_expected; // Теоретические частоты
    std::map<int32_t,uint64_t> m_observed;  // Эмпирические частоты
    std::map<int32_t,uint64_t>m_observedMerged;
    std::map<int32_t,double> m_expectedMerged;



};


#endif //COUSERASPECYELLOW_HISTOGRAM_H
