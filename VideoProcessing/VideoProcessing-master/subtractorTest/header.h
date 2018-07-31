#pragma once
#include <opencv\highgui.h>
#include <opencv2\opencv.hpp>
#include <opencv2/video/background_segm.hpp>
#include <opencv2/core/core.hpp> 
#include <opencv\cv.h>
#include <stdio.h>
#include <string>
#include <Windows.h>


// People Area Detection Parameter
const int MINWIDTH = 40;
const int MINHEIGHT = 50;
const int MAXWIDTH = 336;
const int MAXHEIGHT = 325;



using namespace cv;
using namespace std;

typedef struct _obj_info {
	int left;
	int top;
	int right;
	int bottom;
	int width;
	int height;
	int area;
	int label;		
}obj_info;

int TemporalMedianBg(Mat frameimg, Mat bgimg, int rows, int cols);

vector<obj_info> connectedComponentsLabelling(Mat frame);

