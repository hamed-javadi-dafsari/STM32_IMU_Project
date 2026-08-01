Start simulation:

powershell:
usbipd list
usbipd attach --wsl --busid 1-1

Terminal 1 — STM32 IMU
source ~/STM32_IMU_Project/imu_ws/install/setup.bash
ros2 run stm32_imu_bridge imu_node

Terminal 2 — Madgwick
source ~/STM32_IMU_Project/imu_ws/install/setup.bash
ros2 run stm32_imu_bridge madgwick_node

Terminal 3 — Gazebo
source /opt/ros/jazzy/setup.bash
gz sim empty.sdf

Terminal 4 — Spawn 
source /opt/ros/jazzy/setup.bash
gz service -s /world/empty/create \
--reqtype gz.msgs.EntityFactory \
--reptype gz.msgs.Boolean \
--req 'sdf_filename:"/home/hamedpcb/STM32_IMU_Project/imu_ws/src/imu_gazebo_bridge/models/box/model.sdf",name:"imu_box"'

Terminal 5 — Bridge ROS2 & Gazebo 
source /opt/ros/jazzy/setup.bash
ros2 run ros_gz_bridge parameter_bridge \
/world/empty/set_pose@ros_gz_interfaces/srv/SetEntityPose

Terminal 6 — test set_pose
source /opt/ros/jazzy/setup.bash
ros2 service list | grep set_pose

Terminal 7 — Connect IMU to Gazebo
source /opt/ros/jazzy/setup.bash
source ~/STM32_IMU_Project/imu_ws/install/setup.bash
ros2 run imu_gazebo_bridge imu_to_gazebo

help:
(test)
ros2 topic echo /imu/data --once
ros2 topic list
ros2 topic info /imu/data
ros2 topic info /imu/raw

source /opt/ros/jazzy/setup.bash
ros2 pkg list | grep ros_gz 

bild project
cd ~/STM32_IMU_Project/imu_ws
colcon build --symlink-install
source install/setup.bash
ros2 pkg list | grep imu

Restart ubuntu:
wsl --shutdown 
