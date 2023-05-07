#include "steganography.h"
#include <mqtt/async_client.h>
#include <QByteArray>
#include <QDebug>

#define SERVER_ADDRESS "tcp://broker.emqx.io:1883"
#define MQTT_TOPIC "/ynov/bordeaux/Drone-militaire"
#define CLIENT_ID "drone"

int main()
{
    QImage image(":/img/img/DroneIMG37337.png");
    Steganography steg;
    QByteArray message = "37°42'41.9\"S 144°59'33.0\"E;";

    steg.encode(image, message);

    image.save("image_steg.png");

    // Convertir l'image en base64
    QByteArray base64Data;
    QBuffer buffer(&base64Data);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");
    QString base64String = QString::fromLatin1(base64Data.toBase64().data());

    mqtt::async_client client(SERVER_ADDRESS, CLIENT_ID);
    mqtt::connect_options options;
    options.set_clean_session(true);
    qDebug() << "Connexion au serveur MQTT en cours...";
    mqtt::token_ptr conntok = client.connect(options);
    conntok->wait();    // Attente de la connexion
    qDebug() << "OK";

    // Envoyer la chaîne de caractères en base64 sur le topic MQTT
    mqtt::message_ptr pubmsg = mqtt::make_message(MQTT_TOPIC, "data:image/png;base64,"+base64String.toStdString());
    pubmsg->set_qos(2);
    mqtt::token_ptr pubtok = client.publish(pubmsg);
    pubtok->wait(); // Attente de la publication
    qDebug() << "Message publié avec succès sur le topic " << MQTT_TOPIC;

    // Déconnexion du serveur MQTT
    client.disconnect()->wait();
    qDebug() << "Déconnexion du serveur MQTT";

        return 0;
}
