#include "header.h"

Mat TemporalMeanBg(Mat frameimg, Mat bgimg, int rows, int cols, double alpha) {
	// Mat nextBgimg(col, row, CV_8UC3);
	// Mat nextBgimg(row, col, CV_8UC3);
	for (int i = 1; i < rows; i++) {
		for (int j = 1; j < cols; j++) {
			bgimg.data[i * bgimg.cols + j]
				= alpha * frameimg.data[i * bgimg.cols + j] + bgimg.data[i * bgimg.cols + j] * (1 - alpha);
		}
	}
	return bgimg;
}

Mat TemporalMedianBg(Mat frameimg, Mat bgimg, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (frameimg.data[i * frameimg.cols + j] > bgimg.data[i * bgimg.cols + j]) {//���� �ȼ��� ��� �ȼ����� Ŭ ��
				if (bgimg.data[i * bgimg.cols + j] == 255) // ������ �̹��� �迭�� ���� 255�� ���� ���( �ִ밪 )
					bgimg.data[i * bgimg.cols + j] = 255;
				else
					bgimg.data[i * bgimg.cols + j] += 1;//1�� ����

			} // ��� �����Ӱ� ���Ͽ� ���� �������� ȭ�� ���� ���� ���, ���� ��� �������� ȭ�Ҹ� ���� 
			else {//���� �ȼ��� ��� �ȼ����� ���� ��
				if (bgimg.data[i * bgimg.cols + j] == 0) // ������ �̹��� �迭�� ���� 0���� ���� ���( �ּҰ� )
					bgimg.data[i *bgimg.cols + j] = 0;
				else
					bgimg.data[i * bgimg.cols + j] -= 1;//1�� ����
			} // ��� �����Ӱ� ���Ͽ� ���� �������� ȭ�� ���� ���� ���, ���� ��� �������� ȭ�Ҹ� ����
		}
	}
	return bgimg;
}