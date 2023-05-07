#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include <QtGui>

class Steganography {
public:
    static QByteArray decode(const QImage &image);
};

#endif
