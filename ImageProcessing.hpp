class ImageProcessing{
	public:
		int getLineIndex(ImagePPM image);
		int containsBlack(ImagePPM image);
		int getExit(ImagePPM image);
	private:
		int* getCenterRow(ImagePPM image);
		int getColor(ImagePPM image, int row, int col);
		int isWhite(ImagePPM image, int row, int col);
		int isRed(ImagePPM image, int row, int col);
		int isBlack(ImagePPM image, int row, int col);
};

/**
 * returns the edge of the frame
 * -1 - none
 * 0 - left
 * 1 - top
 * 2 - right
 */
int ImageProcessing::getExit(ImagePPM image){	
	// look at left edge, bottom to top
	for(int i = image.height-1; i >= 0; i--){
		if(getColor(image, i, 0)){
			return 0; 
		}
	}
	
	// looks at top edge, left to right
	for(int i = 0; i < image.width; i++){
		if(getColor(image, 0, i)){
			return 1;
		}
	}
	
	// look at right edge, top to bottom
	for(int i = 0; i < image.height; i++){
		if(getColor(image, i, image.height-1)){
			return 2;
		}
	}
	
	return -1;
}

/**
 * returns the center of the line
 */
int ImageProcessing::getLineIndex(ImagePPM image){
	int* row = getCenterRow(image);
	// look at each row and check for 1s
	int total = 0;		// stores the total of all index
	int pixels = 0;		// stores white pixels
	
	// loops the row
	for(int i = 0; i < image.width; i++){
		if(row[i]){
			// white pixel
			total += i;
			pixels++;
		}
	}
	
	// gets average index of the white pixels
	if(pixels == 0){
		return -1;
	}
	return (total/pixels);
}


/**
 * returns a summary of the center row
 */
int* ImageProcessing::getCenterRow(ImagePPM image){
	int* rowData = new int[image.width];	// store row data
	int centerRow = image.height/2;			// index of row
	
	// loop through pixels in the row
	for(int i = 0; i<image.width; i++){
		rowData[i] = getColor(image, centerRow, i);
	}
	return rowData;
}

/**
 * returns a number for colour of the pixel
 * 0-not any of the following colours
 * 1-white
 * 2-black
 */
int ImageProcessing::getColor(ImagePPM image, int row, int col){
	if(isWhite(image, row, col)){
		return 1;
	} else {
		return 0;
	}
}

/**
 * returns 0 or 1 based on if the pixel is white
 */
int ImageProcessing::isWhite(ImagePPM image, int row, int col){
	// check white by looking at the luminocity
	int lumin = get_pixel(image, row, col, 1);
	return (int)(lumin > 240);
}
