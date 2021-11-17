
#ifndef COUSERASPECYELLOW_DISTRIBUTION_H
#define COUSERASPECYELLOW_DISTRIBUTION_H

#include <vector>
#include <iostream>
#include <QVector>
using std::vector;
using std::string;

struct Distribution {
private:
    QVector<double> m_p;
public:
    Distribution(const QVector<double> & p);
    Distribution(){};
    double getProbAt(int i) {return m_p[i];}
    size_t getDistributionSize() const {return m_p.size();}
    void NormalizeDistribution();
};

std::ostream & operator <<(std::ostream& stream,Distribution & distribution);


#endif //COUSERASPECYELLOW_DISTRIBUTION_H
