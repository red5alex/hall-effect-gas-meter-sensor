/*
  Sketch for reading a Hall Latch Sensor

  TODO:
  - MQTT communication
  - Add voltage divider to board for larger input range of sensor
  - add hysteresis in this script as additional noise filter
  - only trigger if there was no state change for n seconds.

*/

#include <Arduino.h>
#include <PubSubClient.h>

#include "credentials.h"

// load wifi library and - settings
#include "are_wifi_config.h"
#include "are_wifi.h"
#include "are_mqtt_config.h"
#include "are_mqtt.h"

// pin definition
const int analogInPin = 4;  // Connect to Signal pin of 4913B TLE4913 Hall Effect Sensor
const int LedPin = 2;  // Analog input pin that the potentiometer is attached to
const int threshold = 4094;  // this is for 5V Power Supply


// variables
long lastMsg = 0; // time counter for MQTT intervalls
int state = 1;
int counter = 0;
int sensorValue = 0;
int sensorValue_last = 0;
bool sensor_high = false;
bool sensor_rising = false;
bool notify_serial = false;
bool notify_mqtt = false;


//MQTT settings
WiFiClient espClient;
PubSubClient mqttclient(espClient);

/* MQTT callback
   This code sections reacts to incoming MQTT messages.
*/

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("mqqt message arrived on topic: ");
  Serial.println(topic);

  // cast payload to string object
  String messageTemp;
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();


  /*
    // Changes the output state according to the message and publish a confirmation
    if (String(topic) == TOPIC_LED_CMD) {
    if (messageTemp == "on") {
      Serial.println("LED on");
      digitalWrite(GPIO_LED, HIGH);
      mqttclient.publish(TOPIC_LED_STATUS, "on");
    }
    else if (messageTemp == "off") {
      Serial.println("LED off");
      digitalWrite(GPIO_LED, LOW);
      mqttclient.publish(TOPIC_LED_STATUS, "off");
    }
  */
  // Add more commands here ...


}


void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);

  // initialize device
  //pinMode(GPIO_LED, OUTPUT);

  // connect to Wifi
  connect_to_wifi(WIFI_SSID, WIFI_PASSWORD, WIFI_HOSTNAME);

  // Connect to MQTT Server
  mqttclient.setServer(MQTT_SERVER, MQTT_PORT);
  mqttclient.setCallback(callback);

}

void loop() {


  // let mqtt work
  mqttclient.loop();
  
  notify_serial = false;
  notify_mqtt = false;

  // read analog value:
  sensorValue = analogRead(analogInPin);
  Serial.print(sensorValue);
  Serial.println("\n");

  if (sensorValue > threshold)
    sensor_high = true;
  else
    sensor_high = false;

  if (sensorValue > sensorValue_last)
    sensor_rising = true;
  else
    sensor_rising = false;


  // register state 1 (no magnetic counter)
  if ((sensorValue > threshold) && (state == 0))
  { state = 1;
    counter++;
    digitalWrite(LedPin, HIGH);
    notify_serial = true;
    notify_mqtt = true;
  }

  // register state 0 (magnetic counter detected)
  else if ((sensorValue < threshold) && (state == 1))
  { state = 0;
    digitalWrite(LedPin, LOW);
    notify_serial = true;
  }

  if (notify_serial)
  {

    // print the results to the Serial Monitor:
    Serial.print(sensor_high);
    Serial.print("\t");
    Serial.print(sensor_rising);
    Serial.print("\t");
    Serial.print(state);
    Serial.print("\t");
    Serial.print(counter);
    Serial.print("\t");
    Serial.println(sensorValue);
  }

  // check of MQTT message must be send due set message intervall
  long now = millis();
  if (now - lastMsg > MQTT_UPDATE_INTERVALL) {
    lastMsg = now;
    notify_mqtt = true;

  }

  if (notify_mqtt)
  {

    // ensure connection to mqtt broker
    mqtt_check_connection(&mqttclient);

    // Convert sensor reading from float to a char array
    char tempString[8];  // increase array length if having runtime errors
    dtostrf(counter, 1, 2, tempString);
    Serial.print("sending mqtt payload: ");
    Serial.print(tempString);
    Serial.println("\n");
    mqttclient.publish(TOPIC_SENSOR_HALL, tempString);
  }
 
  // delay to let the sensor settle on new value
  delay(5);
}
