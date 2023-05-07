#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qdatetime.h"
#include <QMainWindow>
#include <QThread>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ImageThread : public QThread
{
    Q_OBJECT

public:
    explicit ImageThread(QObject *parent = nullptr);
    void run() override;

signals:
    void newImage(const QPixmap &pixmap);

private:
    QPixmap m_pixmap;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    ImageThread m_thread;

private slots:
    void onNewImage(const QPixmap &pixmap);

};

#endif // MAINWINDOW_H
