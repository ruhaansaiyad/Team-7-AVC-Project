class ImageProcessing{
	public:
		int* getCenterRow(ImagePPM image);
	private:
		int getColor(ImagePPM image, int row, int col);
		int isWhite(ImagePPM image, int row, int col);
		//int isRed(ImagePPM image, int row, int col);
};

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
