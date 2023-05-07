#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <QtGui>

class Steganography 
{
    
public:
    static bool encode(QImage &image, const QByteArray &message);
    static QByteArray decode(const QImage &image);
};

#endif // STEGANOGRAPHY_H
