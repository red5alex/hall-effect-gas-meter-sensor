/*
 * Server settings
 * Below settings uses the public MQTT broker of HiveMQ.
 * Note: All messages are public!
 */


#define MQTT_SERVER "192.168.188.2"
#define MQTT_PORT 1883
//#define MQTT_USER NULL --> Create this in credentials.h
//#define MQTT_PASSWORD NULL --> Create this in credentials.h

#define MQTT_LASTWILL_TOPIC "red5alex/gasmeter/lastwill"
#define MQTT_LASTWILL_MESSAGE "connection lost"
#define MQTT_LASTWILL_QOS 0
#define MQTT_LASTWILL_RETAIN false

/*
 * MQTT Actions
 * MQTT messages causing an action, e.g. switching a relais, are configured here.
 * Note that the main code must still be implemented in the main script.
 * Actions are received on one topic, and a confirmation is send on a different topic.
 * Here, all actions topics are in the same branch to ease subscrition.
 */

#define MQTT_SUBSCRIBE_TOPIC "red5alex/gasmeter/cmd/#"  // all messages matching this topic pattern will be evaluated by the mqtt_callback function.
#define TOPIC_LED_CMD  "red5alex/gasmeter/cmd/led"  // send "on" or "off" to switch inbuil LED
#define TOPIC_LED_STATUS  "red5alex/gasmeter/status/led"  // command will be confirmed on this channel

/* 
 *  MQTT Sensor updates
 *  Sensors readings are send at an intervall, given below as milliseconds.
 */

#define MQTT_UPDATE_INTERVALL 300000  // milliseconds after which new sensor values are send
#define TOPIC_SENSOR_HALL  "red5alex/gasmeter/sensor/counter"  // publish the current counter value
