#include "sim_sub.hpp"

#define TAG "LED_SUB"
#define LED_PIN 2 // GPIO2 for LED

const char * sub_topic_name = "/led_control";

simSub* simSub::sub = 0;

// Message type support
const rosidl_message_type_support_t * sub_type_support = ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32);

simSub::simSub() { sub = this; }

void simSub::init() {
    // Initialize subscriber
    rclc_subscription_init_default(&subscriber, node, sub_type_support, sub_topic_name);

    // Add subscriber to executor
    rclc_executor_add_subscription(exec, &subscriber, &sub->msg, &simSub::subscription_callback, ON_NEW_DATA);
    
    ESP_LOGI(TAG, "LED subscriber initialized successfully!");
}

void simSub::subscription_callback(const void *msg) {
    const std_msgs__msg__Int32 *data = (const std_msgs__msg__Int32 *)msg;

    LEDController ledController(GPIO_NUM_23);
    ledController.function(data->data);  // Fixed typo: `dta -> data`
}
