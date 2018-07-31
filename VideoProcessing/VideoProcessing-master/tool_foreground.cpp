#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include <opencv\cv.h>

#include "header.h"

Mat ExtractFg(Mat frameimg, Mat bgimg, int rows, int cols) {
	//   Mat fgimg(col, row, CV_8UC3);
	//   Mat fgimg(row, col, CV_8UC3);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (abs(frameimg.data[i * bgimg.cols + j] - bgimg.data[i * bgimg.cols + j]) < 30)
				frameimg.data[i * bgimg.cols + j] = 0;
		}
	}
	return frameimg;
}