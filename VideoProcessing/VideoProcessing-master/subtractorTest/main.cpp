#include "header.h"

const int nThreshold = 50;

Mat morphologicalOperation(Mat img_binary) {
	//morphological opening 작은 점들을 제거
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing 영역의 구멍 메우기
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	return img_binary;
}


void main() {
	int cnt = 0;

	VideoCapture vc("test.mp4");
	if (!vc.isOpened()) return;
	vc.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	
	int cols = vc.get(CV_CAP_PROP_FRAME_WIDTH);
	int rows = vc.get(CV_CAP_PROP_FRAME_HEIGHT);

	Mat frame(rows, cols, CV_8UC3);
	Mat frame_g(rows, cols, CV_8UC1);
	Mat background(rows, cols, CV_8UC1);

	// MOG2의 결과를 받을 변수와 MOG2 정의 및 객체 생성부분
	Mat fgMaskMOG2;
	// Ptr<BackgroundSubtractor> pMOG;
	Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2();
	// Ptr<BackgroundSubtractorGMG> pGMG;


	// pMOG = new BackgroundSubtractorMOG();
	// pGMG = new BackgroundSubtractorGMG();

	vector<obj_info> object_region;
	while (1) {
		vc >> frame;
		if (frame.empty()) break;

		cvtColor(frame, frame_g, CV_RGB2GRAY);

		cnt = TemporalMedianBg(frame_g, background, rows, cols);
		printf("%d, ", cnt);
		// 노이즈 제거
		// frame_g = morphologicalOperation(frame);
		blur(frame_g, frame_g, Size(9, 9));
		
		// threshold(frame_g, frame_g, nThreshold, 255, CV_THRESH_BINARY);

		pMOG2->apply(frame_g, fgMaskMOG2); // MOG2 적용 연산
		
		// 검출한 부분 레이블링 연산
		object_region = connectedComponentsLabelling(fgMaskMOG2);

		// 네모치기

		for (int i = 0; i < object_region.size(); i++) {
			rectangle(frame, Point(object_region[i].left, object_region[i].top),
				Point(object_region[i].right, object_region[i].bottom), Scalar(0, 255, 0), 1);
		}
		imshow("frame", frame);
		imshow("background", background);
		imshow("fgMaskMOG2", fgMaskMOG2);
		if (waitKey(10) == 27) break; // ESC
	}
	destroyAllWindows();
}
