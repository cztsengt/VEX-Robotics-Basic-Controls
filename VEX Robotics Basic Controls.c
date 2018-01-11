#pragma config(Motor,  port2,           right,         tmotorVex393_MC29, openLoop, reversed, driveRight)
#pragma config(Motor,  port3,           left,          tmotorVex393_MC29, openLoop, driveLeft)
#pragma config(Motor,  port4,           claw,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           arm1,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          arm2,          tmotorVex393_HBridge, openLoop, reversed)

/*
Names: Caleb Tseng-Tham
Date: April 24, 2017
This program codes for the movement and actions able to be done by the VEX robot.
*/

float velocity = 50.0;
float maxVelocity = 127.0;

void armFunction(){
	int armDefault = 20;
	float armThrottle = 0.5;

	motor[arm1] = motor[arm2] = armDefault + vexRT[Ch2]*armThrottle;
}

void clawFunction() {
	int clawSpeed = 25;

	if (vexRT[Btn6D])
		motor[claw] = vexRT[Btn6D]*clawSpeed+5;
	else
		motor[claw] = clawSpeed*-1;
}

int clawOverride(){
	if (vexRT[Btn5D]){
		motor[claw] = -50;
		return 0;
	}
	return 1;
}

int maxSpeed(){
	if (vexRT[Btn7U]){
		motor[right] = motor[left] = maxVelocity;
		return 0;
	}
	if (vexRT[Btn7D]){
		motor[right] = motor[left] = maxVelocity*-1;
		return 0;
	}
	return 1;
}

int maxTurn(){
	if (vexRT[Btn7R]){
		motor[left] = maxVelocity;
		motor[right] = maxVelocity*-1;
		return 0;
	}
	if (vexRT[Btn7L]){
		motor[right] = maxVelocity;
		motor[left] = maxVelocity*-1;
		return 0;
	}
	return 1;
}

void jMovement(){
	if (vexRT[Ch3] < -50) {
		motor[right] = (vexRT[Ch3] + vexRT[Ch4])*(velocity/maxVelocity);
		motor[left] = (vexRT[Ch3] - vexRT[Ch4])*(velocity/maxVelocity);
	}
	else {
		motor[left] = (vexRT[Ch3] + vexRT[Ch4])*(velocity/maxVelocity);
		motor[right] = (vexRT[Ch3] - vexRT[Ch4])*(velocity/maxVelocity);
	}
}

task main() {
	while(42069) {
		if (maxSpeed() && maxTurn()){
			jMovement();
		}
		armFunction();
		if (clawOverride()){
			clawFunction();
		}
	}
}
