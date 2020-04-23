#pragma config(Sensor, dgtl7,  ultrasonic,     sensorSONAR_inch)
#pragma config(Motor,  port1,           leftMotor,     tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port6,           clawMotor,     tmotorVex269_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           armMotor,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          rightMotor,    tmotorVex393_HBridge, openLoop)

task main(){
	// COUNTER FOR CARRYING OBJECT
	int counter = 0;
	// EQUAL SPEED (FOR LEFT MOTOR)
	float equalSpeed = 30;
	float lengthFromObject = 0;
	// BOOLEANS FOR EVENTS
	bool foundObject = false;
	bool isSearching = true;
	bool turning = false;
	bool goingBack = false;
	// SEARCH? FOR AN OBJECT
	clearTimer(T1);
	while (isSearching) {
		// FIND LENGTH OF THE DISTANCE
		lengthFromObject = SensorValue[dgtl7];
		// OPEN CLAW
		motor[clawMotor] = 50;
		counter++;
	  writeDebugStreamLine("IM COUNTING");
		// PICK UP OBJECT IF BETWEEN 9-4 INCHES
		if(lengthFromObject == 6 || lengthFromObject == 7 || lengthFromObject == 5 || lengthFromObject == 4){
				foundObject = true;
			} else {
				motor[leftMotor] = 25 + equalSpeed;
				motor[rightMotor] = 25;
		}
		if (foundObject) {
			motor[leftMotor] = 25 + equalSpeed;
			motor[rightMotor] = 25;
			motor[armMotor] = -35;
			sleep(1200);
			motor[clawMotor] = -25;
			sleep(2000);
			motor[armMotor] = 40;
			sleep(1000);
			foundObject = false;
			// KILL THE FORWARD MOVEMENT
			isSearching = false;
			turning = true;
		}
	}
	// WHEN THE OBJECT IS PICKED UP
	while (turning) {
		motor[rightMotor] = 80;
		motor[leftMotor] = 0;
	  motor[armMotor] = 0;
	  motor[clawMotor] = 0;
		sleep(2700);
		turning = false;
		goingBack = true;
	}
	// GOING BACK
	while(goingBack){
	  // ASSIGN TIMER TO VARIABLE
		int timeToGoBack = time1[T1];
		clearTimer[T1];
		clearTimer[T2];
		// DOING TIMER WITH BUOLT IN TIME
		while(time1[
		if (counter != 0) {
				motor[leftMotor] = 25 + equalSpeed;
				motor[rightMotor] = 25;
				counter--;
			} else {
		    goingBack = false;
		}
	}
}
