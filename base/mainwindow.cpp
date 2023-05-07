#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mqttsubscriber.h"
#include "steganography.h"
#include <QDebug>


ImageThread::ImageThread(QObject *parent) :
    QThread(parent)
{

}

void ImageThread::run()
{
    while(true) {
        m_pixmap.load("image.png"); 
        emit newImage(m_pixmap); 
        sleep(1); 
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MqttSubscriber subscriber;
    connect(&m_thread, &ImageThread::newImage, this, &MainWindow::onNewImage);

    m_thread.start();
}

MainWindow::~MainWindow()
{
    m_thread.quit();
    m_thread.wait();
    delete ui;
}

void MainWindow::onNewImage(const QPixmap &pixmap)
{
    QImage image("image.png");
    Steganography steg;
    ui->label_img->setPixmap(pixmap);
    QByteArray extractedMessage = steg.decode(image);
    QString message = QString::fromUtf8(extractedMessage);
    message.replace(QStringLiteral("°"), QStringLiteral("°"));
    message.replace(QChar('\''), QStringLiteral("’"));
    message.replace(QChar('\"'), QStringLiteral("’’"));
    message.replace(QChar(';'), QStringLiteral(" "));
    ui->label_3->setText("Le message cache: " + message);
}
