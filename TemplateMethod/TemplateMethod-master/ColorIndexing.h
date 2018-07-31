#pragma once
#include "FrameIndexing.h"
class ColorIndexing :
	public FrameIndexing {
private :
	Vec3b standardColor;
	int flagOfColor;
public:
	ColorIndexing();
	ColorIndexing(int, int, Mat, Mat);
	~ColorIndexing();
	void executeIndexingFunction(Mat );
	void makeTrackBar(int, int);
	// ���� ��� �Լ� ������
	bool compareColor(Vec3b);

	bool compareFacePart();
	void detectClothes();
	int getHistogram();
	int getSpecifiedColor(Vec3b);

	void setStdColor(Vec3b);
	unsigned int getR_color();
	unsigned int getG_color();
	unsigned int getB_color();
	// getter, setter
};

