//
// Created by glushkov on 06.11.2021.
//

#ifndef COUSERASPECYELLOW_TISM_GENERATOR_H
#define COUSERASPECYELLOW_TISM_GENERATOR_H

#include "Generator.h"


class TISM_Generator : public Generator {
public:
    TISM_Generator(const Distribution & dist);
    int32_t GenerateValue(double alpha) override ;


};

#endif //COUSERASPECYELLOW_TISM_GENERATOR_H
