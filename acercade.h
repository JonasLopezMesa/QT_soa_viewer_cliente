#ifndef ACERCADE_H
#define ACERCADE_H

#include <QDialog>

namespace Ui {
class acercade;
}

class acercade : public QDialog
{
    Q_OBJECT

public:
    explicit acercade(QWidget *parent = 0);
    ~acercade();

private:
    Ui::acercade *ui;
};

#endif // ACERCADE_H
