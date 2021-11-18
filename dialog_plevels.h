#ifndef DIALOG_PLEVELS_H
#define DIALOG_PLEVELS_H

#include <QDialog>

namespace Ui {
class Dialog_Plevels;
}

class Dialog_Plevels : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Plevels(QWidget *parent = nullptr);
    ~Dialog_Plevels();

private:
    Ui::Dialog_Plevels *ui;
};

#endif // DIALOG_PLEVELS_H
