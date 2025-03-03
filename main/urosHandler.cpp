#include "urosHandler.hpp"

#include <rmw_microros/rmw_microros.h>
#include <rmw_microros/custom_transport.h>

// #define TAG "DEBUG"

// #define RCCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Aborting.\n",__LINE__,(int)temp_rc);vTaskDelete(NULL);}}
// #define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){printf("Failed status on line %d: %d. Continuing.\n",__LINE__,(int)temp_rc);}}

bool esp32_serial_open(uxrCustomTransport* transport);
bool esp32_serial_close(uxrCustomTransport* transport);
size_t esp32_serial_write(
        uxrCustomTransport* transport,
        const uint8_t* buffer,
        size_t length,
        uint8_t* errcode);

size_t esp32_serial_read(
        uxrCustomTransport* transport,
        uint8_t* buffer,
        size_t length,
        int timeout,
        uint8_t* errcode);


// if issue in node_name then change type (string), then convert to c_str()
uros_master_node::uros_master_node(const char * node_name) {

    uart_port_t uart_port = UART_NUM_0;

    #if UROS_OVER_SERIAL == 0
        // setup custom transport for usb here
        rmw_uros_set_custom_transport(
            true,
            (void *) &uart_port,
            esp32_serial_open,
            esp32_serial_close,
            esp32_serial_write,
            esp32_serial_read);
    #endif

    allocator = rcl_get_default_allocator();
    
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
	// RCCHECK(rcl_init_options_init(&init_options, allocator));
	rcl_init_options_init(&init_options, allocator);
    // rcl_init_options_get_rmw_init_options(&init_options);

    // RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator));
    // rclc_support_t support;
    rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator);

    // rclc_support_init(&support, 0, NULL, &allocator);

    // RCCHECK(rclc_node_init_default(&node, node_name.c_str(), "", &support));
    rclc_node_init_default(&node, node_name, "", &support);
}

void uros_master_node::add_urosElement(std::vector<urosElement*> uros_elements) {
    rclc_executor_t executor = rclc_executor_get_zero_initialized_executor();
    rclc_executor_init(&executor, &support.context, 5, &allocator);

    for (auto elems : uros_elements) {
        elems->node = &node;
        elems->exec = &executor;
        elems->alloc = &allocator;
        elems->support = &support;

        elems->init();
    }

    rclc_executor_spin(&executor);
}


bool esp32_serial_open(uxrCustomTransport* transport)
{
    uart_port_t * uart_port = (uart_port_t*) transport->args;

    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    if (uart_param_config(*uart_port, &uart_config) == ESP_FAIL) {
        return false;
    }
    if (uart_set_pin(*uart_port, UART_TXD, UART_RXD, -1, -1) == ESP_FAIL) {
        return false;
    }
    if (uart_driver_install(*uart_port, UART_BUFFER_SIZE * 2, 0, 0, NULL, 0) == ESP_FAIL) {
        return false;
    }

    return true;
}

bool esp32_serial_close(uxrCustomTransport* transport)
{
    uart_port_t * uart_port = (uart_port_t*) transport->args;
    return uart_driver_delete(*uart_port) == ESP_OK;
}


size_t esp32_serial_write(
        uxrCustomTransport* transport,
        const uint8_t* buffer,
        size_t length,
        uint8_t* errcode)
{
    uart_port_t * uart_port = (uart_port_t*) transport->args;
    const int txBytes = uart_write_bytes(*uart_port, (const char*)buffer, length);
    return txBytes;
}


size_t esp32_serial_read(
        uxrCustomTransport* transport,
        uint8_t* buffer,
        size_t length,
        int timeout,
        uint8_t* errcode)
{
    uart_port_t * uart_port = (uart_port_t*) transport->args;
    const int rxBytes = uart_read_bytes(*uart_port, buffer, length, timeout / portTICK_PERIOD_MS);
    return rxBytes;
}