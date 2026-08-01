import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Imu

import serial
import math


class STM32IMU(Node):

    def __init__(self):
        super().__init__('stm32_imu_node')

        self.publisher = self.create_publisher(
            Imu,
            '/imu/raw',
            10
        )

        self.serial = serial.Serial(
            '/dev/ttyACM0',
            115200,
            timeout=1
        )

        self.timer = self.create_timer(
            0.01,
            self.read_sensor
        )


    def read_sensor(self):

        try:

            line = self.serial.readline().decode().strip()

            if line.startswith("ACC"):

                print(line)

                # مثال:
                # ACC -133 7 2062 | GYRO -5 1 -2 | MAG -751 -523 2344 | BMP 7093248 8670720


                parts=line.replace("|","").split()


                ax=float(parts[1])
                ay=float(parts[2])
                az=float(parts[3])

                gx=float(parts[5])
                gy=float(parts[6])
                gz=float(parts[7])


                msg=Imu()


                msg.header.stamp=self.get_clock().now().to_msg()
                msg.header.frame_id="imu_link"


                # شتاب
                scale = 9.81 / 2048.0
                msg.linear_acceleration.x = ax * scale
                msg.linear_acceleration.y = ay * scale
                msg.linear_acceleration.z = az * scale


                # ژیروسکوپ
                msg.angular_velocity.x=math.radians(gx)
                msg.angular_velocity.y=math.radians(gy)
                msg.angular_velocity.z=math.radians(gz)


                self.publisher.publish(msg)



        except Exception as e:
            print(e)



def main(args=None):

    rclpy.init(args=args)

    node=STM32IMU()

    rclpy.spin(node)


    node.destroy_node()

    rclpy.shutdown()



if __name__=="__main__":
    main()
