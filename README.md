# STM32 IMU Project

## Real-Time IMU Sensor Fusion with STM32, ROS2 and Gazebo Simulation

This project implements a complete IMU processing pipeline using an **STM32F401RE** microcontroller, multiple sensors, **ROS2 Jazzy**, and **Gazebo Simulation**.

The goal of this project is to read real sensor data from an embedded system, process orientation data using sensor fusion algorithms, and visualize the real-world motion inside a Gazebo simulation environment.

---

# System Architecture

```
+----------------------+
| STM32F401RE           |
|                      |
|  ICM42688 IMU        |
|  QMC5883P Magnetometer|
|  BMP388 Barometer    |
+----------+-----------+
           |
           | USB CDC Serial
           |
           v
+----------------------+
| ROS2 Jazzy           |
|                      |
| stm32_imu_bridge     |
|                      |
| /imu/raw             |
+----------+-----------+
           |
           v
+----------------------+
| Madgwick Filter      |
|                      |
| Sensor Fusion        |
|                      |
| /imu/data            |
+----------+-----------+
           |
           v
+----------------------+
| imu_gazebo_bridge    |
+----------+-----------+
           |
           v
+----------------------+
| Gazebo Simulation    |
|                      |
| 3D Model Orientation |
+----------------------+
```

---

# Hardware

## Microcontroller

* STM32F401RE

## Sensors

### ICM42688

6-axis IMU:

* 3-axis Accelerometer
* 3-axis Gyroscope

Used for:

* Linear acceleration
* Angular velocity
* Orientation estimation

---

### QMC5883P

3-axis magnetometer:

Used for:

* Magnetic heading
* Yaw correction

---

### BMP388

High precision barometer:

Used for:

* Pressure measurement
* Altitude estimation

---

# STM32 Firmware

Location:

```
STM32_IMU_Project/
```

Implemented drivers:

```
Core/
 ├── bmp388.c
 ├── icm42688.c
 ├── qmc5883p.c
 └── sensors.c
```

The STM32 firmware:

* Initializes sensors through I2C
* Reads IMU data
* Sends sensor measurements through USB CDC serial

---

# ROS2 Packages

Location:

```
imu_ws/src/
```

## stm32_imu_bridge

Responsible for:

* Reading STM32 serial data
* Publishing raw IMU messages

ROS2 topics:

```
/imu/raw
```

---

## Madgwick Filter

Node:

```
madgwick_node
```

Responsibilities:

* Sensor fusion
* Quaternion orientation calculation

Output:

```
/imu/data
```

Message type:

```
sensor_msgs/Imu
```

---

## imu_gazebo_bridge

Responsible for:

* Receiving orientation data
* Sending pose updates to Gazebo

Input:

```
/imu/data
```

Output:

Gazebo model rotation

---

# Repository Structure

```
STM32_IMU_Project/

├── STM32_IMU_Project/
│   ├── Core/
│   ├── Drivers/
│   └── STM32_IMU_Project.ioc
│
├── imu_ws/
│   └── src/
│       ├── stm32_imu_bridge/
│       └── imu_gazebo_bridge/
│
├── RUN_SIMULATION.md
└── README.md
```

---

# Software Requirements

## Embedded

* STM32CubeIDE
* STM32 HAL Library

## Linux / ROS2

* Ubuntu
* ROS2 Jazzy
* Gazebo Sim
* ros_gz_bridge
* colcon

---

# Build ROS2 Workspace

```bash
cd ~/STM32_IMU_Project/imu_ws

colcon build --symlink-install

source install/setup.bash
```

---

# Run Simulation

For complete execution steps see:

```
RUN_SIMULATION.md
```

The simulation pipeline:

```
STM32
 ↓
imu_node
 ↓
madgwick_node
 ↓
imu_to_gazebo
 ↓
Gazebo
```

---

# Current Features

✅ STM32 sensor hub
✅ I2C sensor drivers
✅ Real-time USB communication
✅ ROS2 integration
✅ Madgwick orientation filter
✅ Gazebo model control using real IMU motion

---

# Future Development

Planned improvements:

* EKF sensor fusion
* GPS integration
* ROS2 Navigation stack
* Camera integration
* LiDAR integration
* PX4/MAVLink support
* Drone flight controller simulation

---

# Author

**Hamed Javadi Dafsari**

Embedded Systems & Robotics Development

GitHub:

```
https://github.com/hamed-javadi-dafsari
```

