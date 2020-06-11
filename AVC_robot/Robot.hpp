class Robot{
	public:
		Robot();
		int start();
		void stop();
		void motors(double vLeft, double vRight);
	private:
		int vMax;
		int vCurve;
		int curveThreshold; 	// min diff between LR velocity to be a curve
		ImageProcessing imgProcess;
		void move(int offset, int width);
		int getOffset(int line, int width);
};

/**
 * instantiate variables
 */
Robot::Robot(){
	vMax = 130;
	vCurve = 80;
	curveThreshold = 12;
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
 */
void Robot::move(int offset, int width){
	double vLeft = (double)(width/2+offset)/width;
	double vRight = (double)(width/2-offset)/width;
	
	// choose speed multiplier 
	if(offset > curveThreshold){
		// curve
		vLeft *= vCurve;
		vRight *= vCurve;
	} else {
		// straight
		vLeft *= vMax;
		vRight *= vMax;
	}
	
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
		int line = imgProcess.getLineIndex(cameraView);
		int offset = getOffset(line, cameraView.width);
		move(offset, cameraView.width);
	} 
}

