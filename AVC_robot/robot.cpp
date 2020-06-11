
#include "robot.hpp"
#include "ImageProcessing.hpp"


ImageProcessing imgProcess;

float error;
float current_error =0;
float numWhite=0;
double baseSpeed = 40.0;

float kp = 0.25;

// This function takes a picture, gets the center row of the image.
// The divergence from the line is calculated to be used in working out
// the motor speed
void readCamera(){
	takePicture();
	// get the center row of the image. This returns an array of 0s and 1s.
	// 1 means white line
	int* row = imgProcess.getCenterRow(cameraView);
	
	// the error in this case is a value that determines
	// how much the white line has diverged from the center.
	error = 0;
	current_error =0;
	numWhite=0;
	int s = 0; 

	// go through the center row values
	
	for(int i = 0; i < cameraView.width; i++){		
		if(row[i]){   
			s = 1;
			numWhite++;												
		}else{
			s = 0;												
		}
		// calculate the error from the center
		error = (i-(cameraView.width/2))*s;
		// add to the total current error 
		current_error = (current_error + error);		
	} 
	current_error = current_error/numWhite;
}

int main(){
	if (initClientRobot() !=0){
		std::cout<<" Error initializing robot"<<std::endl;
	}
   
    SavePPMFile("i0.ppm",cameraView);
    while(1){
		
		// calculate the error here.
		readCamera();
		
		// proportional input
		float p_signal = current_error*kp;  
		
		//set speeds
		double left = baseSpeed + (p_signal);
		double right = baseSpeed -(p_signal);
		
		setMotors(left,right);
		usleep(1000);
  } //while

} // main
