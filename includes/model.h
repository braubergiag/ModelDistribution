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
    Model();
    ~Model();


    // Getters
    Generator *generator() const;
    Histogram *histogram() const;
    Distribution getD0() const;
    Distribution getD1() const;
    uint32_t plevelsInteravalsSize() const;
    uint32_t plevelsSize() const;
    uint64_t sampleSize() const;
    double significaneLevel() const;
    double maxPowerLevel() const;
    bool isPowerEstimate() const;


    const std::vector<double> &plevelsInteravals() const;
    const std::vector<uint32_t> &plevelObservedCDF() const;
    const std::vector<uint32_t> &plevelDistribution() const;

    const std::vector<double> &sampleSizeInterval() const;



    // Setters
    void setD0(const Distribution &newD0);
    void setD1(const Distribution &newD1);
    void setPlevelsSize(uint32_t newPlevelsSize);
    void setSampleSize(uint64_t newSampleSize);
    void setGenerator(Generator  * newGenerator);
    void setSignificaneLevel(double newSignificaneLevel);
    void setIsPowerEstimate(bool newIsPowerEstimate);
    void setSampleSizeInterval(const std::vector<double> &newSampleSizeInterval);



    // Core
    void createPlevelsSample();
    void createPlevelsDistribution();
    void createPowerDependencyTable(); // Зависимость мощности от объема выборки
    void InitPlevelsIntervals();
    void InitHistogram();



    //Test
    void PrintPlevels() const;






     std::string generatorMethod() const;
    void setGeneratorMethod( std::string newGeneratorMethod);

    const std::vector<double> &powerDependencyNormalized() const;

    const std::vector<double> &plevelObservedCDFNormalized() const;

    const std::vector<double> &plevelDistributionNormalized() const;

private:


    Distribution d0,d1;
    Generator * m_generator = nullptr;
    std::string m_generatorMethod;
    Histogram * m_histogram = nullptr;



    double m_currentPvalue = 0; // текущее p-value
    double m_significanceLevel = 0; // уровень значимости (alpha)
    double m_maxPowerLevel = 0; // Максимальный уровень мощности (нужен для посторения графика)
    uint64_t m_sampleSize = 0; // Объем выборки для моделирования
    uint64_t m_sampleSizeForPlevels = 0; // Объём выбооки для моделирования plevels
    uint32_t m_plevelsSize = 0; // Объем моделирования выборки p-levels
    uint32_t m_plevelsInteravalsSize = 20; // Количество интервалов для разбиения


    bool m_isPowerEstimate = true; // Оцениваем мощность или ошибку первого рода

    std::vector<double> m_sampleSizeInterval; // Объемы выборок, для которых считаем мощность
    std::vector<uint32_t> m_powerDependency; // Мощности для кажого объема выборки
    std::vector<double> m_powerDependencyNormalized;
    std::vector<double> m_plevelsInteravals; //  Значения теоретической ф.р plevels
    std::vector<uint32_t> m_plevelObservedCDF; // Значения эмирической ф.р plevels
    std::vector<double> m_plevelObservedCDFNormalized;
    std::vector<uint32_t> m_plevelDistribution; // Мощности/Ошибки первого рода для каждого уровня alpha
    std::vector<double> m_plevelDistributionNormalized;



};

#endif // MODEL_H
