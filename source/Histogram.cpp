
#include <cassert>
#include "Histogram.h"
 Histogram::Histogram(Generator *  sampleGenerator, size_t sampleSize):
     m_sampleGenerator(sampleGenerator),
     m_sampleSize(sampleSize){}

 Histogram::~Histogram()
 {
     delete m_uniform;
 };


void Histogram::GenerateSample()  {
    double  alpha = 0.0;
    m_observed.clear();
    for (size_t i = 0; i < m_sampleSize; ++i) {
        alpha = (*m_uniform)(m_generator);
        m_observed[m_sampleGenerator->GenerateValue(alpha)] += 1;
    }


}


void Histogram::calcChi(){
    double squareDiff = 0,diff = 0;
    GenerateSample();
    mergeExeptectedValues();

    m_chiValue = 0;
    for (auto &  [key,expected_value] : m_expectedMerged) {
        if (m_observedMerged.count(key) != 0) {
            diff = (m_observedMerged.at(key) - expected_value);
            squareDiff =  diff * diff;
            m_chiValue += squareDiff / expected_value;
        }
        else {
            m_chiValue += expected_value;
        }

    }


    CHI(1, m_distribSizeMerged - 1, m_chiValue, m_pvalue);
   //std::cout << "Pvalue << " << m_pvalue << std::endl;

    double m_expectedMergedSum = 0, m_observedMergedSum = 0;
    for (auto [k,v]: m_expectedMerged) {
        m_expectedMergedSum += v;
    }
    for (auto [k,v]: m_observedMerged) {
        m_observedMergedSum += v;
    }
    qDebug() << "m_expectedMergedSum" << m_expectedMergedSum  << "\n";
    qDebug() << "m_observedMergedSum" << m_observedMergedSum  << "\n";
    assert(m_observedMergedSum == m_sampleSize);


   m_mean += m_chiValue;

}













void Histogram::mergeExeptectedValues()
{
    const int NMAX = 5;
    m_expectedMerged = m_expected;
    m_observedMerged = m_observed;
    m_distribSizeMerged = m_distSize;

    size_t prev_index = 0;
    for (size_t i = 0; i < m_distSize; ++i) {
        if (m_expectedMerged.at(i) < NMAX) {
            if (i != ( m_distSize - 1)){
                m_expectedMerged[i + 1] += m_expectedMerged[i];
                m_observedMerged[i + 1] += m_observedMerged[i];

            } else {
                m_expectedMerged[prev_index] += m_expectedMerged[i];
                m_observedMerged[prev_index] += m_observedMerged[i];



            }
            m_observedMerged.erase(i);
            m_expectedMerged.erase(i);
            m_distribSizeMerged -= 1;

        } else {
            prev_index = i;
        }

    }





}

size_t Histogram::distSize() const
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

const std::map<int32_t, uint64_t> Histogram::observed() const
{
    return m_observed;
}

const std::map<int32_t, double> Histogram::expected() const
{
    return m_expected;
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

const Distribution &Histogram::d0() const
{
    return m_d0;
}

void Histogram::setD0(const Distribution &newD0)
{
    m_d0 = newD0;
}



void Histogram::setDf(int32_t newDf)
{
    m_df = newDf;
}

void Histogram::setDistSize(int32_t newDistSize)
{
    m_distSize = newDistSize;
}

void Histogram::Init()
{

    if (m_d0.getDistributionSize() != 0) {
        m_distSize = m_d0.getDistributionSize();
        m_df = m_distSize -1;
        if (m_sampleSize != 0){
             CalculateExpectedFrequency();
             m_isReady = true;
        }

    }


    m_seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_generator.seed(m_seed);
    m_uniform = new std::uniform_real_distribution<double> (0.0,1.0);
}

void Histogram::setSampleSize(uint64_t newSampleSize)
{

    m_sampleSize = newSampleSize;
    CalculateExpectedFrequency();
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
        m_expected[i] = m_sampleSize * m_d0.getProbAt(i);
    }
}

void Histogram::PrintPlevels() {
    for (const auto & p : m_plevels){
        std::cout << p << " ";
    }
    std::cout << "\n";

}



uint64_t Histogram::MaxFrequency() const{
    uint64_t currentMax_1 = 0, currentMax_2 = 0;

    for(auto it = m_expected.cbegin(); it != m_expected.cend(); ++it ) {
        if (it ->second > currentMax_1) {
            currentMax_1 = it->second;
        }
    }


    for(auto it = m_observed.cbegin(); it != m_observed.cend(); ++it ) {
        if (it ->second > currentMax_2) {
            currentMax_2 = it->second;
        }
    }

    uint64_t maxValue = currentMax_1 > currentMax_2 ? currentMax_1 : currentMax_2;
    return static_cast<uint64_t>(maxValue);


}
