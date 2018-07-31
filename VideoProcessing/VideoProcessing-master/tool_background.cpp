#include "header.h"

Mat TemporalMeanBg(Mat frameimg, Mat bgimg, int rows, int cols, double alpha) {
	// Mat nextBgimg(col, row, CV_8UC3);
	// Mat nextBgimg(row, col, CV_8UC3);
	for (int i = 1; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			bgimg.data[i * bgimg.cols + j]
				= alpha * frameimg.data[i * bgimg.cols + j] + bgimg.data[i * bgimg.cols + j] * (1 - alpha);
		}
	}
	return bgimg;
}

Mat TemporalMedianBg(Mat frameimg, Mat bgimg, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (frameimg.data[i * frameimg.cols + j] > bgimg.data[i * bgimg.cols + j]) {//현재 픽셀이 배경 픽셀보다 클 때
				if (bgimg.data[i * bgimg.cols + j] == 255) // 연산할 이미지 배열의 값이 255가 넘을 경우( 최대값 )
					bgimg.data[i * bgimg.cols + j] = 255;
				else
					bgimg.data[i * bgimg.cols + j] += 1;//1씩 증가

			} // 배경 프레임과 비교하여 현재 프레임의 화소 값이 높은 경우, 다음 배경 프레임의 화소를 증가 
			else {//현재 픽셀이 배경 픽셀보다 작을 때
				if (bgimg.data[i * bgimg.cols + j] == 0) // 연산할 이미지 배열의 값이 0보다 작을 경우( 최소값 )
					bgimg.data[i *bgimg.cols + j] = 0;
				else
					bgimg.data[i * bgimg.cols + j] -= 1;//1씩 감소
			} // 배경 프레임과 비교하여 현재 프레임의 화소 값이 낮은 경우, 다음 배경 프레임의 화소를 감소
		}
	}
	return bgimg;
}