//
// Created by glushkov on 06.11.2021.
//

#include "TISM_Generator.h"


TISM_Generator::TISM_Generator(const Distribution & dist) : Generator (dist){
    GenerateSumProbabilities();
    SortProbsDescend();
};


int32_t TISM_Generator::GenerateValue(double alpha)  {
    int i = 0;
    while (alpha > m_s[i] && i < m_distSize - 1){
        i += 1;
    }
    return m_distribution.at(i).first;
}
