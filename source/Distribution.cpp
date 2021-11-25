
#include "Distribution.h"

const vector<double> &Distribution::p() const
{
    return m_p;
}

void Distribution::setP(const vector<double> &newP)
{
    m_p = newP;
    NormalizeDistribution();
}

Distribution::Distribution(const std::vector<double> & p) :m_p(p){
    NormalizeDistribution();
};


void Distribution::NormalizeDistribution() {
    double probsSum = 0;
    for (const auto& prob : m_p ) {
        probsSum += prob;
    }
    for ( auto& prob : m_p  ) {
        prob /= probsSum;
    }
}

std::ostream & operator <<(std::ostream& stream,Distribution & distribution) {
    for (size_t i = 0; i < distribution.getDistributionSize(); ++i ){
        stream << i << ' ' << distribution.getProbAt(i) << std::endl;
    }

    return stream;
}
