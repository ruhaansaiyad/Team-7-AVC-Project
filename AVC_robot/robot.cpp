#include "robot.hpp"
#include "ImgProcess.hpp"
#include <cmath>
 
/**
 * The robot object that moves the robot on screen 
 * by following a line or the wall
 */
class Robot{
	public:
		Robot(int wallDist, int width);
		static const float KP;
		static const double BASE_SPEED;
		
		int start();
		void stop();
	private:
		int wallDist;
		int width;
		
		float getError(ImagePPM image, int target, int color);
		void move(float error);
		void adjust(int exit);
		int followLine(int exit, ImagePPM image);
		int followWall(ImagePPM image, int targetDist);
		void turnWallCorner(int angle);
};

/**
 * instantiate variables
 */
const float  Robot::KP = 0.25;
const double Robot::BASE_SPEED = 40;

Robot::Robot(int wallDist, int width){
	this->wallDist = wallDist;
	this->width = width;
}

/**
 * stop the robot
 */
void Robot::stop(){
	setMotors(0, 0);
}

/**
 * PID algorithm
 * This function takes a picture, gets the center row of the image.
 * The divergence from the line is calculated to be used in working out
 * the motor speed
 */
float Robot::getError(ImagePPM image, int target, int color){
	// get the center row of the image as array of 0s and 1s.
	int* row = ImgProcess::getCenterRow(image);
	
	// error is how far from the target the robot is
	float error = 0;
	float currentError =0;
	float num=0;
	int s = 0; 

	// go through the center row values
	for(int i = 0; i < image.width; i++){		
		if(row[i] == color){   
			s = 1;
			num++;												
		}else{
			s = 0;												
		}
		// calculate the error from the center
		error = (i-target)*s;
		// add to the total current error 
		currentError += error;		
	} 
	return currentError/num;
}

/**
 * Calculates and moves robot
 */
void Robot::move(float error){
	// proportional input
	float p_signal = error*KP;  
		
	//set speeds
	double left = BASE_SPEED + (p_signal);
	double right = BASE_SPEED -(p_signal);
		
	setMotors(left,right);
}

/**
 * adjust to corners
 */
void Robot::adjust(int exit){
	// respond to different exits and make adjustments
	switch(exit){
		case 0:
			// left
			setMotors(0,BASE_SPEED);
			break;
		case 1:
			// middle, do nothing and leave for PID
			break;
		case 2:
			// right
			setMotors(BASE_SPEED,0);
			break;
		default:
			// deadend, turn right
			setMotors(50,-30);
			break;
	}
}

/**
 * does procedures for lines and returns error for forward movement
 */
int Robot::followLine(int exit, ImagePPM image){
	// adjust and follow the line
	adjust(exit);
	
	// get error 
	int error = getError(image, image.width/2, 1);
	// check for error
	if(error > image.width || error < -image.width){
		// moves the maximum to left or right
		return cameraView.width/2;
	}	
	return error;
}

/**
 * maintains a constant distance between the robot and the left wall
 * returns the error
 */
int Robot::followWall(ImagePPM image, int targetDist){
	float error;
	
	// there is a wall in front
	if(ImgProcess::hasObstacle(image)){
		// has a wall very close to it
		// reverse and turn
		setMotors(-40, -40);
		setMotors(-30, -70);
		error = image.width/2;
				  
	} else {  
		// get red wall error
		error = getError(image, targetDist, 2);
				
		// has a left wall shorter than half the height 
		// move forward and turn to the left so it pasts the wall
		if(std::isnan(error)){
			turnWallCorner(ImgProcess::getWallCurve(image));
			error = 0;
		}
	}
	
	return error;
}

/**
 * turn the robot around the corner to the left
 */
void Robot::turnWallCorner(int angle){
	int forward = 20;
			
	// moves forward to a position where you can turn 
	for(int i=0; i<forward; i++){
		setMotors(40, 40);
	} 
	
	// turn the angle of the wall
	// at this point it is only 90 and 180
	int reps = (angle/8) + 1;
	float m = 1+(float)angle/540;
	for(int i=0; i<reps; i++){
		setMotors(wallDist*m, wallDist*m+width);
	}
	 
	//sleep(5);
}

  
/** 
 * starts the robot and main loop
 */
int Robot::start(){ 
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
     
    // loops forever and check path
    while(1){
		takePicture();
		// finds exit
		int exit = ImgProcess::getExit(cameraView);
		float error;
		
		if(exit != -1){
			// follows a left, forward or right facing line
			error = followLine(exit, cameraView);
			
		} else if(ImgProcess::hasWall(cameraView)){
			// no line exit but has walls to follow
			error = followWall(cameraView, wallDist);
			
		} else { 
			// no line and no walls
			// turn right
			adjust(-1);
			error = 0; 
		} 
		
		move(error);
	} 
}

/**
 * Main Routine
 */
int main(){
	Robot robot(24, 30);
	robot.start();
}
