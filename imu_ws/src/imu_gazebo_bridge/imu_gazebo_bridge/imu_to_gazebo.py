import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Imu

from ros_gz_interfaces.srv import SetEntityPose
from geometry_msgs.msg import Pose


class ImuToGazebo(Node):

    def __init__(self):

        super().__init__('imu_to_gazebo')

        self.sub = self.create_subscription(
            Imu,
            '/imu/data',
            self.imu_callback,
            10
        )

        self.client = self.create_client(
            SetEntityPose,
            '/world/empty/set_pose'
        )

        while not self.client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info(
                'Waiting for Gazebo set_pose service...'
            )

        self.get_logger().info(
            'Connected to Gazebo'
        )


    def imu_callback(self, msg):

        request = SetEntityPose.Request()

        request.entity.name = "imu_box"

        request.pose = Pose()

        request.pose.orientation.x = msg.orientation.x
        request.pose.orientation.y = msg.orientation.y
        request.pose.orientation.z = msg.orientation.z
        request.pose.orientation.w = msg.orientation.w


        self.client.call_async(request)


def main(args=None):

    rclpy.init(args=args)

    node = ImuToGazebo()

    rclpy.spin(node)

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()
