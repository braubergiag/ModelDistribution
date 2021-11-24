//
// Created by marshall on 28.10.2021.
//

#ifndef COUSERASPECYELLOW_GENERATOR_H
#define COUSERASPECYELLOW_GENERATOR_H
#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <map>
#include <cstdint>
#include "probdist.h"
#include "Distribution.h"


class Generator {
public:
    Generator(const Distribution & dist);
    virtual ~Generator() = 0;
    Distribution GetDistribution() {return  m_dist;}
    size_t GetDistSize() const {return m_distSize;}

    virtual int32_t GenerateValue(double alpha) = 0;
protected:


    Distribution m_dist; // Распределение
    std::vector<std::pair<int32_t , double> > m_distribution; // Само распределение - Значение - Вероятность
    std::vector<double> m_s; // Накопленные вероятности

    size_t m_distSize = 0 ; // Размер распределения (количество значений в нём)
protected:
    void GenerateSumProbabilities(); // Подсчёт накопленных вероятностей
    void SortProbsDescend(); // Cортирую вероятности в порядке убывания вместе со значениями


private:
    // Перетаскиваю параметры распределения в вектор пар, чтобы мне было удобно его сортировать
    // Также исходные вероятности мы не трогаем
    void Initialize();


};




#endif //COUSERASPECYELLOW_GENERATOR_H
