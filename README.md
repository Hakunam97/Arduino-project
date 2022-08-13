Smart Arduino-RC car-project
================
Remote Controlled Car build with Arduino Uno and communication via Bluetooth and Self-Driving RC car
---------------------------------------------
---
1. Software for Arduino Uno-based remote controlled car together with a Arduino Nano-based remote controlling and intercommunication via Bluetooth modules using C++   
2. Autonomous mode using Ultrasonic sensor for obstacle avoidance


### Hardware components used for Remote Controlled Car   
* Arduino **Uno** or compatible
* Battery or powerbank [ 5V, +1450 mAh ] to power-up Arduino and its components (bluetooth module and speaker)
* Battery or powerbank [ 12V, +4000 mAh ] to power-up motors
* HC-SR04 Ultrasonic Module
* Bluetooth HC-06 slave module
* Android Smartphone with Bluetooth
* Motor Drive Controller Module L298N
* Buzzer / piezo speaker
* 4 DC motors + wheels
* Sensor Shield
* Optional dip switch to turn on/off the motor
* Car structure

### Software structure
The software is splitted into Abstraction Layers so the responsability of each layer are very limited and will make easier the growth and maintenance of the project in a Architectural point of view. Using a objected-oriented language such as C++ accepted by Arduino, makes the implementation closer to this approach.




### Final Car Build
<img src='https://ifh.cc/g/O12cqY.jpg' width="50%" height="40%">
<img src='https://ifh.cc/g/vDOkHo.jpg' width="50%" height="40%">

---   
### Test and Driving
1. **Motor_test**  
(click the image below)

[![Video Label](http://img.youtube.com/vi/3k8P_rJN_Zc/0.jpg)](https://youtu.be/3k8P_rJN_Zc)

2. **Sub_motor_test**  
(click the image below)

[![Video Label](http://img.youtube.com/vi/WtocgYKOh2A/0.jpg)](https://youtu.be/WtocgYKOh2A)

3. **Remote Control**  
(click the image below)

[![Video Label](http://img.youtube.com/vi/K7encdYvTJI/0.jpg)](https://youtu.be/K7encdYvTJI)

4. **Self-Driving and Ultrasonic sensor**  
(click the image below)

[![Video Label](http://img.youtube.com/vi/biwDIe3V3Ak/0.jpg)](https://youtu.be/biwDIe3V3Ak)
