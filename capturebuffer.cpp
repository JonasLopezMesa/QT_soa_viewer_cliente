#include "capturebuffer.h"

CaptureBuffer::CaptureBuffer()
{
}
bool CaptureBuffer::present(const QVideoFrame &frame)
{
    // A través de este método nos darán el frame para que
    // lo mostremos.
    QVideoFrame frameN(frame);
    frameN.map(QAbstractVideoBuffer::ReadOnly);
    QImage frameAsImage = QImage(frameN.bits(), frameN.width(),
        frameN.height(), frameN.bytesPerLine(),
        QVideoFrame::imageFormatFromPixelFormat(frameN.pixelFormat()));

    // Aquí el código que manipula frameAsImage...

    emit enviarImagen(frameAsImage);

    frameAsImage.copy();
    frameN.unmap();

    return true;
}
