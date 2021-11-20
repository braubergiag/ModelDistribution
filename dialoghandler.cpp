#include "dialoghandler.h"

DialogHandler::DialogHandler()
{

}

std::vector<double> DialogHandler::parseTxtToVector(QLineEdit *  lineEdit)
{
    QString txt  = lineEdit->text();
    QStringList value_list = txt.split(",");
    std::vector<double> v(value_list.size());
    bool ok;
    for (size_t i = 0 ; i < value_list.size(); ++i){
       double value = value_list[i].toDouble(&ok);
       if (ok && value > 0) {
           v[i] = value;
           qDebug() << v[i] << " ";
       }

    }


    return v;
}

bool DialogHandler::checkSamleSize(QLineEdit *  lineEdit)
{
    bool ok;
    QMessageBox msgBox;
    const uint64_t SAMPLE_MAX_SIZE = 10e8;
    const uint64_t SAMPLE_BASE_SIZE = 10e4;
    int64_t sampleSize = lineEdit->text().toUInt(&ok);
    if (!ok ) {

        msgBox.setText("Объём выборки должен быть целым положительным числом.");
        lineEdit->setText(QString::number(SAMPLE_BASE_SIZE));
        msgBox.exec();

    } else if (sampleSize > SAMPLE_MAX_SIZE) {

        msgBox.setText("\n Максимальный размер выборки:" + QString::number(SAMPLE_MAX_SIZE));
        lineEdit->setText(QString::number(SAMPLE_BASE_SIZE));
        msgBox.exec();
    }

    else {
        return true;
    }
}






