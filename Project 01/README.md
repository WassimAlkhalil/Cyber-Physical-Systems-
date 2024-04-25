# EV3 Robot Control Program

## Description

This repository contains a series of exercises designed to demonstrate control of an EV3 robot using C++ and the `ev3dev` library. The exercises incrementally develop a robot's capabilities, including response to touch inputs, object detection, and tracking moving objects.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
  - [Exercise 1-2: Drive on Command](#exercise-1-2-drive-on-command)
  - [Exercise 1-4: Object Identification](#exercise-1-4-object-identification)
  - [Exercise 1-5: Tracking a Moving Object](#exercise-1-5-tracking-a-moving-object)

## Installation

1. Clone this repository to your local machine or download the source code.
2. Ensure that your EV3 device is running the `ev3dev` operating system. Instructions for setting up `ev3dev` can be found on the [official ev3dev website](https://www.ev3dev.org/docs/getting-started/).

## Usage

### Drive on Command

This exercise demonstrates basic motor control with the EV3 robot. The program reads the state of a touch sensor and controls two main motors. It runs in a non-blocking manner, allowing for other operations to potentially execute simultaneously.

To run this exercise:
- Compile the code using a C++ compiler that supports C++11.
- Deploy and execute on the EV3 robot.

### Object Identification

In this exercise, the robot uses an ultrasonic sensor to detect the distance and direction of the nearest object. The robot does not move; it only reads and displays sensor values.

To run this exercise:
- Compile and deploy the code similarly as described for Exercise 1-2.

### Tracking a Moving Object

This exercise completes the functionality by enabling the robot to track and move towards a detected object, adjusting its speed based on the object's distance and angle.

To run this exercise:
- Ensure that the EV3 robot has space to move and that the environment is safe for navigation.
- Compile, deploy, and execute the code.

