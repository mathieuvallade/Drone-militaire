#pragma once

#include <QObject>
#include <mqtt/async_client.h>

class MqttManager : public QObject
{
    Q_OBJECT

public:
    explicit MqttManager(const std::string& address, const std::string& clientID, QObject* parent = nullptr);
    ~MqttManager();

    void connect(const mqtt::connect_options& options);
    void disconnect();

    bool isConnected() const;
    void publishImage(const std::string& topic, const std::vector<uint8_t>& data);

signals:
    void messageReceived(const std::string& topic, const std::vector<uint8_t>& data);

private:
    mqtt::async_client m_client;
    mqtt::delivery_token_ptr m_deliveryToken;
    bool m_isConnected = false;

    void onConnectionLost(const mqtt::connection_lost_reason& reason);
    void onMessageReceived(const mqtt::const_message_ptr& message);
};
