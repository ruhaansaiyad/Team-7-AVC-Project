#include <cmath>

class Robot{
	public:
		Robot();
		int start();
		void stop();
		void motors(double vLeft, double vRight);
	private:
		int vMax;
		int vMin;
		ImageProcessing imgProcess;
		void move(int offset, int width);
		int getOffset(int line, int width);
};

/**
 * instantiate variables
 */
Robot::Robot(){
	vMax = 140;
	vMin = 80;
}
 
/**
 * calls set motors and moves robot
 */
void Robot::motors(double vLeft, double vRight){
	setMotors(vLeft, vRight);
}

/**
 * stop the robot
 */
void Robot::stop(){
	setMotors(0, 0);
}

/**
 * moves the left and right motors based on offset
 * only when exit is straight
 */
void Robot::move(int offset, int width){
	double vLeft = (double)(width/2+offset)/width;
	double vRight = (double)(width/2-offset)/width;
	
	// changes the speed based on displacement from center
	int r = offset/(width/2); 
	int v = (vMax - vMin) * cos(M_PI * r);
	
	vLeft *= v;
	vLeft += vMin;
	vRight *= v;
	vRight += vMin;
	
	motors(vLeft, vRight);
}

/**
 * get offset from center
 */
int Robot::getOffset(int line, int width){
	return line - width/2;
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
		// check for exits
		int exit = imgProcess.getExit(cameraView);
		
		// goes left if possible
		switch(exit){
			case 0:
				// left
				motors(10, 10);
				motors(-10, 32);
				break;
			case 1:
				// straight
				{
				// check line
				int line = imgProcess.getLineIndex(cameraView);
				int offset = getOffset(line, cameraView.width);
				move(offset, cameraView.width);
				}
				break;
			default:
				// turns rights
				// searches for line clockwise
				motors(10, 10);
				motors(32, -10);
				break;
		}		
	} 
}

