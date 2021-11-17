//
// Created by glushkov on 06.11.2021.
//

#include "TID_Generator.h"
#include "Generator.h"
TID_Generator::TID_Generator(const Distribution & dist) : Generator(dist){};
int32_t TID_Generator:: GenerateValue(double alpha)  {
    int i = 0, k = 0, j = m_distSize - 1;
    while (i < j) {
        k = floor((i + j) / 2);
        if (alpha <= m_s[k]) {
            j = k;
        } else {
            i = k + 1;
        }

    }
    return m_distribution.at(i).first;
}