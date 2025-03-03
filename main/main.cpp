#include <stdio.h>
#include <rcl/error_handling.h>

#include "urosHandler.hpp"
#include "sim_sub.hpp"

uros_master_node* master_node = 0;

extern "C" void app_main(void)
{
    master_node = new uros_master_node("master_node");
    master_node->add_urosElement({
        new simSub() // Add the LED subscriber
    });
}
