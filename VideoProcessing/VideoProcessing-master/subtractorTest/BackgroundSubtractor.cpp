#include "header.h"

int TemporalMedianBg(Mat frameimg, Mat bgimg, int rows, int cols) {
	int cnt = 0;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (frameimg.data[i * frameimg.cols + j] > bgimg.data[i * bgimg.cols + j]) {//���� �ȼ��� ��� �ȼ����� Ŭ ��
				if (bgimg.data[i * bgimg.cols + j] == 255) // ������ �̹��� �迭�� ���� 255�� ���� ���( �ִ밪 )
					bgimg.data[i * bgimg.cols + j] = 255;
				else
					bgimg.data[i * bgimg.cols + j] += 1;//1�� ����

			} // ��� �����Ӱ� ���Ͽ� ���� �������� ȭ�� ���� ���� ���, ���� ��� �������� ȭ�Ҹ� ���� 
			else if (frameimg.data[i * frameimg.cols + j] < bgimg.data[i * bgimg.cols + j]) {//���� �ȼ��� ��� �ȼ����� ���� ��
				if (bgimg.data[i * bgimg.cols + j] == 0) // ������ �̹��� �迭�� ���� 0���� ���� ���( �ּҰ� )
					bgimg.data[i *bgimg.cols + j] = 0;
				else
					bgimg.data[i * bgimg.cols + j] -= 1;//1�� ����
			} // ��� �����Ӱ� ���Ͽ� ���� �������� ȭ�� ���� ���� ���, ���� ��� �������� ȭ�Ҹ� ����
			else if (frameimg.data[i * frameimg.cols + j] == bgimg.data[i * bgimg.cols + j]) {
				cnt++;
			}
		}
	}
	return cnt;
}

// ����� �� �������� ���Ϸ�(.jpg) �����ϴ� �Լ�
void backgroundSubtractor(Mat frame, Mat background_frame) {
	// �ϴ� temporal median�� ����Ͽ�
	// ��ü �����ӿ� �������� ���� ���ٰ� �Ǵܵ� ��쿡
	// ����� ���Ϸ� �����ϵ��� ��

	string filename, fullPath;
	// �����δ� ���������� ������ �� ���� �̸� ����(CString type)������
	// ������ ���� �̸��� ���ͼ� �̸� ���̱�
	stringstream ss;



	filename = "test.mp4's background";
	ss << filename << ".jpg";
	fullPath = ss.str();
	ss.str("");
	
	imwrite(fullPath, background_frame);
}