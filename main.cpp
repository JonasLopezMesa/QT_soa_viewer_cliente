#include "viewerwindow.h"
#include <QApplication>

int main(int argc, char *argv[])

{
    QApplication a(argc, argv); //sólo se puede crear un único objeto QApplication.
    ViewerWindow w; // crear objeto de la ventana
    w.show(); //mostrar la ventana

    QCoreApplication::setOrganizationName("Jonas");
    QCoreApplication::setApplicationName("viewer");

    return a.exec(); //La aplicación entra en el BUCLE DE MENSAJES. No se acaba hasta que se cierra la aplicación.
}
