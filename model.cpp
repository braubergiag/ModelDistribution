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

       for (size_t j = 0; j < m_plevelsInteravals.size(); ++j) {
           if (m_currentPvalue < m_plevelsInteravals[j]) {
               ++m_plevelObservedCDF[j];
               break;
           }
       }
    }


    qDebug() << "m_plevelObservedFreq \n";
    for(auto & item : m_plevelObservedCDF ) {
        qDebug() << "Step: " << item.first << " Value :" << item.second << "\n";
    }

    // Нормировка
    for (size_t i = 0; i < m_plevelObservedCDF.size(); ++i) {
        m_plevelObservedCDF[i] /= m_plevelsSize;
    }

    // Cчитаем накопленные вероятности
    for (size_t i = 1; i < m_plevelObservedCDF.size(); ++i) {
        m_plevelObservedCDF[i] += m_plevelObservedCDF[i - 1];
    }

    // Тест
    qDebug() << "m_plevelObservedCDF \n";
    for(auto & item : m_plevelObservedCDF ) {
        qDebug() << "Step: " << item.first << " Value :" << item.second << "\n";
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

void Model::InitExpectedPlevelCDF()
{
    //double step_size = 1./ m_plevelsInteravals, currentStep = step_size; // Шаг.
    double entryInOneBar = (m_plevelsSize/ m_plevelsInteravalsSize); // Теоретическое значения кол-ва plevels в одной ячейке(диапазоне)
    double probabilityForOneEntry = entryInOneBar/ m_plevelsSize ; // Теоретическая вероятность попадания в ячейку (диапазон)

    for (size_t i = 0; i < m_plevelsInteravalsSize; ++i){
        if (i == 0) {
             m_plevelExpectedCDF[i] = probabilityForOneEntry;
             continue;
        }


        m_plevelExpectedCDF[i] = probabilityForOneEntry +  m_plevelExpectedCDF[i - 1];

    }


    // Test
    qDebug() << "m_plevelExpectedCDF \n";
    for(auto & item : m_plevelExpectedCDF ) {
        qDebug() << "Step: " << item.first << " Value :" << item.second << "\n";
    }



}

void Model::InitObservedPlevelCDF()
{


    for (size_t i = 0; i < m_plevelsInteravalsSize; ++i){
        if (i == 0) {
             m_plevelObservedCDF[i] = 0;
             continue;
        }


        m_plevelObservedCDF[i] = 0;

    }


    // Test
    qDebug() << "m_plevelExpectedCDF \n";
    for(auto & item : m_plevelExpectedCDF ) {
        qDebug() << "Step: " << item.first << " Value :" << item.second << "\n";
    }
}

void Model::InitPlevelsIntervals()
{
    double entryInOneBar = (m_plevelsSize/ m_plevelsInteravalsSize); // Теоретическое значения кол-ва plevels в одной ячейке(диапазоне)
    double probabilityForOneEntry = entryInOneBar/ m_plevelsSize ; // Теоретическая вероятность попадания в ячейку (диапазон)
    m_plevelsInteravals.resize(m_plevelsInteravalsSize);
    for (size_t i = 0; i < m_plevelsInteravals.size(); ++i){
        if ( i == 0){
             m_plevelsInteravals[i] = probabilityForOneEntry;
             continue;
        }
        m_plevelsInteravals[i] = m_plevelsInteravals[i - 1] + probabilityForOneEntry;


    }
    qDebug() << "Intervals \n";
    for (auto & interval: m_plevelsInteravals){
        qDebug() << interval << "\n";

      }

}

void Model::InitModel()
{
    m_distSize = d0.getDistributionSize();
}

void Model::InitHistogram()
{
    if (d0.getDistributionSize() != 0  && m_generator){
         m_histogram = new Histogram(m_generator,m_sampleSize);
         m_histogram->setD0(d0);
         m_histogram->Init();
    }

}

void Model::PrintPlevels() const
{
    qDebug() << "m_plevelObservedCDF \n";
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

const std::map<uint32_t, double> &Model::plevelExpectedCDF() const
{
    return m_plevelExpectedCDF;
}

const std::map<uint32_t, double> &Model::plevelObservedCDF() const
{
    return m_plevelObservedCDF;
}

const std::vector<double> &Model::plevelsInteravals() const
{
    return m_plevelsInteravals;
}
