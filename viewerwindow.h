#ifndef VIEWERWINDOW_H
#define VIEWERWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include "acercade.h"
#include "preferencias.h"
#include <QtMultimedia>
#include <QVideoWidget>
#include <QWidget>
#include <QCameraViewfinder>
#include <QCamera>
#include <QGridLayout>
#include <QTcpSocket>


namespace Ui {
class ViewerWindow;
}

class ViewerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ViewerWindow(QWidget *parent = 0);
    ~ViewerWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionSalir_triggered();

    void on_actionAbrir_triggered();

    void on_actionCargar_imagen_triggered();

    void on_actionAbrirpelicula_triggered();

    //void on_movie_frame(const QRect& rect);

    void on_checkBox_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_actionAcerca_de_triggered();

    void on_actionPreferencias_triggered();

    void on_actionCapturar_triggered();

    void capturaImagen(QImage image);

private:
    Ui::ViewerWindow *ui; //la ventana principal tiene un puntero al formulario
    QMovie *movie;
    int chec;
    QSettings settings;
    QTcpSocket * tcpSocket;
};

#endif // VIEWERWINDOW_H
