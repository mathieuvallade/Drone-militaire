#include "mqttmanager.h"
#include <QDebug>

MqttManager::MqttManager(const std::string& address, const std::string& clientID, QObject* parent)
    : QObject(parent), m_client(address, clientID)
{
    m_client.set_callback(mqtt::create_callback_fun(
        [this](const mqtt::const_message_ptr& message) { onMessageReceived(message); },
        [this](const mqtt::delivery_token_ptr& token) { m_deliveryToken = token; }
        ));
}

MqttManager::~MqttManager()
{
    if (isConnected())
    {
        disconnect();
    }
}

void MqttManager::connect(const mqtt::connect_options& options)
{
    m_client.connect(options)->wait();
    m_isConnected = true;
}

void MqttManager::disconnect()
{
    m_client.disconnect()->wait();
    m_isConnected = false;
}

bool MqttManager::isConnected() const
{
    return m_isConnected;
}

void MqttManager::publishImage(const std::string& topic, const std::vector<uint8_t>& data)
{
    mqtt::message_ptr message = mqtt::make_message(topic, data);
    message->set_qos(2);
    m_client.publish(message)->wait_for(mqtt::seconds(10));
}

void MqttManager::onConnectionLost(const mqtt::connection_lost_reason& reason)
{
    qWarning() << "MQTT connection lost:" << reason;
    m_isConnected = false;
}

void MqttManager::onMessageReceived(const mqtt::const_message_ptr& message)
{
    emit messageReceived(message->get_topic(), std::vector<uint8_t>(message->get_payload(), message->get_payload() + message->get_payload_len()));
}
