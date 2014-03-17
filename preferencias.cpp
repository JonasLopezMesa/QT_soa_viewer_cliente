#include "preferencias.h"
#include "ui_preferencias.h"
#include "viewerwindow.h"

Preferencias::Preferencias(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preferencias)
{
    ui->setupUi(this);
    //PERMITE BUSCAR Y MOSTRAR EN EL comboBox la lista de Cámaras
    QList<QByteArray> dispositivos = QCamera::availableDevices();
    ui->comboBox->addItem("Predeterminada");
    for (int i = 0; i < dispositivos.size(); i++) {
        ui->comboBox->addItem(QCamera::deviceDescription(dispositivos[i]));
    }
    //HASTA AQUÍ.
    sel = settings.value("dispAct").toInt();
    ui->comboBox->setCurrentIndex(sel);
}

Preferencias::~Preferencias()
{
    delete ui;
}

void Preferencias::on_comboBox_activated(int index)
{
    settings.setValue("dispAct", index);
}
