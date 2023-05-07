#ifndef MQTTSUBSCRIBER_H
#define MQTTSUBSCRIBER_H

#include "MQTTClient.h"
class MqttSubscriber
{

public:
    MqttSubscriber();
private:

    MQTTClient client;

    static int messageArrived(void *context, char *topicName, int topicLen, MQTTClient_message *message);
};

#endif // MQTTSUBSCRIBER_H
