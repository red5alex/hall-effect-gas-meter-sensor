#include "are_mqtt_config.h"

void mqtt_reconnect(PubSubClient *mqtt_client) {
  // Loop until we're reconnected
  while (!mqtt_client->connected()) {
    Serial.print("Attempting MQTT connection...");
    if (mqtt_client->connect(WIFI_HOSTNAME, MQTT_USER, MQTT_PASSWORD, MQTT_LASTWILL_TOPIC, MQTT_LASTWILL_QOS, MQTT_LASTWILL_RETAIN, MQTT_LASTWILL_MESSAGE)) {
      Serial.println("connected");
      mqtt_client->subscribe(MQTT_SUBSCRIBE_TOPIC);
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void mqtt_check_connection(PubSubClient *mqtt_client) {
    if (!mqtt_client->connected()) {
      Serial.println("not connected!");
      mqtt_reconnect(mqtt_client);
    }
}
