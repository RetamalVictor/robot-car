# Robot Car

This project is based in the Elegoo Conqueror tank.

The directory includes two folders. 
- MotorControl: Contains the Arduino Sketch to run the Project "MotorControl.ino" (Still under development)
- Libraries: Contains the libraries needed for the project. Currently, they are two:
  - IMPU: My implementation for an interface to interact with the MPU6050, heavily inspired in [Detailed MPU6065 tutorial](https://www.youtube.com/watch?v=k5i-vE5rZR0&t=1939s)
  - MPU6050 library by Jeff Rowberg. 
  
  
  ## TODO:
  #### Motors
  - [x] Motor driver
  - [ ] Interface for motors
  #### Servos
  - [ ] Drivers and interface
  #### Sensors
  - [ ] Write sensors drivers
  - [x] Extrac MPU6050 sensor information
  - [ ] Extrac Ultrasound information
  - [ ] Camara information
  - [x] Navigation Filters
  #### Controllers
  - [ ] Guidance algorithm
  - [ ] Control algorithm
