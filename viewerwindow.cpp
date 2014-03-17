#include <QFileDialog> //NUEVO
#include <QFile> //NUEVO
#include <QTextStream> //NUEVO
#include <QMessageBox> //NUEVO
#include <QLabel> //NUEVO
#include <QWaitCondition>
#include <QMutex>
#include <QMovie>
#include <QtNetwork>


/*
 * constructor: QTCPSocket
 * destructor: delete QTCPSocket
 * slot: connectToHost(QSettings)
 *
*/


#include "viewerwindow.h"
#include "ui_viewerwindow.h"
#include "capturebuffer.h"

ViewerWindow::ViewerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewerWindow) //construye el formulario
{
    ui->setupUi(this); //configura el formulario
    //QSettings settings;
    chec = settings.value("stado").toInt();
    ui->checkBox->setChecked(chec);
    tcpSocket = new QTcpSocket(this);
}

ViewerWindow::~ViewerWindow()
{
    delete ui;
    delete tcpSocket;
}

void ViewerWindow::on_pushButton_clicked()
{
    qApp->quit(); //puntero al objeto de QApplication que se creó en el main
}

void ViewerWindow::on_actionSalir_triggered()
{
    qApp->quit();
}

void ViewerWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir archivo", QString(), "Texto (*.txt);;Fuente C++ (*.cpp)");//es necesario el primer include. Almacena el nombre del archivo que se selecciona en fileName.
    if(!fileName.isEmpty()) { // si se selecciona un fichero.
        QFile file(fileName); //creamos un objeto qfile con el nombre del fichero
        if(!file.open(QIODevice::ReadOnly)){ //Abrirlo como sólo lectura.
            //mensaje de error porque no se pudo abrir el archivo.
            QMessageBox::information(this, "Abrir archivo", "No se pudo abrir el archivo");
        }
        else {
            QTextStream stream(&file); //leer el contenido del archivo y meterlo en un editor. Necesario QTextStream.
            QString texto;
            texto = stream.readAll();
            ui->textEdit->setText(texto); //asigna el contenido de texto al objeto
        }
    }
}

void ViewerWindow::on_actionCargar_imagen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir imagen", QString(), "Images (*.png *.xpm *.jpg)");
    if(!fileName.isEmpty()) {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)){
            QMessageBox::information(this, "Abrir imagen", "No se pudo abrir la imagen");
        }
        else {
            /*Otras opciones
            1   QImage image(filename)
                QPixmap pixmap = QPixmap::fromImage(image)
            2   QImagereader ir(file)
                QPixmap pixmap = QPixmap::fromImageReader(ir)
                Te da la posibilidad de detectar dos errores: si el fichero existe y si es una imagen*/
            QPixmap pix(fileName);
            ui->label->setPixmap(pix);

            /*QWaitCondition wc;
            QMutex mutex; //Controla los hilos. Semáforo.
            wc.wait(&mutex, 5000); //bloquea el hilo en ejecución durante 5 segundos.*/


        }
    }
}

void ViewerWindow::on_actionAbrirpelicula_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir video", QString(), "video (*.mjpeg)");
    movie = new QMovie();

    movie->setFileName(fileName);
    if (!movie->isValid()) {
        QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo o el formato" " es inválido"));
        return;
    } else {
        if (ui->checkBox->checkState()==false) {
            //ui->label->setMovie(movie);
            connect(movie, SIGNAL(updated(const QRect&)), this, SLOT(on_movie_frame(const QRect&)));
            connect(ui->playButton, SIGNAL(clicked()), movie, SLOT(start()));
            connect(ui->stopButton, SIGNAL(clicked()), movie, SLOT(stop()));
        } else {
            ui->label->setMovie(movie);
            movie->start();
            connect(ui->playButton, SIGNAL(clicked()), movie, SLOT(start()));
            connect(ui->stopButton, SIGNAL(clicked()), movie, SLOT(stop()));
        }
    }
    //movie->start();
}

/*void ViewerWindow::on_movie_frame(const QRect& rect)
{
    QPixmap pixmap = movie->currentPixmap();
    ui->label->setPixmap(pixmap);
}*/

void ViewerWindow::on_checkBox_clicked()
{

}

void ViewerWindow::on_checkBox_stateChanged(int arg1)
{
    //QSettings settings;
    settings.setValue("stado", arg1);
}

void ViewerWindow::on_actionAcerca_de_triggered()
{
    acercade dialog;
    dialog.exec();
}

void ViewerWindow::on_actionPreferencias_triggered()
{
    Preferencias dialog;
    dialog.exec();
}

void ViewerWindow::on_actionCapturar_triggered()
{
    qDebug() << "sdfd";
    tcpSocket->connectToHost("127.0.0.1", 15000);
    if(tcpSocket->waitForConnected(3000)==true)
        qDebug() << "connected";


    int x = settings.value("dispAct").toInt(); //almacena en x el valor por defecto
    QList<QByteArray> devices = QCamera::availableDevices(); //
    QCamera * camera = new QCamera(devices[x]);
    CaptureBuffer *captureBuffer = new CaptureBuffer;
    camera->setViewfinder(captureBuffer);

    camera->start();

    connect(captureBuffer, SIGNAL(enviarImagen(QImage)), this, SLOT(capturaImagen(QImage)));
    /*
    QCameraViewfinder * viewfinder = new QCameraViewfinder;
    camera->setViewfinder(viewfinder);

    viewfinder->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    delete ui->label;
    ui->centralWidget->layout()->addWidget(viewfinder);
    //setCentralWidget(viewfinder);

    //camera->setCaptureMode(QCamera::CaptureVideo);
    camera->setCaptureMode(QCamera::CaptureViewfinder);
    camera->start();*/
}

void ViewerWindow::capturaImagen(QImage image) {
    //Obtener la hora
    QTime * tim = new QTime;
    QString hora;
    hora = tim->currentTime().toString();
    //ui->textEdit->setText(hora);
    //Pintar la hora en el frame
    QPainter time(&image);
    time.setPen(Qt::red);
    time.drawText(20,20,hora);
    //Mostrar el frame en el label
tcpSocket->write("HOLA\n", 5);
    QPixmap pix;
    pix = pix.fromImage(image);
    ui->label->setPixmap(pix);
}
