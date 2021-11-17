//
// Created by marshall on 28.10.2021.
//

#include "Generator.h"
Generator::Generator(const Distribution & dist) : m_dist(dist),m_distSize(m_dist.getDistributionSize()) {

    Initialize();
    GenerateSumProbabilities();
}



void Generator::Initialize() {
    m_distribution.resize(m_dist.getDistributionSize());
    for (size_t i = 0; i < m_dist.getDistributionSize(); ++i){
        auto p = std::make_pair(i,m_dist.getProbAt(i));
        m_distribution[i] = p;
    }
}
// Подсчёт накопленных вероятностей
void Generator::GenerateSumProbabilities(){
    m_s.resize(m_distSize);

    int i = 0, k = 0;
    m_s[i] = m_distribution.at(i).second; // d.at(i).second - вероятность для значения i
    while (k < m_distSize - 1) {
        ++k;
        m_s[k] = m_s[k - 1] + m_distribution.at(k).second;
    }
}
// Cортирую вероятности в порядке убывания вместе со значениями
void Generator::SortProbsDescend() {
    sort(m_distribution.begin(),m_distribution.end(),[=](std::pair<int32_t ,double> & a, std::pair<int32_t,double> & b) {
        return a.second > b.second;
    });
}