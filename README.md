# HallEffectGasMeter

Building a device for reading the pulse count of a gas meter using a hall effect sensor, and sending the counter value to an MQTT broker for further processing.

# Hardware used

- hall effect sensor 4913B TLE4913
- ESP32 or ESP8266
- 3 Dupont wires
- some kind of server to send MQTT messages to (e.g. node-red, home-assistant...)

Note: I tried a classic mechanical Reed sensor with this setup to no avail. Changing to a digital sensor with inbuilt hysteresis made the difference

# Checking the gasmeter

My gasmeter is a Actaris G4 RF1, however I am positive this setup can read-out any other meter with a magnetic pulse.

One of the dials contains a magnet.
I was able to figure out which one it is by moving a strong magnet in the vicinity which caused the relevant one to wiggle a little bit.
The sensor must be place close to this roller.

# 3D printed sensor holder

To hold the sensor in place, I have created a printable piece of plastic that press-fits into the slot above the holder and holds the sensor and cable firmly in place.
The CAD model is made using OnShape and can be seen [here](https://cad.onshape.com/documents/e0d259fd877c1182a09bbc17/w/994389497a324f97073d213b/e/8d6a3ead179d19c52f29340c?renderMode=0&uiState=62d9d468549a2247567e7bfb)

If you do not have a 3D printer, play dough will do just fine :)

# The Ardunio Sketch



