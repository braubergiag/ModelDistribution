#include "model.h"

Model::Model(Generator * generator) : m_generator(generator)
{


}

Model::Model()
{

}

Model::~Model()
{

    delete m_generator;
    delete m_histogram;
}

 Distribution Model::getD0() const
{
    return m_d0;
}

void Model::setD0(const Distribution &newD0)
{
    m_d0 = newD0;
}

 Distribution Model::getD1() const
{
    return m_d1;
}

void Model::setD1(const Distribution &newD1)
{
    m_d1 = newD1;
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



void Model::createPlevelsDistribution()
{
    m_plevelDistribution.clear();
    m_plevelDistribution.resize(m_plevelsInteravalsSize,0);




    for (size_t i = 0; i < m_plevelsSize; ++i){
        m_histogram->calcChi();
        m_currentPvalue = m_histogram->pvalue();

        for (size_t j = 0; j < m_plevelsInteravals.size(); ++j) {
            if (m_currentPvalue < m_plevelsInteravals[j]) {
                ++m_plevelDistribution[j];
                break;
            }
        }
    }




   m_plevelDistributionNormalized.clear();
   m_plevelDistributionNormalized.resize(m_plevelDistribution.size(),0);
   // Нормировка
   for (size_t i = 0; i < m_plevelDistribution.size(); ++i) {
       m_plevelDistributionNormalized[i] = static_cast<double>(m_plevelDistribution[i]) / m_plevelsSize;
   }


   for (size_t i = 1; i < m_plevelDistributionNormalized.size(); ++i) {
       m_plevelDistributionNormalized[i] += m_plevelDistributionNormalized[i - 1];
   }





   // Тест
   qDebug() << "m_plevelDistribution \n";
   for (size_t i = 0; i < m_plevelDistributionNormalized.size(); ++i) {
        qDebug() << "Step: " << i << " Value :" << m_plevelDistributionNormalized[i] << "\n";
   }



}

void Model::createPowerDependencyTable()
{


    if (m_sampleSizeInterval.size() == 0) return;

    m_powerDependency.clear();
    m_powerDependency.resize(m_sampleSizeInterval.size(),0);
    qDebug() << "Intervals for sampleSize";
    for (auto & el : m_sampleSizeInterval){
        qDebug() << el << " ";
    }


    for (size_t i = 0; i < m_sampleSizeInterval.size(); ++i) {
        m_histogram->setSampleSize(static_cast<uint64_t>(m_sampleSizeInterval[i]));
        for (size_t j = 0; j < m_plevelsSize; ++j){
            m_histogram->calcChi();
            if (m_histogram->pvalue() < m_significanceLevel) {
                ++m_powerDependency[i];
                continue;
            }
        }

    }

    m_maxPowerLevel = 0;
    m_powerDependencyNormalized.clear();
    m_powerDependencyNormalized.resize(m_powerDependency.size(),0);
    for (size_t i = 0; i < m_powerDependency.size(); ++i){
        m_powerDependencyNormalized[i] = static_cast<double>(m_powerDependency[i]) / m_plevelsSize;
        if (m_powerDependencyNormalized[i] > m_maxPowerLevel  ) {
            m_maxPowerLevel = m_powerDependencyNormalized[i];
        }
    }

    // Тест
    qDebug() << "m_powerDependency \n";
    for (size_t i = 0; i < m_powerDependencyNormalized.size(); ++i) {
         qDebug() << "N: " << m_sampleSizeInterval[i] << " Value :" << m_powerDependencyNormalized[i] << "\n";
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


void Model::InitHistogram()
{
    if (m_histogram){
        delete m_histogram;
    }

    if (m_d0.getDistributionSize() != 0  && m_generator){
         m_histogram = new Histogram(m_generator,m_sampleSize);
         m_histogram->setD0(m_d0);

         m_histogram->Init();
    } else {
        qDebug() << "Cannot initilize histogram \n";
    }

}


const std::string& Model::generatorMethod() const
{
    return m_generatorMethod;
}

void Model::setGeneratorMethod( std::string newGeneratorMethod)
{
    m_generatorMethod = newGeneratorMethod;
}

const std::vector<double> &Model::powerDependencyNormalized() const
{
    return m_powerDependencyNormalized;
}


const std::vector<double> &Model::plevelDistributionNormalized() const
{
    return m_plevelDistributionNormalized;
}

bool Model::isReady() const
{
    return m_isReady;
}

void Model::setIsReady(bool newModelIsReady)
{
    m_isReady = newModelIsReady;
}

const std::string &Model::d0String() const
{
    return m_d0String;
}

void Model::setD0String(const std::string &newD0String)
{
    m_d0String = newD0String;
}

const std::string &Model::d1String() const
{
    return m_d1String;
}

void Model::setD1String(const std::string &newD1String)
{
    m_d1String = newD1String;
}

const std::string &Model::sampleSizesString() const
{
    return m_sampleSizesString;
}

void Model::setSampleSizesString(const std::string &newSampleSizesString)
{
    m_sampleSizesString = newSampleSizesString;
}

const std::string &Model::significanceLevelString() const
{
    return m_significanceLevelString;
}

void Model::setSignificanceLevelString(const std::string &newSignificanceLevelString)
{
    m_significanceLevelString = newSignificanceLevelString;
}

void Model::setSampleSizeInterval(const std::vector<double> &newSampleSizeInterval)
{
    m_sampleSizeInterval = newSampleSizeInterval;
}




void Model::setGenerator(Generator *newGeneratorSample)

{
    if (m_generator){
        delete m_generator;
    }
    m_generator = newGeneratorSample;
}

Generator *Model::generator() const
{
    return m_generator;
}


const std::vector<double> &Model::plevelsInteravals() const
{
    return m_plevelsInteravals;
}


const std::vector<uint32_t> &Model::plevelDistribution() const
{
    return m_plevelDistribution;
}

uint32_t Model::plevelsInteravalsSize() const
{
    return m_plevelsInteravalsSize;
}



double Model::significaneLevel() const
{
    return m_significanceLevel;
}

void Model::setSignificaneLevel(double newSignificaneLevel)
{
    m_significanceLevel = newSignificaneLevel;
}

const std::vector<double> &Model::sampleSizeInterval() const
{
    return m_sampleSizeInterval;
}

double Model::maxPowerLevel() const
{
    return m_maxPowerLevel;
}

bool Model::isPowerEstimate() const
{
    return m_isPowerEstimate;
}

void Model::setIsPowerEstimate(bool newIsPowerEstimate)
{
    m_isPowerEstimate = newIsPowerEstimate;
}
