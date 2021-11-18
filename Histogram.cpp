
#include <cassert>
#include "Histogram.h"
 Histogram::Histogram(Generator *  sampleGenerator,Distribution d0, size_t sampleSize):
    m_sampleGenerator(sampleGenerator),
    m_sampleSize(sampleSize),
    m_distribution(d0),
    m_distSize(d0.getDistributionSize())
 {

        m_seed = std::chrono::system_clock::now().time_since_epoch().count();
        m_generator.seed(m_seed);
        m_uniform = new std::uniform_real_distribution<double> (0.0,1.0);


        int32_t m_plevels_N = 20;
        m_plevels.resize(m_plevels_N);
        m_distribSizeMerged = m_distSize;
        m_df = m_distSize - 1;
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
    double squareDiff = 0;
    GenerateSample();
    mergeExeptectedValues();


    for (auto &  [key,expected_value] : m_expectedMerged) {
        if (m_observed.count(key) != 0) {
            squareDiff = (m_observedMerged.at(key) - expected_value) * (m_observedMerged.at(key) - expected_value);
            m_chiValue += squareDiff / expected_value;
        }
        else {
            m_chiValue += expected_value;
        }

    }





    CHI(1, m_distSize - 1, m_chiValue, m_pvalue);
//    int f = floor(plevel * 100 / 10);
//    int s = ceil(static_cast<int>(floor(plevel * 100)) % 10);
//    ++m_plevels[f+s];
//    if (plevel < alpha){
//        m_alpha += 1;
//    }
    m_mean += m_chiValue;
    //std::cout << "Chi value : " << m_chiValue_2 << " m_plevel " << plevel << std::endl;
}

void Histogram::mergeExeptectedValues()
{
    const int NMAX = 5;
    m_expectedMerged = m_expected;
    m_observedMerged = m_observed;
    m_distribSizeMerged = m_distSize;

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

            m_distribSizeMerged -= 1;

        }
    }


}

int32_t Histogram::distSize() const
{
    return m_distSize;
}

int32_t Histogram::distribSizeMerged() const
{
    return m_distribSizeMerged;
}


int32_t Histogram::sampleSize() const
{
    return m_sampleSize;
}

const std::map<int32_t, uint64_t> Histogram::observedMerged() const
{
    return m_observedMerged;
}

const std::map<int32_t, double> Histogram::expectedMerged() const
{
    return m_expectedMerged;
}

double Histogram::chi() const
{
    return m_chiValue;
}

double Histogram::pvalue() const
{
    return m_pvalue;
}

int32_t Histogram::df() const
{
    return m_df;
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



uint64_t Histogram::MaxFrequency() const{
    uint64_t currentMax_1 = 0;
    double currentMax_2 = 0;
    for(auto it = m_observedMerged.cbegin(); it != m_observedMerged.cend(); ++it ) {
        if (it ->second > currentMax_1) {
            currentMax_1 = it->second;
        }
    }



    for(auto it = m_expectedMerged.cbegin(); it != m_expectedMerged.cend(); ++it ) {
        if (it ->second > currentMax_2) {
            currentMax_2 = it->second;
        }
    }
    auto val = currentMax_1 > currentMax_2 ? currentMax_1 : currentMax_2;
    return static_cast<uint64_t>(val);


}
