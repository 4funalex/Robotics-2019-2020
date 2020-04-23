/**
* Basic Autonomous with Switches
*/
#pragma config(Sensor, dgtl12, LimitSwitch, sensorTouch)
#pragma config(Motor, port1, leftMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port6, clawMotor, tmotorVex269, openLoop, reversed)
#pragma config(Motor, port7, armMotor, tmotorVex393, openLoop, reversed)
#pragma config(Motor, port10, rightMotor, tmotorVex393, openLoop)
/* Basic Imports? */
#pragma platform(VEX2)
#pragma competitionControl(Competition)
/* Competition Code (It says to make sure it's included, so...) */
#include "Vex_Competition_Includes.c"

/**
* Set bStopTasksBetweenModes to false if you want to keep user created tasks
* running between Autonomous and Driver controlled modes. You will need to
* manage all user created tasks if set to false.
*/
void pre_auton() {
	bStopTasksBetweenModes = true;
}

task autonomous() {
	while(true){
	}
}

/**
* Basic User Control From https://raw.githubusercontent.com/checrobotics/VEX-Sample-Programs/master/Remote%20Control/Clawbot%20Single%20Joystick%20Control.c
* @return
*/
task usercontrol() {
	while (true) {
		motor[leftMotor] = (vexRT[Ch2] + vexRT[Ch1]) / 2;  // (y + x)/2
		motor[rightMotor] = (vexRT[Ch2] - vexRT[Ch1]) / 2;  // (y - x)/2

		// Raise, lower or do not move arm
		if (vexRT[Btn5U] == 1) {
			motor[armMotor] = 127;        //...raise the arm.
			} else if (vexRT[Btn5D] == 1) {
			motor[armMotor] = -127;    //...lower the arm.
			} else {
			motor[armMotor] = 0;        //...stop the arm.
		}

		// Open, close or no more claw
		if (vexRT[Btn6U] == 1) {
			motor[clawMotor] = 127;        //...close the gripper.
			} else if (vexRT[Btn6D] == 1){
			motor[clawMotor] = -127;        //...open the gripper.
			} else {
			motor[clawMotor] = 0;            //...stop the gripper.
		}
	}
}
