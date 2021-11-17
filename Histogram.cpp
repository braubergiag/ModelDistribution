
#include <cassert>
#include "Histogram.h"
 Histogram::Histogram(Generator *  sampleGenerator,Distribution d0, size_t sampleSize):
m_sampleGenerator(sampleGenerator), m_sampleSize(sampleSize),
m_distribution(d0), m_distSize(m_distribution.getDistributionSize()){

        m_seed = std::chrono::system_clock::now().time_since_epoch().count();
        m_generator.seed(m_seed);
        m_uniform = new std::uniform_real_distribution<double> (0.0,1.0);
        int32_t m_plevels_N = 20;
        m_plevels.resize(m_plevels_N);
         m_distribSizeMerged = m_distSize;
         CalculateExpectedFrequency();


};
void Histogram::GenerateSample()  {
    double  alpha = 0.0;
    m_observed.clear();
    for (int i = 0; i < m_sampleSize; ++i) {
        alpha = (*m_uniform)(m_generator);
        m_observed[m_sampleGenerator->GenerateValue(alpha)] += 1;
    }


}


void Histogram::calcChi(){
    double alpha = 0.05,plevel = 0.0;
    GenerateSample();
    mergeExeptectedValues();
    double m_chiValue = 0.0;
    double squareDiff = 0;

    double m_chiValue_1 = 0.0;
    for (auto &  [key,expected_value] : m_expectedMerged) {
        if (m_observed.count(key) != 0) {
            squareDiff = (m_observedMerged.at(key) - expected_value) * (m_observedMerged.at(key) - expected_value);
            m_chiValue_1 += squareDiff / expected_value;
        }
        else {
            m_chiValue_1 += expected_value;
        }

    }





    CHI(1, m_distSize - 1, m_chiValue_1, plevel);
    int f = floor(plevel * 100 / 10);
    int s = ceil(static_cast<int>(floor(plevel * 100)) % 10);
    ++m_plevels[f+s];
    if (plevel < alpha){
        m_alpha += 1;
    }
    m_mean += m_chiValue_1;
    //std::cout << "Chi value : " << m_chiValue_2 << " m_plevel " << plevel << std::endl;
}

void Histogram::mergeExeptectedValues()
{
    const int NMAX = 5;
    m_expectedMerged = m_expected;
    m_observedMerged = m_observed;


    for (int i = m_distSize - 1; i >= 0; i--) {
        if (m_expectedMerged[i] < NMAX) {
            if (i != 0){
                m_expectedMerged[i - 1] += m_expectedMerged[i];
                m_observedMerged[i - 1] += m_observedMerged[i];
            } else {
                m_expectedMerged[i + 1] += m_expectedMerged[i];
                m_observedMerged[i + 1] += m_observedMerged[i];

            }
            m_observedMerged.erase(i);
            m_expectedMerged.erase(i);

        }
    }


}

int32_t Histogram::distSize() const
{
    return m_distSize;
}

int32_t Histogram::sampleSize() const
{
    return m_sampleSize;
}
void Histogram::PrintObservedFreq(){
    std::cout << "ObservedFreq" << std::endl;
    for (const auto& [key,value] : m_observed){
        std::cout << key << "-" << value << std::endl;
    }
}
void Histogram::PrintExpectedFreq(){
    std::cout << "ExpectedFreq" << std::endl;
    for (const auto& [key,value] : m_expected){
        std::cout << key << "-" << value << std::endl;
    }
}
void Histogram::PrintObservedMergedFreq(){
    std::cout << "ObservedMergedFreq" << std::endl;
    for (const auto& [key,value] : m_observedMerged){
        std::cout << key << "-" << value << std::endl;
    }
}
void Histogram::PrintExpectedMergedFreq(){
    std::cout << "ExpectedMergedFreq" << std::endl;
    for (const auto& [key,value] : m_expectedMerged){
        std::cout << key << "-" << value << std::endl;
    }
}
void Histogram::CalculateExpectedFrequency(){

    for (size_t i = 0; i < m_distSize; ++i){
        m_expected[i] = m_sampleSize * m_distribution.getProbAt(i);
    }
}

void Histogram::PrintPlevels() {
    for (const auto & p : m_plevels){
        std::cout << p << " ";
    }
    std::cout << "\n";

}
