#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "header.h"

using namespace cv;
using namespace std;

Mat objectHistogram;
Mat globalHistogram;

void getObjectHistogram(Mat &frame, Rect object_region) {
	const int channels[] = { 0, 1 };
	const int histSize[] = { 64, 64 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };

	// Histogram in object region
	Mat objectROI = frame(object_region);
	calcHist(&objectROI, 1, channels, noArray(), objectHistogram, 2, histSize, ranges, true, false);

	// A priori color distribution with cumulative histogram
	calcHist(&frame, 1, channels, noArray(), globalHistogram, 2, histSize, ranges, true, true);

	// Boosting: Divide conditional probabilities in object area by a priori probabilities of colors
	for (int y = 0; y < objectHistogram.rows; y++) {
		for (int x = 0; x < objectHistogram.cols; x++) {
			objectHistogram.at<float>(y, x) /= globalHistogram.at<float>(y, x);
		}
	}
	normalize(objectHistogram, objectHistogram, 0, 255, NORM_MINMAX);
}
void backProjection(const Mat &frame, const Mat &histogram, Mat &bp) {
	const int channels[] = { 0, 1 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };
	calcBackProject(&frame, 1, channels, objectHistogram, bp, ranges);
}

Mat morphologicalOperation(Mat img_binary) {
	Mat img_result;
	//morphological opening ���� ������ ����
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing ������ ���� �޿��
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img_binary, img_result, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	return img_result;
}

bool makeTrackbar(int maxWidth, int maxHeight, int minThreshold) {
	//Ʈ���ٿ��� ���Ǵ� ���� �ʱ�ȭ
	//int LowH = 9;
	//int HighH = 72;

	//int LowS = 0;
	//int HighS = 23;

	//int LowV = 0;
	//int HighV = 255;

	namedWindow("ã�� ������ ����", WINDOW_NORMAL);

	// Ʈ���� ����
	//cvCreateTrackbar("LowH", "ã�� ������ ����", &LowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "ã�� ������ ����", &HighH, 179);

	//cvCreateTrackbar("LowS", "ã�� ������ ����", &LowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "ã�� ������ ����", &HighS, 255);

	//cvCreateTrackbar("LowV", "ã�� ������ ����", &LowV, 255); //Value (0 - 255)
	//cvCreateTrackbar("HighV", "ã�� ������ ����", &HighV, 255);

	cvCreateTrackbar("maxWidth", "ã�� ������ ����", &maxWidth, 255);
	cvCreateTrackbar("maxHeight", "ã�� ������ ����", &maxHeight, 255);

	cvCreateTrackbar("minThreshold", "ã�� ������ ����", &minThreshold, 255);
	return true;
}


