#pragma once

#include <opencv2\opencv.hpp>
#include <opencv\cv.h>
#include <stdio.h>
#include <string>
#include <Windows.h>

using namespace cv;
using namespace std;

typedef struct _component {
	string fileName; // ����ǰ� �ҷ��� ���׸�Ʈ�� jpg ���� �̸�(1)
	unsigned int timeTag; // �ð�å����(2)
	unsigned int label; // ���̺� ��ȣ(3)
	int frameCount; // ���󿡼� �� ��° ������������ ���� �����(4)
	Vec3b color; // RGB ���� ���� ����(5) (channel of pixel)
	float centerOfX;
	float centerOfY; // ���׸�Ʈ �߽���ǥ(6)
	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom; // ��ü�� �� ��, ��, ��, �� ��ǥ(7)
	int width;
	int height; // ����, ����(8)
	int area; // ��ü ��ȿ ������ �ȼ� ����(9)
	_component() {
		fileName = ""; 
		timeTag = 0; 
		label = 0;
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
		width = 0;
		height = 0;
		area = 0;
	}
}component;