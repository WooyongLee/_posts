#include "header.h"

int TemporalMedianBg(Mat frameimg, Mat bgimg, int rows, int cols) {
	int cnt = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (frameimg.data[i * frameimg.cols + j] > bgimg.data[i * bgimg.cols + j]) {//현재 픽셀이 배경 픽셀보다 클 때
				if (bgimg.data[i * bgimg.cols + j] == 255) // 연산할 이미지 배열의 값이 255가 넘을 경우( 최대값 )
					bgimg.data[i * bgimg.cols + j] = 255;
				else
					bgimg.data[i * bgimg.cols + j] += 1;//1씩 증가

			} // 배경 프레임과 비교하여 현재 프레임의 화소 값이 높은 경우, 다음 배경 프레임의 화소를 증가 
			else if (frameimg.data[i * frameimg.cols + j] < bgimg.data[i * bgimg.cols + j]) {//현재 픽셀이 배경 픽셀보다 작을 때
				if (bgimg.data[i * bgimg.cols + j] == 0) // 연산할 이미지 배열의 값이 0보다 작을 경우( 최소값 )
					bgimg.data[i *bgimg.cols + j] = 0;
				else
					bgimg.data[i * bgimg.cols + j] -= 1;//1씩 감소
			} // 배경 프레임과 비교하여 현재 프레임의 화소 값이 낮은 경우, 다음 배경 프레임의 화소를 감소
			else if (frameimg.data[i * frameimg.cols + j] == bgimg.data[i * bgimg.cols + j]) {
				cnt++;
			}
		}
	}
	return cnt;
}

// 배경이 될 프레임을 파일로(.jpg) 저장하는 함수
void backgroundSubtractor(Mat frame, Mat background_frame) {
	// 일단 temporal median을 사용하여
	// 전체 프레임에 움직임이 거의 없다고 판단될 경우에
	// 배경을 파일로 저장하도록 함

	string filename, fullPath;
	// 실제로는 전역변수로 선언해 둔 파일 이름 변수(CString type)가지고
	// 선택한 파일 이름을 따와서 이를 붙이기
	stringstream ss;



	filename = "test.mp4's background";
	ss << filename << ".jpg";
	fullPath = ss.str();
	ss.str("");
	
	imwrite(fullPath, background_frame);
}