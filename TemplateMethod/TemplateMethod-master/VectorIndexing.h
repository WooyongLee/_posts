#pragma once
#include "FrameIndexing.h"
class VectorIndexing : 
	public FrameIndexing {
private : 
	double standardMinAngle;
	double standardMaxAngle;
public:
	VectorIndexing();
	VectorIndexing(int, int, Mat, Mat);
	~VectorIndexing();
	void executeIndexingFunction(Mat);
	void makeTrackBar(int, int);
	// ���� ��� �Լ� ������
	bool comparePrevData();

	int calcVelocity();
	bool stopObjectDetect();
	component getPrevData();

	double getStdMinAngle();
	double getStdMaxAngle();
	void setStdMinAngle(double);
	void setStdMaxAngle(double);
	// getter, setter
};

