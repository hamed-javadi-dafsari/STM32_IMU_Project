import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Imu

from ahrs.filters import Madgwick

import numpy as np


class MadgwickNode(Node):

    def __init__(self):

        super().__init__('madgwick_node')


        self.filter = Madgwick(
            sampleperiod=0.01,
            beta=0.1
        )


        self.q = np.array([1.0,0.0,0.0,0.0])


        self.sub = self.create_subscription(
            Imu,
            '/imu/raw',
            self.callback,
            10
        )


        self.pub = self.create_publisher(
            Imu,
            '/imu/data',
            10
        )


    def callback(self,msg):


        gyro=np.array([
            msg.angular_velocity.x,
            msg.angular_velocity.y,
            msg.angular_velocity.z
        ])


        acc=np.array([
            msg.linear_acceleration.x,
            msg.linear_acceleration.y,
            msg.linear_acceleration.z
        ])


        # نرمال کردن شتاب
        norm=np.linalg.norm(acc)

        if norm !=0:
            acc=acc/norm


        self.q=self.filter.updateIMU(
            self.q,
            gyr=gyro,
            acc=acc
        )


        out=Imu()


        out.header=msg.header


        # quaternion
        out.orientation.w=float(self.q[0])
        out.orientation.x=float(self.q[1])
        out.orientation.y=float(self.q[2])
        out.orientation.z=float(self.q[3])


        out.angular_velocity=msg.angular_velocity
        out.linear_acceleration=msg.linear_acceleration


        self.pub.publish(out)



def main(args=None):

    rclpy.init(args=args)

    node=MadgwickNode()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()



if __name__=="__main__":
    main()
