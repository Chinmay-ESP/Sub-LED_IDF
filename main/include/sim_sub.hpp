#ifndef SIM_SUB_HPP
#define SIM_SUB_HPP

#include "urosElement.hpp"
#include <std_msgs/msg/int32.h>
#include <driver/gpio.h>
#include "esp_log.h"

class simSub : public urosElement {
    public:
        static simSub* sub;
        simSub();

        // Micro-ROS initialization
        void init();

        // Subscriber callback function
        static void subscription_callback(const void *msg);

    private:
        rcl_subscription_t subscriber;
        std_msgs__msg__Int32 msg;
};

class LEDController {
    private:
        gpio_num_t ledPin;
    
    public:
        // Constructor to initialize the LED pin
        explicit LEDController(gpio_num_t pin) : ledPin(pin) {
            gpio_reset_pin(ledPin);
            gpio_set_direction(ledPin, GPIO_MODE_OUTPUT);
        }
    
        // Method to turn the LED on/off
        void function(int dat) {  // Changed int -> void
            if (dat == 1) {
                gpio_set_level(ledPin, true);
            } else {
                gpio_set_level(ledPin, false);
            }
        }
};

#endif
