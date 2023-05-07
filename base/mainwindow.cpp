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
        m_pixmap.load("image.png"); // Charger l'image
        emit newImage(m_pixmap); // Envoyer le signal avec l'image chargée
        sleep(1); // Attendre 1 seconde
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MqttSubscriber subscriber;
    // Connecter le signal newImage de la classe ImageThread au slot onNewImage de la classe MainWindow
    connect(&m_thread, &ImageThread::newImage, this, &MainWindow::onNewImage);

    // Démarrer le thread
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
    // Afficher l'image dans le QLabel
    ui->label_img->setPixmap(pixmap);
    QByteArray extractedMessage = steg.decode(image);
    QString message = QString::fromUtf8(extractedMessage);
    message.replace(QStringLiteral("°"), QStringLiteral("°"));
    message.replace(QChar('\''), QStringLiteral("’"));
    message.replace(QChar('\"'), QStringLiteral("’’"));
    message.replace(QChar(';'), QStringLiteral(" "));
    ui->label_3->setText("Le message cache: " + message);
}
