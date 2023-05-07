#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QObject>
#include <QPixmap>

class ImageLoader : public QObject
{
    Q_OBJECT
public:
    explicit ImageLoader(const QString& filename, QObject *parent = nullptr);

signals:
    void imageLoaded(const QPixmap& pixmap);

public slots:
    void load();

private:
    QString filename;
};

#endif // IMAGELOADER_H
