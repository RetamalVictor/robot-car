# Robot Car with Vision Guidance

This is a work in progress repository for the Robot Car with Vision guidance. 
The directory includes two folders for now.

- MotorControl: Contains the Arduino Sketch to run the Project "MotorControl.ino" (Still under development)
- Libraries: Contains the libraries needed for the project. Currently, they are two:
  - IMPU: My implementation for an interface to interact with the MPU6050, heavily inspired in [Detailed MPU6065 tutorial](https://www.youtube.com/watch?v=k5i-vE5rZR0&t=1939s)
  - MPU6050 library by Jeff Rowberg.

  The last commit included implementing Proportional control to follow a straight trajectory.  
  
## TODO

### Connectivity
- [ ] Wifi controller

### Camera
- [ ] Neural depth estimation
- [ ] Relative localization via Vision

### Motors

- [x] Motor driver
- [x] Interface for motors

### Servos

- [ ] Drivers and interface

### Sensors

- [x] Write sensors drivers
- [x] Extrac MPU6050 sensor information
- [x] Extrac Ultrasound information
- [x] Camera information
- [x] Navigation Filters

### Controllers

- [ ] Guidance algorithm
- [x] Control algorithm

### Software

- [ ] Write automatic tests
