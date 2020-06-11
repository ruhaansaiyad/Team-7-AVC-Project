#include "robot.hpp"
#include "ImageProcessing.hpp"

class Robot{
	public:
		Robot();
		int start();
		void stop();
	private:
		ImageProcessing imgProcess;
		float KP;
		double BASE_SPEED;
		float getError(ImagePPM image);
		void move(float error);
};

/**
 * instantiate variables
 */
Robot::Robot(){
	KP = 0.25;
	BASE_SPEED = 40;
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
float Robot::getError(ImagePPM image){
	// get the center row of the image as array of 0s and 1s.
	int* row = imgProcess.getCenterRow(image);
	
	// error is how much the white line has diverged from the center.
	float error = 0;
	float currentError =0;
	float numWhite=0;
	int s = 0; 

	// go through the center row values
	for(int i = 0; i < image.width; i++){		
		if(row[i]){   
			s = 1;
			numWhite++;												
		}else{
			s = 0;												
		}
		// calculate the error from the center
		error = (i-(image.width/2))*s;
		// add to the total current error 
		currentError = (currentError + error);		
	} 
	return currentError/numWhite;
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
 * starts the robot and main loop
 */
int Robot::start(){ 
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
     
    // loops forever and check path
    while(1){
		takePicture();
		float error = getError(cameraView);
		move(error);
	} 
}

/**
 * Main Routine
 */
int main(){
	Robot robot;
	robot.start();
}
