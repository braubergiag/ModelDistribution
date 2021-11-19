
#include "TISM_Generator.h"


TISM_Generator::TISM_Generator(const Distribution & dist) : Generator (dist){
    SortProbsDescend();
    GenerateSumProbabilities();

}

TISM_Generator::~TISM_Generator()
{
    std::cout << "TISM_Generator destructor was called\n ";
};


int32_t TISM_Generator::GenerateValue(double alpha)  {
    int i = 0;
    while (alpha > m_s[i] && i < m_distSize - 1){
        i += 1;
    }
    return m_distribution.at(i).first;
}
