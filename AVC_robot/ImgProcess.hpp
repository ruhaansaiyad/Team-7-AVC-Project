/**
 * static class that processes the pictures from the robot
 */
class ImgProcess{
	public:
		static int getWallCurve(ImagePPM image);
		static int* getCenterRow(ImagePPM image);
		static int getExit(ImagePPM image);
		static int hasWall(ImagePPM image);
		static int hasObstacle(ImagePPM image);
	private:
		static int getColor(ImagePPM image, int row, int col);
		static int isWhite(ImagePPM image, int row, int col);
		static int isRed(ImagePPM image, int row, int col);
};

/**
 * returns the edge of the frame
 * -1 - none
 * 0 - left
 * 1 - top
 * 2 - right
 */
int ImgProcess::getExit(ImagePPM image){	
	// look at left edge, bottom to top
	for(int i = image.height-1; i >= 0; i--){
		if(getColor(image, i, 0) == 1){
			return 0; 
		}
	}
	
	// looks at top edge, left to right
	for(int i = 0; i < image.width; i++){
		if(getColor(image, 0, i) == 1){
			return 1;
		}
	}
	
	// look at right edge, top to bottom
	for(int i = 0; i < image.height; i++){
		if(getColor(image, i, image.height-1) == 1){
			return 2;
		}
	}
	
	return -1;
}

/**
 * returns a summary of the center row
 */
int* ImgProcess::getCenterRow(ImagePPM image){
	int* rowData = new int[image.width];	// store row data
	int centerRow = image.height/2;			// index of row
	
	// loop through pixels in the row
	for(int i = 0; i<image.width; i++){
		rowData[i] = getColor(image, centerRow, i);
	}
	return rowData;
}

/**
 * returns 01 based on if there is a wall on the robots left
 */
int ImgProcess::hasWall(ImagePPM image){
	// looks at left edge and bottom left pixels for red pixels
	// look at left edge
	for(int i = 0; i < image.height; i++){
		if(getColor(image, i, 0) == 2){
			return 1; 
		}
	}
	// looks at bottom left
	for(int i = 0; i < image.width/2; i++){
		if(getColor(image, image.height-1, i) == 2){
			return 1; 
		}
	}
	
	return 0;
}

/**
 * returns 01 based on if there is a wall in front
 */
int ImgProcess::hasObstacle(ImagePPM image){
	// bottom column
	for(int i = image.height*3/4; i < image.height; i++){
		if(getColor(image, i, image.width/2) == 2){
			return 1;
		}
	}
	return 0;
}

/**
 * returns the angle at which the robot should turn 
 * to touch the next left wall after the left wall ends
 */
int ImgProcess::getWallCurve(ImagePPM image){
	// checks if there is a horizontal wall attached to the left wall
	for(int i = 0; i < image.height; i++){
		if(getColor(image, i, 0) == 2){
			return 90;
		}
	}
	return 180;
}

/**
 * returns a number for colour of the pixel
 * 0-not any of the following colours
 * 1-white
 * 2-red
 */
int ImgProcess::getColor(ImagePPM image, int row, int col){
	if(isWhite(image, row, col)){
		return 1;
	} else if(isRed(image, row, col)){
		return 2;
	} else {
		return 0;
	}
}

/**
 * returns 0 or 1 based on if the pixel is white
 */
int ImgProcess::isWhite(ImagePPM image, int row, int col){
	// check white by looking at the luminocity
	int lumin = get_pixel(image, row, col, 3);
	return (int)(lumin > 240);
}

/**
 * returns 0 or 1 based on if the pixel is red
 */
int ImgProcess::isRed(ImagePPM image, int row, int col){
	// check white by looking at the luminocity
	int r = get_pixel(image, row, col, 0);
	int g = get_pixel(image, row, col, 1);
	int b = get_pixel(image, row, col, 2);
	return (r/2 > b) && (r/2 > g) && (r > 10);
}
