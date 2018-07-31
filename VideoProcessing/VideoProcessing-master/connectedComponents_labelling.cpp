#include "header.h"

// People Area Detection Parameter
const int MINWIDTH = 80;
const int MINHEIGHT = 80;
const int MAXWIDTH = 250;
const int MAXHEIGHT = 250;

// Caculating for Object Histogram Parameter  
const int channels[] = { 0, 1 };
const int histSize[] = { 64, 64 };
float range[] = { 0, 256 };
const float *ranges[] = { range, range };

void getObjectHistogram(Mat &frame, Rect object_region) {

	// Object region ���� ������׷� ���
	Mat objectROI = frame(object_region);
	calcHist(&objectROI, 1, channels, noArray(), objectHistogram, 2, histSize, ranges, true, false);

	// globalHistogram ����, ���� frame�� ������׷� ���
	calcHist(&frame, 1, channels, noArray(), globalHistogram, 2, histSize, ranges, true, true);

	// Boosting: Divide conditional probabilities in object area by a priori probabilities of colors
	// ���� �𸣰���;;
	for (int y = 0; y < objectHistogram.rows; y++) {
		for (int x = 0; x < objectHistogram.cols; x++) {
			objectHistogram.at<float>(y, x) /= globalHistogram.at<float>(y, x);
		}
	}
	// ����ȭ��Ű�°�
	normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);
}
void backProjection(const Mat &frame, const Mat &histogram, Mat &bp) {
	calcBackProject(&frame, 1, channels, objectHistogram, bp, ranges);
}
vector<component> connectedComponentsWithStats(Mat frame, int rows, int cols) {
	vector<component> result;
	result.clear();
	
	component *componentArray= (component*)malloc(sizeof(component)*50); // componentArray�� ���� �Ҵ�
	
	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(frame, img_labels,
		stats, centroids, 8, CV_32S); // label ���� ��ȯ

	// Component�� ������ ����
	// �����ڽ� �׸���
	int max = -1, idx = 0;
	for (int i = 0; i < numOfLables; i++) {
		int area = stats.at<int>(i, CC_STAT_AREA);

		// ���� ���̺��� �ִ뿵�� ���� (������ ����..)
		if (max < area) {
			max = area;
		}

		// ���� ��ǥ ���ϱ�
		componentArray[i].left = stats.at<int>(i, CC_STAT_LEFT); // Left
		componentArray[i].top = stats.at<int>(i, CC_STAT_TOP); // Top
		componentArray[i].right = stats.at<int>(i, CC_STAT_LEFT) + stats.at<int>(i, CC_STAT_WIDTH); // right
		componentArray[i].bottom = stats.at<int>(i, CC_STAT_TOP) + stats.at<int>(i, CC_STAT_HEIGHT); // Height

		// ���� �ʺ� ����
		componentArray[i].height = stats.at<int>(i, CC_STAT_HEIGHT);
		componentArray[i].width = stats.at<int>(i, CC_STAT_WIDTH);
	}

	return result;
}

void labelSizeFiltering(Mat frame, component comp) {
	if (comp.width > MINWIDTH && comp.height > MINHEIGHT
		&& comp.width < MAXWIDTH && comp.height < MAXHEIGHT) {
		// �簢�� ���ֱ�
		rectangle(frame, Point(comp.left, comp.top), Point(comp.right, comp.bottom), Scalar(0, 255, 0), 1);


	}
}

Rect meanShiftTracking()