#include "steganography.h"
typedef char char_t;
typedef unsigned long uint64_t;
typedef int int32_t;

bool Steganography::encode(QImage& image, const QByteArray& message) 
{
    if (image.format() != QImage::Format_RGB32) 
    {
        image = image.convertToFormat(QImage::Format_RGB32);
    }

    std::vector<bool> bits;
    for (int i = 0; i < message.size(); i++) 
    {
        char_t c = message.at(i);
        for (int j = 0; j < 8; j++) 
        {
            bits.push_back((c >> j) & 1);
        }
        if (c == ';') 
        {
            break;
        }
    }

    uint64_t index = 0;
    for (int32_t y = 0; y < image.height(); y++) 
    {
        for (int32_t x = 0; x < image.width(); x++) 
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
