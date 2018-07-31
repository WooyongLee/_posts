#pragma once
#include "FrameIndexing.h"
class SizeIndexing :
	public FrameIndexing {
private :
	int standardHeight;
	int standardWidth;
	int standardArea;
	// 따로 구조체로 묶을 수도 있음
public:
	SizeIndexing();
	SizeIndexing(int, int, Mat, Mat);
	~SizeIndexing();
	void executeIndexingFunction(Mat);
	void makeTrackBar(int, int);
	// 가상 멤버 함수 재정의
	bool compareSize(int, int, int);

	void setStdHeight(int);
	void setStdWidth(int);
	void setStdArea(int);
	int getStdHeight();
	int getStdWidth();
	int getStdArea();
	// getter, setter
};

