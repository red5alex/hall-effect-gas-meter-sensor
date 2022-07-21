/*
  Sketch for reading a Hall Latch Sensor 

  TODO: 
  - MQTT communication
  - Add voltage divider to board for larger input range of sensor
  - add hysteresis in this script as additional noise filter
  - only trigger if there was no state change for n seconds.
  
*/

// pin definition
const int analogInPin = 4;  // Connect to Signal pin of 4913B TLE4913 Hall Effect Sensor
const int LedPin = 2;  // Analog input pin that the potentiometer is attached to
const int threshold = 4094;  // this is for 5V Power Supply


// variables
int state = 1;
int counter = 0;
int sensorValue = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LedPin, OUTPUT);
}

void loop() {
  // read analog value:
  sensorValue = analogRead(analogInPin);

  // register state 1 (no magnetic counter)
  if ((sensorValue > threshold) && (state == 0))
  { state = 1;
    counter++;
    digitalWrite(LedPin, HIGH);
  }

  // register state 0 (magnetic counter detected)
  else if ((sensorValue < threshold) && (state == 1))
  { state = 0;
    digitalWrite(LedPin, LOW);
  }

  

  // print the results to the Serial Monitor:
  Serial.print(state);
  Serial.print("\t");
  Serial.print(counter);
  Serial.print("\t");
  Serial.println(sensorValue);

  // delay to let the sensor settle on new value
  delay(5);
}
