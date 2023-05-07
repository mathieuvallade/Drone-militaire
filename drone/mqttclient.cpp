#include "mqttclient.h"

MqttClient::MqttClient(const std::string& serverAddress, const std::string& clientId, const std::string& topic, QObject* parent) :
    QObject(parent),
    m_serverAddress(serverAddress),
    m_clientId(clientId),
    m_topic(topic),
    m_client(serverAddress, clientId)
{
    m_connectOptions.set_clean_session(true);
    m_client.set_callback([this](const mqtt::message_received& message) {
        // rien à faire ici pour le moment
    });

    mqtt::connect_options connectOptions;
    connectOptions.set_clean_session(true);

    m_lastWillMsg = mqtt::make_message(m_topic, "");
    m_lastWillMsg->set_qos(1);
    m_lastWillMsg->set_retained(true);
    connectOptions.set_will_message(m_lastWillMsg);

    m_client.connect(connectOptions, nullptr, [this](const mqtt::connect_response& response) {
        onConnect(response);
    });
}

MqttClient::~MqttClient()
{
    m_client.disconnect()->wait();
}

void MqttClient::publish(const std::string& message)
{
    auto pubMsg = mqtt::make_message(m_topic, message);
    pubMsg->set_qos(1);
    m_client.publish(pubMsg)->wait();
}

void MqttClient::onConnect(const mqtt::connect_response& response)
{
    emit connected();
}

void MqttClient::onDisconnect(const mqtt::disconnect_response& response)
{
    emit disconnected();
}
