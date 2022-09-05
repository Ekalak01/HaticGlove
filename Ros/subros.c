from example_interfaces.msg import Int64 
from std_msgs.msg import String
import rclpy
import random
from rclpy.node import Node

class NumberSub(Node):
    def __init__(self):
        super().__init__("tesa_sub")
        qos_policy = rclpy.qos.QoSProfile(reliability=rclpy.qos.ReliabilityPolicy.BEST_EFFORT,
                                          history=rclpy.qos.HistoryPolicy.KEEP_LAST,
                                          depth=1)
        self.publishers_ = self.create_subscription(String, "rostestkub", self.sub, qos_profile=qos_policy)

    def sub(self, msg):
        data = list(map(int,msg.data.split(",")))
        self.get_logger().info(f"sub: {data}")
        # self.get_logger().info(f"x0: {data[0]}")
        # self.get_logger().info(f"x1: {data[1]}")
        # self.get_logger().info(f"x2: {data[2]}")
        # self.get_logger().info(f"x3: {data[3]}")
        


def main(args=None):
    rclpy.init(args=args)
    node = NumberSub()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == "__main__":
    main()
