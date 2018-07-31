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
	//morphological opening 작은 점들을 제거
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing 영역의 구멍 메우기
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img_binary, img_result, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	return img_result;
}

bool makeTrackbar(int maxWidth, int maxHeight, int minThreshold) {
	//트랙바에서 사용되는 변수 초기화
	//int LowH = 9;
	//int HighH = 72;

	//int LowS = 0;
	//int HighS = 23;

	//int LowV = 0;
	//int HighV = 255;

	namedWindow("찾을 색범위 설정", WINDOW_NORMAL);

	// 트랙바 생성
	//cvCreateTrackbar("LowH", "찾을 색범위 설정", &LowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "찾을 색범위 설정", &HighH, 179);

	//cvCreateTrackbar("LowS", "찾을 색범위 설정", &LowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "찾을 색범위 설정", &HighS, 255);

	//cvCreateTrackbar("LowV", "찾을 색범위 설정", &LowV, 255); //Value (0 - 255)
	//cvCreateTrackbar("HighV", "찾을 색범위 설정", &HighV, 255);

	cvCreateTrackbar("maxWidth", "찾을 색범위 설정", &maxWidth, 255);
	cvCreateTrackbar("maxHeight", "찾을 색범위 설정", &maxHeight, 255);

	cvCreateTrackbar("minThreshold", "찾을 색범위 설정", &minThreshold, 255);
	return true;
}


int main()
{
	VideoCapture vc("test.mp4");
	Mat background = imread("background.jpg");
	if (!vc.isOpened()) {
		cout << "비디오를 열 수 없습니다." << endl;
		return -1;
	}
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	int maxWidth = 150;
	int maxHeight = 150;

	int minThreshold = 100;

	namedWindow("찾을 색범위 설정", WINDOW_NORMAL);

	// 트랙바 생성
	//cvCreateTrackbar("LowH", "찾을 색범위 설정", &LowH, 179); //Hue (0 - 179)
	//cvCreateTrackbar("HighH", "찾을 색범위 설정", &HighH, 179);

	//cvCreateTrackbar("LowS", "찾을 색범위 설정", &LowS, 255); //Saturation (0 - 255)
	//cvCreateTrackbar("HighS", "찾을 색범위 설정", &HighS, 255);

	//cvCreateTrackbar("LowV", "찾을 색범위 설정", &LowV, 255); //Value (0 - 255)
	//cvCreateTrackbar("HighV", "찾을 색범위 설정", &HighV, 255);

	cvCreateTrackbar("maxWidth", "찾을 색범위 설정", &maxWidth, 255);
	cvCreateTrackbar("maxHeight", "찾을 색범위 설정", &maxHeight, 255);

	cvCreateTrackbar("minThreshold", "찾을 색범위 설정", &minThreshold, 255);

	Rect trackingWindow(0, 0, 30, 30);

	int totalframe = 0;
	while (true)
	{
		totalframe++;

		//웹캠에서 캡처되는 속도 출력
		int fps = vc.get(CAP_PROP_FPS);

		Mat img, img_hsv, img_binary;
		vc >> img;
		if (img.empty()) break;

		//HSV로 변환
		cvtColor(img, img_hsv, COLOR_BGR2HSV);

		img = ExtractFg(img, background, ROWS * 3, COLS);

		//지정한 HSV 범위를 이용하여 영상을 이진화
		// inRange(img_hsv, Scalar(LowH, LowS, LowV), Scalar(HighH, HighS, HighV), img_binary);
		cvtColor(img, img_binary, CV_RGB2GRAY);
		threshold(img_binary, img_binary, minThreshold, 255, THRESH_BINARY);

		img_binary = morphologicalOperation(img_binary);
		blur(img_binary, img_binary, Size(9, 9));

		//라벨링
		Mat img_labels, stats, centroids;
		int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
			stats, centroids, 8, CV_32S);
		printf("%d %d %d\n", totalframe, fps, numOfLables);
		//영역박스 그리기
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

			// 라벨링한 크기가 일정 크기 이상만 연산
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

		imshow("이진화 영상", img_binary);
		imshow("원본 영상", img);

		//ESC키 누르면 프로그램 종료
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
//	////라벨링된 이미지중 특정 라벨을 컬러로 표현해주기  
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
//	//라벨링 된 이미지에 각각 직사각형으로 둘러싸기 
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
//	if (!vc.isOpened()) return; // 불러오기 실패
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
