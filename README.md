# Micro-ROS LED Subscriber on ESP32

## Overview
This project demonstrates the implementation of a Micro-ROS subscriber on an ESP32. The ESP32 subscribes to the `/led_control` topic and controls an LED based on the received messages.

## Features
- Implements a Micro-ROS subscriber to listen for LED control commands.
- Uses `urosHandler` for managing Micro-ROS nodes and subscriptions.
- Controls an LED using GPIO on the ESP32.
- Compatible with the `std_msgs/msg/Int32` message type.

## Repository Structure
```
├── main.cpp             # Entry point for the Micro-ROS application
├── sim_sub.cpp          # Implements the subscriber functionality
├── sim_sub.hpp          # Header file for the subscriber class
├── urosHandler          # External repository for handling Micro-ROS elements
```

## Dependencies
- ESP-IDF (ESP32 Development Framework)
- Micro-ROS (ROS2 client for microcontrollers)

## Installation & Setup
1. **Clone this repository:**
   ```sh
   git clone https://github.com/your-username/your-repository.git
   cd your-repository
   ```
2. **Initialize submodules:**
   ```sh
   git submodule update --init --recursive
   ```
3. **Install ESP-IDF:** Follow the official [ESP-IDF installation guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html).
4. **Set up Micro-ROS:**
   ```sh
   idf.py menuconfig
   ```
   Configure Micro-ROS settings if required.

## Building and Flashing
1. **Build the project:**
   ```sh
   idf.py build
   ```
2. **Flash the firmware to ESP32:**
   ```sh
   idf.py flash
   ```
3. **Monitor the serial output:**
   ```sh
   idf.py monitor
   ```

## Usage
- The ESP32 subscribes to the `/led_control` topic.
- Sending `std_msgs/msg/Int32` messages with values:
  - `1` → Turns the LED ON
  - `0` → Turns the LED OFF
- Example command to publish a message from ROS 2:
  ```sh
  ros2 topic pub /led_control std_msgs/msg/Int32 '{"data": 1}'
  ```


