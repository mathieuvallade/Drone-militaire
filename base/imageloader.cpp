#include "imageloader.h"
#include <QPixmap>
#include <QDebug>

ImageLoader::ImageLoader(const QString& filename, QObject *parent) :
    QObject(parent),
    filename(filename)
{
}

void ImageLoader::load()
{
    QPixmap pixmap;
    if (!pixmap.load(filename))
    {
        qWarning() << "Failed to load image:" << filename;
        emit imageLoaded(QPixmap());
        return;
    }

    emit imageLoaded(pixmap);
}
