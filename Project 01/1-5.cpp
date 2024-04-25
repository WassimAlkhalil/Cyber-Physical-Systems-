#include <iostream>
#include "ev3dev.h"

/*
This program utilizes the EV3DEV library to control an EV3 robot equipped with ultrasonic sensors and motors.
It tracks an object by rotating the ultrasonic sensor, finding the object with the minimum distance, and moves towards it.
*/

using namespace std;
using namespace ev3dev;

// Initialization of sensors and motors
touch_sensor touch(INPUT_1);
motor leftMotor = motor(OUTPUT_A, motor::motor_large);
motor rightMotor = motor(OUTPUT_B, motor::motor_large);
motor ultrasonicMotor = motor(OUTPUT_D, motor::motor_medium);
ultrasonic_sensor ultrasonic = ultrasonic_sensor(INPUT_4);

// Variables for managing the state and measurements of the robot and ultrasonic sensor 
bool active = false, pressed = false; 
bool wasPressed = false;
bool neg_90 = false, pos_90 = false;
int minimumDistance = 200;
int maximumDistance = 0;
int minimumAngle = 0;
int ultrasonicSpeed = 400;

// Function to measure distance and update the minimum distance and angle
void storeValues() {
    int distance = ultrasonic.distance_centimeters();
    // Update the minimum distance and angle if a new minimum is found
    if (distance < minimumDistance) {
        minimumDistance = distance;
        maximumDistance = distance;
        minimumAngle = ultrasonicMotor.position();
    }
}

// Function to stop the motors of the robot and ultrasonic sensor 
void stopMotor() {
    leftMotor.stop();
    rightMotor.stop();
    ultrasonicMotor.stop();
}

// Moves the robot towards the detected object based on the minimum distance and angle.
void moveRobot(int minimumDistance, int minimumAngle) {
    // Reset the flags for the ultrasonic sensor motor position 
    neg_90 = false;
    pos_90 = false;
 
    /*
    if(ultrasonic.distance_centimeters() <= 25){
        stopMotor();
        return;
    } else 
    */

    // Adjust motor speed based on the angle to the object.
    if (minimumAngle >= 20) {
        leftMotor.set_duty_cycle_sp(40);
        rightMotor.set_duty_cycle_sp(15);
        leftMotor.run_direct();
        rightMotor.run_direct();
    } else if (minimumAngle <= -20) {
        leftMotor.set_duty_cycle_sp(15);
        rightMotor.set_duty_cycle_sp(40);
        leftMotor.run_direct();
        rightMotor.run_direct();
    } else if (ultrasonic.distance_centimeters() >= 100) {
            leftMotor.set_duty_cycle_sp(35);
            rightMotor.set_duty_cycle_sp(35);
            leftMotor.run_direct();
            rightMotor.run_direct();
    } 
    // Move the robot forward if the object is within the desired range. 
    else {
            leftMotor.set_duty_cycle_sp(25);
            rightMotor.set_duty_cycle_sp(25);
            leftMotor.run_direct();
            rightMotor.run_direct();
    }
}

// Function to track the object by rotating the ultrasonic sensor and finding the object with the minimum distance.
void trackObject() {
    // Store the current distance and update the minimum distance and angle values 
    storeValues();

    // Stop the motors if the object is too close to the robot 
    if(ultrasonic.distance_centimeters() <= 25){
        stopMotor();
        return;
    }

    // Rotate the ultrasonic sensor to find the object with the minimum distance 
    ultrasonicMotor.run_to_abs_pos();

    // Store the current position of the ultrasonic sensor motor 
    int currentPosition = ultrasonicMotor.position();

    // Check if the ultrasonic sensor motor has reached the maximum angle positions
    if (currentPosition >= 80) {
        ultrasonicMotor.set_position_sp(-90);
        ultrasonicMotor.run_to_abs_pos();
        pos_90 = true;
        // Reset the minimum distance and angle values for the next iteration 
    } else if (currentPosition <= -80) {
        ultrasonicMotor.set_position_sp(90);
        ultrasonicMotor.run_to_abs_pos();
        neg_90 = true;
    }
    // Continue tracking the object by rotating the ultrasonic sensor
    if (neg_90 == true && pos_90 == true) {
        std::cout<<"Minimum Distance = "<<minimumDistance<<std::endl;
        std::cout<<"Minimum Angle = "<<minimumAngle<<std::endl;
        minimumDistance = 200;
        // Move the robot towards the object based on the minimum distance and angle 
        moveRobot(minimumDistance, minimumAngle);
    }

    // Stop the motors if the object is too far from the robot 
    if (maximumDistance >= 150) {
        stopMotor();
        return;
    }
}

int main() {

    cout << "Press main button to leave ..." << endl;
    // Set the speed of the motors 
    ultrasonicMotor.set_position(0);
    // Set the speed of the ultrasonic sensor motor
    ultrasonicMotor.set_position_sp(-90);
    // Set the speed of the ultrasonic sensor motor
    ultrasonicMotor.set_speed_sp(ultrasonicSpeed);

    // This loop switches between active and standby mode based on the touch sensor input and it will keep running as long as the enter button is not pressed
    do {
        pressed = touch.is_pressed();

        // Toggle active state on rising edge of the touch sensor signal 
        if (pressed && !wasPressed) {
            active = !active;
        }

        wasPressed = pressed;

        // Control the motors based on the active state
        if (active) {
            cout << "Status: Active" << endl;
            // Track the object by rotating the ultrasonic sensor and moving the robot towards the object 
            trackObject();
        } else {
            cout << "Status: Standby" << endl;
            stopMotor();
        }
        
    } while (!button::enter.pressed());

    return 0;
}