int main()
{
	VideoCapture vc("test.mp4");
	Mat background = imread("background.jpg");
	if (!vc.isOpened()) {
		cout << "������ �� �� �����ϴ�." << endl;
		return -1;
	}
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	int maxWidth = 150;
	int maxHeight = 150;

	int minThreshold = 100;

	namedWindow("ã�� ������ ����", WINDOW_NORMAL);

	// Ʈ���� ����
	//cvCreateTrackbar("LowH", "ã�� ������ ����", &LowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "ã�� ������ ����", &HighH, 179);

	//cvCreateTrackbar("LowS", "ã�� ������ ����", &LowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "ã�� ������ ����", &HighS, 255);

	//cvCreateTrackbar("LowV", "ã�� ������ ����", &LowV, 255); //Value (0 - 255)
	//cvCreateTrackbar("HighV", "ã�� ������ ����", &HighV, 255);

	cvCreateTrackbar("maxWidth", "ã�� ������ ����", &maxWidth, 255);
	cvCreateTrackbar("maxHeight", "ã�� ������ ����", &maxHeight, 255);

	cvCreateTrackbar("minThreshold", "ã�� ������ ����", &minThreshold, 255);

	Rect trackingWindow(0, 0, 30, 30);

	int totalframe = 0;
	while (true)
	{
		totalframe++;

		//��ķ���� ĸó�Ǵ� �ӵ� ���
		int fps = vc.get(CAP_PROP_FPS);

		Mat img, img_hsv, img_binary;
		vc >> img;
		if (img.empty()) break;

		//HSV�� ��ȯ
		cvtColor(img, img_hsv, COLOR_BGR2HSV);

		img = ExtractFg(img, background, ROWS * 3, COLS);

		//������ HSV ������ �̿��Ͽ� ������ ����ȭ
		// inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
		cvtColor(img, img_binary, CV_RGB2GRAY);
		threshold(img_binary, img_binary, minThreshold, 255, THRESH_BINARY);

		img_binary = morphologicalOperation(img_binary);
		blur(img_binary, img_binary, Size(9, 9));

		//�󺧸�
		Mat img_labels, stats, centroids;
		int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
			stats, centroids, 8, CV_32S);
		printf("%d %d %d\n", totalframe, fps, numOfLables);
		//�����ڽ� �׸���
		int max = -1, idx = 0;
		for (int i = 1; i < numOfLables; i++) {
			int area = stats.at<int>(i, CC_STAT_AREA);
			if (max < area) {
				max = area;
				idx = i;
			}

			int left = stats.at<int>(i, CC_STAT_LEFT);
			int top = stats.at<int>(i, CC_STAT_TOP);
			int width = stats.at<int>(i, CC_STAT_WIDTH);
			int height = stats.at<int>(i, CC_STAT_HEIGHT);

			// �󺧸��� ũ�Ⱑ ���� ũ�� �̻� ����
			if (width > 40 && height > 40
				&& width < maxWidth && height < maxHeight) {
				rectangle(img, Point(left, top), Point(left + width, top + height),
					Scalar(0, 255, 0), 1);

				Rect object_region(left, top, width, height);

				getObjectHistogram(img_hsv, object_region);
				trackingWindow = object_region;

				Mat bp;
				backProjection(img_hsv, objectHistogram, bp);

				// Tracking
				meanShift(bp, trackingWindow, TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 100, 0.01));
				rectangle(img, trackingWindow, CV_RGB(0, 0, 255), 2);

			}
		}

		imshow("����ȭ ����", img_binary);
		imshow("���� ����", img);

		//ESCŰ ������ ���α׷� ����
		if (waitKey(1) == 27)
			break;
	}

	return 0;
}

//int main() {
//	Mat img_gray, img_color, img_binary;
//
//	img_gray = imread("img2.jpg", IMREAD_GRAYSCALE);
//
//	resize(img_gray, img_gray, Size(600, 800));
//	threshold(img_gray, img_binary, 127, 255, THRESH_BINARY);
//	cvtColor(img_gray, img_color, COLOR_GRAY2BGR);
//
//
//	Mat img_labels, stats, centroids;
//	int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
//		stats, centroids, 8, CV_32S);
//
//
//	////�󺧸��� �̹����� Ư�� ���� �÷��� ǥ�����ֱ�  
//	//for (int y = 0; y<img_labels.rows; ++y) {
//	//	int *label = img_labels.ptr<int>(y);
//	//	Vec3b* pixel = img_color.ptr<Vec3b>(y);
//	//	for (int x = 0; x < img_labels.cols; ++x) {
//	//		if (label[x] == 3) {
//	//			pixel[x][2] = 0;
//	//			pixel[x][1] = 255;
//	//			pixel[x][0] = 0;
//	//		}
//	//	}
//	//}
//
//	//�󺧸� �� �̹����� ���� ���簢������ �ѷ��α� 
//
//
//	static int label_count = 0;
//	for (int j = 1; j < numOfLables; j++) {
//		int area = stats.at<int>(j, CC_STAT_AREA);
//		int left = stats.at<int>(j, CC_STAT_LEFT);
//		int top = stats.at<int>(j, CC_STAT_TOP);
//		int width = stats.at<int>(j, CC_STAT_WIDTH);
//		int height = stats.at<int>(j, CC_STAT_HEIGHT);
//
//		if ((width > 30) && (height > 30)) {
//			label_count++;
//			rectangle(img_color, Point(left, top), Point(left + width, top + height),
//				Scalar(0, 0, 255), 1);
//
//			putText(img_color, to_string(label_count), Point(left + 20, top + 20),
//				FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 0, 0), 2);
//		}
//	}
//
//	VideoCapture vc("test.mp4");
//	if (!vc.isOpened()) return; // �ҷ����� ����
//
//	Mat img;
//	while (1) {
//		vc >> img;
//		if (img.empty()) break;
//		imshow("video", img);
//		if (waitKey(10) == 27) break; //ESC
//	}
//	destroyAllWindows();
//
//
//	waitKey(0);
//}
