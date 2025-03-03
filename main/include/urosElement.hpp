
#ifndef UROS_ELEMENT_HPP
#define UROS_ELEMENT_HPP

#include <rclc/rclc.h>
#include <rclc/executor.h>


class urosElement {

public:
    rclc_support_t* support = 0;
    rclc_executor_t* exec = 0;
    rcl_node_t* node = 0;
    rcl_allocator_t* alloc = 0;


    virtual void init() = 0;

};



#endif // UROS_ELEMENT_HPP