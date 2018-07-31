#include "header.h"

obj_info dataAllocateAtComponent(Mat stats, obj_info o, int indexOflables) {
	// ���� �����ϱ�
	o.area = stats.at<int>(indexOflables, CC_STAT_AREA);

	// �簢 ���� �����ϱ�
	o.left = stats.at<int>(indexOflables, CC_STAT_LEFT); // Left
	o.top = stats.at<int>(indexOflables, CC_STAT_TOP); // Top
	o.right = stats.at<int>(indexOflables, CC_STAT_LEFT) + stats.at<int>(indexOflables, CC_STAT_WIDTH); // right
	o.bottom = stats.at<int>(indexOflables, CC_STAT_TOP) + stats.at<int>(indexOflables, CC_STAT_HEIGHT); // Height

																										 // ���� �ʺ� �����ϱ�
	o.height = stats.at<int>(indexOflables, CC_STAT_HEIGHT);
	o.width = stats.at<int>(indexOflables, CC_STAT_WIDTH);
	return o;
}

// �簢�� ���ְ� ����� �Լ�
Rect savingRectangle(Mat frame, obj_info o) {
	// �簢�� ȭ�鿡 ���ֱ�
	// rectangle(frame, Point(o.left, o.top), Point(o.right, o.bottom), Scalar(0, 255, 0), 1);
	// �簢�� ����
	Rect objectRegion(o.left, o.top, o.width, o.height);
	return objectRegion;
}

// ���̺� ũ�⸦ ������� �����ϰ� �Ÿ��� �Լ�
int labelSizeFiltering(Mat frame, int width, int height) {
	if (width > MINWIDTH && height > MINHEIGHT
		&& width < MAXWIDTH && height < MAXHEIGHT)
		return 1; // true
	else
		return 0; // false
}

// Component Labelling(opencv�� �Լ� connectedComponentsWithStats�� �̿��Ͽ�)
vector<obj_info> connectedComponentsLabelling(Mat frame) {
	vector<obj_info> result;
	result.clear();
	Rect objectRegion(0, 0, 30, 30); // ���̺� ������ �簢��
	obj_info *obj_array = (obj_info*)calloc(999, sizeof(obj_info)); // componentArray�� ���� �Ҵ�

	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(frame, img_labels,
		stats, centroids, 8, CV_32S); // label ���� ��ȯ

	int index = 0;
	for (int i = 1; i < numOfLables; i++) {
		// height, width�� �̸� ����
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int width = stats.at<int>(i, CC_STAT_WIDTH);

		// �����ڽ� �׸���, ���̺� ũ�⸦ ���͸� �Ͽ�(���ũ�⿡ �ش�� ��ŭ)
		if (labelSizeFiltering(frame, width, height)) {
			// ��ȿ�� ���̺� �ε����� ����
			obj_array[index].label = index;

			// Component�� ������ ����
			obj_array[index] = dataAllocateAtComponent(stats, obj_array[index], i);
			// RectŸ�� ������ ���̺�� ������Ʈ ����
			objectRegion = savingRectangle(frame, obj_array[index]);
			result.push_back(obj_array[index]);

			index++;
		}
	}

	return result;
}
