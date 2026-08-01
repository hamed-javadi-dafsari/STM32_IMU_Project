# STM32 IMU ROS2 Gazebo Simulation

## Start Simulation

### Connect STM32 USB to WSL

Windows PowerShell:

```powershell
usbipd list
usbipd attach --wsl --busid 1-1
```

---

## Terminal 1 - STM32 IMU Node

```bash
source ~/STM32_IMU_Project/imu_ws/install/setup.bash
ros2 run stm32_imu_bridge imu_node
```

---

## Terminal 2 - Madgwick Filter

```bash
source ~/STM32_IMU_Project/imu_ws/install/setup.bash
ros2 run stm32_imu_bridge madgwick_node
```

---

## Terminal 3 - Gazebo

```bash
source /opt/ros/jazzy/setup.bash
gz sim empty.sdf
```

---

## Terminal 4 - Spawn IMU Box

```bash
source /opt/ros/jazzy/setup.bash

gz service -s /world/empty/create \
--reqtype gz.msgs.EntityFactory \
--reptype gz.msgs.Boolean \
--req 'sdf_filename:"/home/hamedpcb/STM32_IMU_Project/imu_ws/src/imu_gazebo_bridge/models/box/model.sdf",name:"imu_box"'
```

---

## Terminal 5 - ROS2 Gazebo Bridge

```bash
source /opt/ros/jazzy/setup.bash

ros2 run ros_gz_bridge parameter_bridge \
/world/empty/set_pose@ros_gz_interfaces/srv/SetEntityPose
```

---

## Terminal 6 - Test Gazebo Service

```bash
source /opt/ros/jazzy/setup.bash

ros2 service list | grep set_pose
```

---

## Terminal 7 - Connect IMU to Gazebo

```bash
source /opt/ros/jazzy/setup.bash
source ~/STM32_IMU_Project/imu_ws/install/setup.bash

ros2 run imu_gazebo_bridge imu_to_gazebo
```

---

# Test Topics

```bash
ros2 topic echo /imu/data --once

ros2 topic list

ros2 topic info /imu/data

ros2 topic info /imu/raw
```

---

# Build ROS2 Workspace

```bash
cd ~/STM32_IMU_Project/imu_ws

colcon build --symlink-install

source install/setup.bash

ros2 pkg list | grep imu
```

---

# Check Gazebo Dependencies

```bash
source /opt/ros/jazzy/setup.bash

ros2 pkg list | grep ros_gz
```

---

# Restart WSL

Windows PowerShell:

```powershell
wsl --shutdown
```
