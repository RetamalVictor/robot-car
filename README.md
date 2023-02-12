# Robot Car with Vision Guidance

This is a work in progress repository for the Robot Car with Vision guidance.

- Lib: Contains the libraries needed for the project. Appart from usual Arduino Framework libraries are:
  - IMPU: My implementation for an interface to interact with the MPU6050, heavily inspired in [Detailed MPU6065 tutorial](https://www.youtube.com/watch?v=k5i-vE5rZR0&t=1939s)
  - MPU6050 library by Jeff Rowberg.

  The last commit included implementing PID to follow a straight trajectory based on relative yaw.  
