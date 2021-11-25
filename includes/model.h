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
    bool isReady() const;

    const std::vector<double> &plevelsInteravals() const;
    const std::vector<uint32_t> &plevelDistribution() const;
    const std::vector<double> &sampleSizeInterval() const;
    const std::vector<double> &powerDependencyNormalized() const;
    const std::vector<double> &plevelObservedCDFNormalized() const;
    const std::vector<double> &plevelDistributionNormalized() const;
    const std::string &d0String() const;
    const std::string &d1String() const;
    const std::string &sampleSizesString() const;
    const std::string &significanceLevelString() const;
    const std::string &generatorMethod() const;


    // Setters
    void setD0(const Distribution &newD0);
    void setD1(const Distribution &newD1);
    void setPlevelsSize(uint32_t newPlevelsSize);
    void setSampleSize(uint64_t newSampleSize);
    void setGenerator(Generator  * newGenerator);
    void setSignificaneLevel(double newSignificaneLevel);
    void setIsPowerEstimate(bool newIsPowerEstimate);
    void setSampleSizeInterval(const std::vector<double> &newSampleSizeInterval);
    void setGeneratorMethod( std::string newGeneratorMethod);
    void setIsReady(bool newModelIsReady);
    void setD0String(const std::string &newD0String);
    void setD1String(const std::string &newD1String);
    void setSampleSizesString(const std::string &newSampleSizesString);
    void setSignificanceLevelString(const std::string &newSignificanceLevelString);



    // Core
    void createPlevelsSample();
    void createPlevelsDistribution();
    void createPowerDependencyTable(); // Зависимость мощности от объема выборки
    void InitPlevelsIntervals();
    void InitHistogram();



    //Test
    void PrintPlevels() const;
private:


    Distribution m_d0,m_d1;
    Generator * m_generator = nullptr;
    std::string m_generatorMethod;
    std::string m_d0String,m_d1String;
    std::string m_sampleSizesString;
    std::string m_significanceLevelString;
    bool m_isReady = false;
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
    std::vector<uint32_t> m_plevelDistribution; // Мощности/Ошибки первого рода для каждого уровня alpha
    std::vector<double> m_plevelDistributionNormalized;



};

#endif // MODEL_H
