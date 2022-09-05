from example_interfaces.msg import Int64 
from std_msgs.msg import Int16MultiArray
import rclpy
import random
from rclpy.node import Node
import sys

class NumberPub(Node):
    def __init__(self):
        super().__init__("number_publisher")
        qos_policy = rclpy.qos.QoSProfile(reliability=rclpy.qos.ReliabilityPolicy.BEST_EFFORT,
                                          history=rclpy.qos.HistoryPolicy.KEEP_LAST,
                                          depth=1)
        self.publishers_ = self.create_publisher(Int16MultiArray, "tesa", qos_profile=qos_policy)
        self.timers_ = self.create_timer(0.5, self.pub_num)

    def pub_num(self):
        msg = Int16MultiArray()
        msg.data = [1,2,3,4]
        self.publishers_.publish(msg)
        self.get_logger().info(f"number: {msg.data}")


def main(args=None):
    rclpy.init(args=args)
    node = NumberPub()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
