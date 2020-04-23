#pragma config(Sensor, dgtl7,  ultrasonic,     sensorSONAR_TwoPins_inch)
#pragma config(Motor,  port1, leftMotor,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop)


task main()
{
	while (true) {
		if(SensorValue[ultrasonic] < 5){
			Motor[leftMotor] = (SensorValue[ultrasonic]) / 2;
			Motor[rightMotor] = (SensorValue[ultrasonic]) / 2;
		} else {
			Motor[armMotor] = 10;

		}
	}
}
