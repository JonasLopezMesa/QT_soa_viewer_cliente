#include "acercade.h"
#include "ui_acercade.h"

acercade::acercade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::acercade)
{
    ui->setupUi(this);
}

acercade::~acercade()
{
    delete ui;
}

//AcercaDeDialog dialog;
//dialog.show() -> muestra y continúa con lo demás.
//dialog.dialog.exec() -> muestra y no se permite usar otra cosa...
//Los cuadros de diálogo pueden devolver un valor.
