#include "steganography.h"

bool Steganography::encode(QImage &image, const QByteArray &message) 
{
    // Vérifier le format de l'image
    if (image.format() != QImage::Format_RGB32) {
        // Convertir l'image en format RGB32
        image = image.convertToFormat(QImage::Format_RGB32);
    }

    // Conversion du message en une séquence de bits
    QByteArray bits;
    for (int i = 0; i < message.size(); i++) 
    {
        char c = message.at(i);
        for (int j = 0; j < 8; j++) 
        {
            bits.append((c >> j) & 1);
        }
        if (c == ';') break; // Stopper la boucle si le caractère ';' est atteint
    }

    // Cacher le message dans l'image
    int index = 0;
    for (int y = 0; y < image.height(); y++) 
    {
        for (int x = 0; x < image.width(); x++) 
        {
            QColor color = image.pixelColor(x, y);
            if (index < bits.size()) 
            {
                color.setRed((color.red() & ~1) | bits.at(index++));
            }
            if (index < bits.size()) 
            {
                color.setGreen((color.green() & ~1) | bits.at(index++));
            }
            if (index < bits.size()) 
            {
                color.setBlue((color.blue() & ~1) | bits.at(index++));
            }
            image.setPixelColor(x, y, color);
        }
    }

    return true;
}

QByteArray Steganography::decode(const QImage &image) 
{
    QByteArray extractedBits;
    for (int y = 0; y < image.height(); y++) 
    {
        for (int x = 0; x < image.width(); x++) 
        {
            QColor color = image.pixelColor(x, y);
            extractedBits.append(color.red() & 1);
            extractedBits.append(color.green() & 1);
            extractedBits.append(color.blue() & 1);
        }
    }

    // Convertir la séquence de bits en message
    QByteArray extractedMessage;
    for (int i = 0; i < extractedBits.size(); i += 8) 
    {
        char c = 0;
        for (int j = 0; j < 8; j++) 
        {
            c |= extractedBits.at(i + j) << j;
        }
        extractedMessage.append(c);
        if (c == ';') break; // Stopper la boucle si le caractère ';' est atteint
    }

    return extractedMessage;
}
