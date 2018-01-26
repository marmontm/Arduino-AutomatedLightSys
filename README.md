# Arduino-AutomatedLightSys

Automated lighting system  
  
Home automation lighting system with Arduino.
Program written in C++ for Arduino boards with ATmega328 CPU (like Arduino Uno and Nano)

## Tags
Arduino, C++, automation, RF-module, geii-lab-er2

## Project description

### Purpose
With this project, we can discover an approach of home automation and connected objects with a simple smart indoor lighting system. This system includes 2 parts: the ambient light sensor, and the lighting system.  
  
Both are wireless linked with RF-modules. The lighting system, when set in automatic mode, request remotely the sensor about how is the ambient light and then adjust the lighting system according to the user's order.   
  
So with such a system you can have an homogeneous light in your room whatever the outdoor light is, because the CPU adjusts it permanently for you.  
  
### Main features
This smart lighting system let the choice to the final user to manage the ambient light in 2 different modes:  
  
1. In manual mode: in this mode, the user can put the light on with the intensity he wants, from 0% (switched off) to 100% (maximum light and maximum power consumption), by step of 10 points.
  
2. In automatic mode: when the system is set in this mode, the user set an order and then the system is able to manage itself without any human action. Each second, it asks the sensor how is the ambient light, and then adjust it from 20% to 100% to have a global light corresponding to the user's order. When the system determinates a light compensation less than 20%, it will switch off the light because it is useless and by the way it will consume less energy.
  
And in automatic mode, if the system can't get the value of the light sensor, what will happen?   
  
If a problem appears on the sensor part (connection lost, power disconnected…), the system will use the previous value of the sensor. When the sensor is available again, the system will recognize it and re-establish automatically the connection with it. So no need to restart the system if a problem appears on the sensor part.

### Prototype images
![Controller part](/images/part1-controller.jpg)  
  
![Sensor part](/images/part2-sensor.jpg)  
  
> See other images in `/images/`.  

### Technologies and models used
In this system, there are 2 important technologies to link.  
  
1. The electronic part: which is composed by the Arduino boards (including the CPUs), the lighting system (represented as a lamp here), the RF-modules (allow the wireless connection) and the sensor (analog electronic). This part is the link between the intelligence and the real world (physics laws)  
  
2. The programming part: done with a computer, this part is the "brain" of the whole system. It permits to manage each part to make them working together. Each of them has one specific function. Two programs are done, one for the actuator part (including the management algorithm), and another for the sensor part
  
Another point is the communication between the sensor and the controller. One RF-module is wired to each part of the system (one for the sensor, the other on the controller). 
  
Because our set of element is very small (only 2 objects), we uses our own proprietary protocol which is fast, easy to implement and reliable.
  
## Additional information
Because this project was long to make it working, we made a diary about the whole project, including more explanations, schemes and the list of everything used. 
You can find everything you need in the documentation folder (`/documents/`) such as:
* The **study diary** and a **PowerPoint keynote** (only in French, sorry…)  
  
* **Schemes and drawings** (available both in French and English)

## How to use this repo?
Same for final user and developer:  
  
1. Download the repo  
  
2. Create 2 projects in your IDE: one for the sensor part, another one for the controller part
  
3. Import source files from:   
`/src-cpp-controller/` for controller program  
`/src-cpp-sensor/` for sensor program  
  
4. Set the target to Arduino Nano board for both projects  
> If you want to use an Arduino Uno (or other pins in your Nano board), don't forget to check the connected pins, and change them if needed.  
> You can find more information on internet about the boards (look for Arduino Nano pin map, Atmega328 pin map, and Atmega328 CPU documentation)  
	
5. Compile the programs and flash your Arduinos
  
6. Disconnect your boards from the computer and/or the power supply, and install each electronic element on the circuit
  
7. Power on the sensor, then the controller, and enjoy it :)
  
8. **For developers:** if you want to check the code, or modify it, don't forget to import the **MIRF** and **SPI** libraries to your IDE (located in `/librairies-cpp/`).  

## Credits
This work was done as part of a university project.
  
Done by **Alan Bello** and **Maxime Marmont**, 1st-year students in a 2-year university degree in Electrical Engineering and Computer Science (DUT GEII, Génie Electrique et Informatique Industrielle) in IUT Annecy, France.  
  
Thanks to the teachers, Bruno MANILLIER, Jean-Noël MARTIN and Thierry SUATON for their help.  
  
June 2016

## Copyright/license
MIT License  
Copyright © 2016 Alan BELLO & Maxime MARMONT
