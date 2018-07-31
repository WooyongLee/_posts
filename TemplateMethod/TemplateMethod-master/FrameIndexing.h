#pragma once
#include "header.h"
class FrameIndexing
{
private : 
	Mat frame;
	Mat background;
	Mat synthesizedframe;
	component* framedata;
	int detectStateFlag;
public:
	FrameIndexing();
	FrameIndexing(int ,int , Mat, Mat);
	~FrameIndexing();
	void getFrame(int, int );
	virtual void makeTrackBar(int, int);
	virtual void executeIndexingFunction(Mat);
	void frameSynthesis(Mat, Mat);
	void showFrame();

	Mat imgProcessing(Mat);
	component getProcessedRoi(Mat );
	Mat getFrame();
	Mat getSyncFrame();
};

