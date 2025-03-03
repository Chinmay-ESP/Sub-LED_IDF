#ifndef UROS_MASTER_NODE_HPP
#define UROS_MASTER_NODE_HPP

#include "urosElement.hpp"
// #include <freertos/FreeRTOS.h>
// #include <freertos/task.h>
#include <vector>
#include <string>
#include "driver/uart.h"


#ifndef UROS_OVER_SERIAL
#define UROS_OVER_SERIAL 0
#endif

#define UART_TXD 1
#define UART_RXD 3
#define UART_BUFFER_SIZE (512)  // 1024

class uros_master_node {
private:
    rcl_allocator_t allocator;
    rclc_support_t support;
    // rclc_support_t * support = 0;
    rcl_node_t node;
    // rclc_executor_t executor;

public:

    // micro ros node initialization
    // uros_master_node(std::string node_name);
    uros_master_node(const char * node_name);

    // adding uros elements
    void add_urosElement(std::vector<urosElement*> uros_elements);
};

#endif