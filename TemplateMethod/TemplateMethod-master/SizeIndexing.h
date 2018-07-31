#pragma once
#include "FrameIndexing.h"
class SizeIndexing :
	public FrameIndexing {
private :
	int standardHeight;
	int standardWidth;
	int standardArea;
	// ���� ����ü�� ���� ���� ����
public:
	SizeIndexing();
	SizeIndexing(int, int, Mat, Mat);
	~SizeIndexing();
	void executeIndexingFunction(Mat);
	void makeTrackBar(int, int);
	// ���� ��� �Լ� ������
	bool compareSize(int, int, int);

	void setStdHeight(int);
	void setStdWidth(int);
	void setStdArea(int);
	int getStdHeight();
	int getStdWidth();
	int getStdArea();
	// getter, setter
};

