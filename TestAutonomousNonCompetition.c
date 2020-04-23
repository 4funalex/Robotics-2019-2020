#pragma config(Sensor, dgtl7,  ultrasonic,     sensorSONAR_TwoPins_inch)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop)

task main(){
	// Declare variables
	int lengthFromObject;
	int currentSpeed;
	// Default starting speed.
	currentSpeed = 108;
	while(true){
		// Sets length to the range from the object
		lengthFromObject = dgtl7;
		// If it's within 54 (4.5 feet) inches we'll start to slow down
		if(lengthFromObject < 54){
			currentSpeed = (lengthFromObject * 2);
			if(lengthFromObject < 7){
				// Drop the arm
				motor[armMotor] = -30;
				// Open the claw
				motor[clawMotor] = -127;
				// Wait four seconds
				wait1Msec(4000);
				// Close the claw on the object
				motor[clawMotor] = 127;
				// Raise the arm
				motor[armMotor] = 30;
				}else{
				// If it's not within 7 inches, procede at the length in inches timed two
				forward(currentSpeed);
			}
		}
	}
}
