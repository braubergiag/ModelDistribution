#ifndef DIALOGHANDLER_H
#define DIALOGHANDLER_H


#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QGroupBox>
#include "Generator.h"
#include "TID_Generator.h"
#include "TISM_Generator.h"
class DialogHandler
{
public:
    DialogHandler();
    std::vector<double> parseTxtToVector(QLineEdit * lineEdit);
    bool checkSamleSize(QLineEdit * lineEdit);


};

#endif // DIALOGHANDLER_H
