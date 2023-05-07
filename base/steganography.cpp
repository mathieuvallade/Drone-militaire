#include "steganography.h"

QByteArray Steganography::decode(const QImage &image) {
    QByteArray extractedBits;
    for (int y = 0; y < image.height(); y++) {
        for (int x = 0; x < image.width(); x++) {
            QColor color = image.pixelColor(x, y);
            extractedBits.append(color.red() & 1);
            extractedBits.append(color.green() & 1);
            extractedBits.append(color.blue() & 1);
        }
    }

    QByteArray extractedMessage;
    for (int i = 0; i < extractedBits.size(); i += 8) {
        char c = 0;
        for (int j = 0; j < 8; j++) {
            c |= extractedBits.at(i + j) << j;
        }
        extractedMessage.append(c);
        if (c == ';') break;
    }

    return extractedMessage;
}
