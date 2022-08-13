Arduino-RC car-project
================
Remote Controlled Car build with Arduino Uno and communication via Bluetooth and self-driving RC car
---------------------------------------------
---
Software for Arduino Uno-based remote controlled car together with a Arduino Nano-based remote controlling and intercommunication via Bluetooth modules using C++   


### Hardware components used for Remote Controlled Car   
* Arduino **Uno** or compatible
* Battery or powerbank [ 5V, +1450 mAh ] to power-up Arduino and its components (bluetooth module and speaker)
* Battery or powerbank [ 12V, +4000 mAh ] to power-up motors
* Bluetooth HC-06 slave module
* L298N Driver to control motors
* Buzzer / piezo speaker
* 4 DC motors + wheels
* Optional dip switch to turn on/off the motor
* Car structure

### Software structure
The software is splitted into Abstraction Layers so the responsability of each layer are very limited and will make easier the growth and maintenance of the project in a Architectural point of view. Using a objected-oriented language such as C++ accepted by Arduino, makes the implementation closer to this approach.

