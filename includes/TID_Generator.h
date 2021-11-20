

#ifndef COUSERASPECYELLOW_TID_GENERATOR_H
#define COUSERASPECYELLOW_TID_GENERATOR_H


#include "Distribution.h"
#include "Generator.h"
// Метод моделирования Table Inverse Dichatomy (Метод обратной дихотомии)

class TID_Generator : public Generator{
public:
    explicit TID_Generator(const Distribution & dist);
    ~TID_Generator();
    int32_t GenerateValue(double alpha) override;
};


#endif //COUSERASPECYELLOW_TID_GENERATOR_H
