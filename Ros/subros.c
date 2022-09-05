// Subscription object
rcl_subscription_t subscriber;
const char * topic_name = "test_topic";

// Get message type support
const rosidl_message_type_support_t * type_support =
  ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

// Set client QoS
const rmw_qos_profile_t * qos_profile = &rmw_qos_profile_default;

// Initialize a subscriber with customized quality-of-service options
rcl_ret_t rc = rclc_subscription_init(
  &subscriber, &node,
  type_support, topic_name, qos_profile);

if (RCL_RET_OK != rc) {
  ...  // Handle error
  return -1;
}
