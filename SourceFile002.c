#pragma config(Sensor, in1, clawPot, sensorPotentiometer)
#pragma config(Sensor, in2, shaftPot, sensorPotentiometer)
#pragma config(Sensor, in3, frontSwitch, sensorLimitSwitch)
#pragma config(Sensor, dgtl7, ultraSonic, sensorSONAR_inch)
#pragma config(Motor, port1, leftMotor, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor, port6, clawMotor, tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor, port7, armMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port10, rightMotor, tmotorVex393_HBridge, openLoop)
/**
 * We'll define every static variable here first.
 */

/* Define the max length the bot can be from the object. */
const long maxLength = 7;
/* This variable will be used by the bot to determine the current mode. */
int currentMode = 0;
/* Here we'll define all of the bot functions. Main will be last, so it can reference all of the previous functions first */

/**
 * Roomba Like method, this will be called whenever too close to an object(wall) or limit switch is hit
 *
 * Reverse for 5 seconds at 45 speed
 * Point rotate 90 degrees to the right
 */
void reverseAndRotate() {
    motor[leftMotor] = -45;
    motor[rightMotor] = -45;
    wait1MSec(5000);
    turnRight(1, degrees, 90);
}

/**
 * This pickup object code will only run if there is an object within range of the bot.
 *
 * Should not be called unless user operated or the bot senses the object.
 */
void pickup_object() {
    /**
     * Confirm that the bot is in distance of the bot
     *
     * The sensor value function refers to the RobotC function to get Sensor Values.
     * The variable ultraSonic rangefinder.
     */
    if (SensorValue[ultraSonic] < maxLength) {
        motor[leftMotor] = 0;
        motor[rightMotor] = 0;
        motor[clawMotor] = 10;
    }
}

/**
 * This function will create the speed for the robot. It'll check the range from the bot so it can calculate speed.
 *
 * @return the new speed for the robot.
 */
int current_speed() {
    int distanceFromObject = SensorValue[ultraSonic];
    /**
     * If the distance is greater than 100 inches, we'll scale down the speed to 90% of the distance.
     * e.g 120 inches, 108 speed.
     *
     * If the distance is greater than 75 but less than 100, we'll go at the same speed as the distance.
     */
    if (distanceFromObject > 100) {
        return (distanceFromObject * 0.9);
    } else if (distanceFromObject > 75) {
        return (distanceFromObject * 1.0);
    } else if (distanceFromObject > 50) {
        return (distanceFromObject * 1.1);
    } else if (distanceFromObject > 25) {
        return (distanceFromObject * 1.2);
    } else if (distanceFromObject > maxLength) {
        return distanceFromObject;
    } else if (distanceFromObject < maxLength) {
        /**
         * If the bot is within the range of the max, we'll stop the motors, the other code will take control for
         * the new speed then.
         */
        return 0;
    }
}

/**
 * The Check_Kill function will always run first, that way if there is an object that was too close, or did not
 * get properly sensed by the Ultrasonic Proximity Sesnor, we'll be able to still function and stop the program.
 *
 * If there is an object in front of it we'll run the roomba like code.
 */
void check_kill() {
    if (!(SensorValue[frontSwitch] == 0)) {
        currentMode = 0;
    }
}

void move_sensor() {
    motor[sensorMotor] = 5;
    wait1Msec(1000);
    motor[sensorMotor] = -5;
    wait1Msec(5000);
}
/**
 * This method will loop through every check needed.
 */
void checks() {
    /* Make sure the kill switch isn't activated */
    check_kill();
    /* Check if the robot is too close to the object */
    if(SensorValue[ultraSonic] > maxLength){
        currentMode = 1;
    }
}

void modes() {
    switch (currentMode) {
        /**
         * Mode 0 equals stop all of the motors, usually called at start and if the kill switch is activated.
         */
        case 0:
            motor[armMotor] = 0;
            motor[clawMotor] = 0;
            motor[leftMotor] = 0;
            motor[rightMotor] = 0;
            /**
             * Mode 1 equals standard driving forward
             */
        case 1:
            motor[leftMotor] = current_speed();
            motor[rightMotor] = current_speed();
            /**
             * Mode 2 equals reversing and turning out.
             */
        case 2:
            reverseAndRotate();
            /**
             * Mode 3 equals activating the claw bot to pickup an object
             */
        case 3:
            pickup_object();
    }
}

/**
 * Robot Start will consistently call the methods inside of it.
 *
 * Modes will determine what the bot should be doing.
 * Checks will run all of the necessary checks for the bot.
 */
void robot_start() {
    while (1) {
        checks();
        modes();
    }
}

task main() {
    /* Start the bot, wait for four seconds and then begin looping the bot. */
    wait1Msec(4000);
    /* Robot Start is the actual loop. */
    robot_start();
    /* Make sure the current mode is 0, so the bot doesn't do a random mode. */
    currentMode = 0;
}