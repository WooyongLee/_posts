#include "header.h"

const int nThreshold = 50;

Mat morphologicalOperation(Mat img_binary) {
	//morphological opening ���� ������ ����
	erode(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
	dilate(img_binary, img_binary, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

	//morphological closing ������ ���� �޿��
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

	// MOG2�� ����� ���� ������ MOG2 ���� �� ��ü �����κ�
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
		// ������ ����
		// frame_g = morphologicalOperation(frame);
		blur(frame_g, frame_g, Size(9, 9));
		
		// threshold(frame_g, frame_g, nThreshold, 255, CV_THRESH_BINARY);

		pMOG2->apply(frame_g, fgMaskMOG2); // MOG2 ���� ����
		
		// ������ �κ� ���̺� ����
		object_region = connectedComponentsLabelling(fgMaskMOG2);

		// �׸�ġ��

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
