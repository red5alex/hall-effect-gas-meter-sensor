# HallEffectGasMeter

Building a device for reading the pulse count of a gas meter using a hall effect sensor, and sending the counter value to an MQTT broker for further processing.

## Hardware used

- hall effect sensor 4913B TLE4913
- ESP32 or ESP8266
- 3 Dupont wires (female-female)
- some kind of server to send MQTT messages to (e.g. node-red, home-assistant...)

Note: I tried a classic mechanical Reed sensor with this setup to no avail. Changing to a digital sensor with inbuilt hysteresis made the difference

## Checking the gasmeter

My gasmeter is a Actaris G4 RF1, however I am positive this setup can read-out any other meter with a magnetic pulse.

One of the dials contains a magnet.
I was able to figure out which one it is by moving a strong magnet in the vicinity which caused the relevant one to wiggle a little bit.
The sensor must be place close to this roller.

## 3D printed sensor holder

To hold the sensor in place, I have created a printable piece of plastic that press-fits into the slot above the holder and holds the sensor and cable firmly in place: 

The CAD model is made using OnShape and can be seen [here](https://cad.onshape.com/documents/e0d259fd877c1182a09bbc17/w/994389497a324f97073d213b/e/8d6a3ead179d19c52f29340c?renderMode=0&uiState=62d9d468549a2247567e7bfb).

If you do not have a 3D printer, play dough should do just fine :)

After printing, the sensor slides into the little notch. Now, attach the dupont cables to its the sensor's terminals and presse them into the little grove (You can secure them with superglue or double sided tape, but it worked fine for me without an issue). I replaces the three single dupont shells with a triple one, which makes handling a bit easier.

## Wiring

Connect the other end of the dupont cable with the following terminals of the ESP

- GND to GND
- 3V3 to 3V3
- The signal terminal to GPIO34

You can choose another GPIO with ADC capability (see pinout of you DevBoard). Note: On ESP32, you cannot use the pins connected to ADC2, as this will conflict with the use of WiFi.

<img src="figs/fritzing-export.jpg" alt="wiring schematics">

# The Ardunio Sketch

The arduino sketch in the repository contains several configuration files.

- enter your WiFi credentials (rename `credentials-template.h` to `credentials.h` and add you WiFi name and password here)
- configure the MQTT broker. If using a public broker (e.g. HiveMQ), make sure to change the default topic.
- The pinout for the LED and Sensor input can be changed as well.

Compile and upload, and check the Serial monitor.
At startup, the LED (if present) will flash until network connectivity is present.

After that, the status LED will be on if the sensor is connected but not detecting the presence of the magnet. Check the connection if it does not come up.

Place a magnet close to the sensor and check if it will turn off. If not, you may need to adjust the threshold voltage in the code (it differs e.g. if powering the ESP32 board via a 5V supply (USB) or a 3.3V supply)

# 3D printed case for MicrController

I used the (ESP32 Open MQTT gateway box)[https://www.thingiverse.com/thing:5345637] by (Simedru Florin)[https://https://www.thingiverse.com/simedruflorin] as an enclosure for my ESP32 DevKit (Checkout his designs if using other boards, e.g. ESP8266).

The Dupont cables can be routed through its openings and secured with hotglue. Below a picture of the final assembly:

<img src="figs/mounted.jpg" alt="picture of the sensor mounted to the gasmeter">


# Example Application with Node-RED

The repository contains a minimal appliacation example, where the ESP32 sends the current count via an MQTT broker to node-red.

<img src="figs/mounted.jpg" alt="example nodes in node-red GUI">




