#ifndef PREFERENCIAS_H
#define PREFERENCIAS_H

#include <QDialog>
#include "viewerwindow.h"

namespace Ui {
class Preferencias;
}

class Preferencias : public QDialog
{
    Q_OBJECT

public:
    explicit Preferencias(QWidget *parent = 0);
    ~Preferencias();

private slots:

    void on_comboBox_activated(int index);

private:
    Ui::Preferencias *ui;
    int sel;
    QSettings settings;
};

#endif // PREFERENCIAS_H
