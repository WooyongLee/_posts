#pragma once

#include <opencv2\opencv.hpp>
#include <opencv\cv.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

using namespace cv;
using namespace std;

typedef struct _component {
	string fileName; // 저장되고 불러올 세그먼트의 jpg 파일 이름(1)
	unsigned int timeTag; // 시간책갈피(2)
	unsigned int label; // 레이블 번호(3)
	int frameCount; // 영상에서 몇 번째 프레임인지에 대한 계수기(4)
	Vec3b color; // RGB 색상 저장 변수(5) (channel of pixel)
	float centerOfX;
	float centerOfY; // 세그먼트 중심좌표(6)
	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom; // 객체의 최 상, 하, 좌, 우 좌표(7)
	int width;
	int height; // 넓이, 높이(8)
	int area; // 전체 유효 넓이의 픽셀 개수(9)
	_component() {
		fileName = ""; 
		timeTag = 0; 
		label = 0;
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
		width = 0;
		height = 0;
		area = 0;
	}
}component;