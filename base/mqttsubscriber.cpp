#include "mqttsubscriber.h"
#include "qimage.h"
#include <QString>
#include <QFile>

MqttSubscriber::MqttSubscriber()
{
    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(&client, "tcp://broker.emqx.io:1883", "MQTTMessageViewer", MQTTCLIENT_PERSISTENCE_NONE, NULL);
    MQTTClient_setCallbacks(client, this, NULL, &MqttSubscriber::messageArrived, NULL);

    int rc;
    if ((rc = MQTTClient_connect(client, &conn_opts)) != MQTTCLIENT_SUCCESS)
    {
        QString errorMessage = QString("Failed to connect to MQTT broker: %1").arg(rc);
    }
    else
    {
        QString successMessage = QString("Connected to MQTT broker at tcp://broker.emqx.io:1883");

        MQTTClient_subscribe(client, "/ynov/bordeaux/Drone-militaire", 0);
    }
}

int MqttSubscriber::messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    Q_UNUSED(context);
    Q_UNUSED(topicLen);
    QString fileName = "image.png";
    QString content = QString::fromUtf8((char *)message->payload, message->payloadlen);

    QString imageData = content.split(",")[1];
    QByteArray imageDataBytes = QByteArray::fromBase64(imageData.toUtf8());

    QImage image;
    image.loadFromData(imageDataBytes);

    QFile file("image.png");
    file.open(QIODevice::WriteOnly);
    image.save(&file, "PNG");
    file.close();

    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

