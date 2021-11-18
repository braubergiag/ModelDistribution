#include "model.h"

Model::Model(Generator * generator) : m_generator(generator)
{


}

Model::~Model()
{

    delete m_generator;
    delete m_histogram;
}

 Distribution Model::getD0() const
{
    return d0;
}

void Model::setD0(const Distribution &newD0)
{
    d0 = newD0;
}

 Distribution Model::getD1() const
{
    return d1;
}

void Model::setD1(const Distribution &newD1)
{
    d1 = newD1;
}

uint32_t Model::plevelsSize() const
{
    return m_plevelsSize;
}

void Model::setPlevelsSize(uint32_t newPlevelsSize)
{
    m_plevelsSize = newPlevelsSize;
}

Histogram *Model::histogram() const
{
    return m_histogram;
}

void Model::createPlevelsSample()
{

    for (size_t i = 0; i < m_plevelsSize; ++i){
        m_histogram->calcChi();
        m_currentPvalue = m_histogram->pvalue();

        for(auto & item : m_plevelObservedCDF ) {
            if (m_currentPvalue < item.first) {
                ++item.second;
                break;
            }

        }
    }


}

uint64_t Model::sampleSize() const
{
    return m_sampleSize;
}

void Model::setSampleSize(uint64_t newSampleSize)
{
    m_sampleSize = newSampleSize;
}

void Model::Init()
{
    double step_size = 1./ m_plevelsNum, currentStep = step_size;

    for (size_t i = 0; i < m_plevelsNum; ++i){
        m_plevelExpectedCDF[currentStep] = m_plevelsSize/ m_plevelsNum;
        currentStep += step_size;
    }

    // Test
    qDebug() << "m_plevelExpectedCDF \n";
    for(auto & item : m_plevelExpectedCDF ) {
        qDebug() << "Step: " << item.first << " Count :" << item.second << "\n";
    }

    currentStep = step_size;


    for (size_t i = 0; i < m_plevelsNum; ++i){
        m_plevelObservedCDF[currentStep] = 0;
        currentStep += step_size;
    }

   // Test
    qDebug() << "m_plevelExpectedCDF \n";
    for(auto & item : m_plevelObservedCDF ) {
        qDebug() << "Step: " << item.first << " Count :" << item.second << "\n";
    }

}

void Model::InitModel()
{
    m_distSize = d0.getDistributionSize();
}

void Model::InitHistogram()
{
    if (d0.getDistributionSize() != 0 && d1.getDistributionSize() !=0 && m_generator){
         m_histogram = new Histogram(m_generator,m_sampleSize);
         m_histogram->setD0(d0);

         m_histogram->setDistSize(m_distSize);
    }

}

void Model::PrintPlevels() const
{
    qDebug() << "m_plevelExpectedCDF \n";
    for(auto & item : m_plevelObservedCDF ) {
        qDebug() << "Step: " << item.first << " Count :" << item.second << "\n";
    }
}

uint32_t Model::distSize() const
{
    return m_distSize;
}

void Model::setDistSize(uint32_t newDistSize)
{
    m_distSize = newDistSize;
}
