#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H


#include <mqtt/async_client.h>
#include <QObject>

class MqttClient : public QObject
{
    Q_OBJECT

public:
    explicit MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& topic, QObject* parent = nullptr);
    ~MqttClient();

public slots:
    void publish(const std::string& message);

signals:
    void connected();
    void disconnected();

private:
    std::string m_serverAddress;
    std::string m_clientId;
    std::string m_topic;

    mqtt::async_client m_client;
    mqtt::connect_options m_connectOptions;
    mqtt::message_ptr m_lastWillMsg;

    void onConnect(const mqtt::connect_response& response);
    void onDisconnect(const mqtt::disconnect_response& response);
};

#endif // MQTTCLIENT_H
