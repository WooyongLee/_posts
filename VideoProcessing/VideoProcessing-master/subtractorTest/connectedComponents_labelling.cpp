#include "header.h"

obj_info dataAllocateAtComponent(Mat stats, obj_info o, int indexOflables) {
	// 영역 저장하기
	o.area = stats.at<int>(indexOflables, CC_STAT_AREA);

	// 사각 끝점 저장하기
	o.left = stats.at<int>(indexOflables, CC_STAT_LEFT); // Left
	o.top = stats.at<int>(indexOflables, CC_STAT_TOP); // Top
	o.right = stats.at<int>(indexOflables, CC_STAT_LEFT) + stats.at<int>(indexOflables, CC_STAT_WIDTH); // right
	o.bottom = stats.at<int>(indexOflables, CC_STAT_TOP) + stats.at<int>(indexOflables, CC_STAT_HEIGHT); // Height

																										 // 높이 너비 저장하기
	o.height = stats.at<int>(indexOflables, CC_STAT_HEIGHT);
	o.width = stats.at<int>(indexOflables, CC_STAT_WIDTH);
	return o;
}

// 사각형 쳐주고 만드는 함수
Rect savingRectangle(Mat frame, obj_info o) {
	// 사각형 화면에 쳐주기
	// rectangle(frame, Point(o.left, o.top), Point(o.right, o.bottom), Scalar(0, 255, 0), 1);
	// 사각형 저장
	Rect objectRegion(o.left, o.top, o.width, o.height);
	return objectRegion;
}

// 레이블 크기를 사람정도 들어갈만하게 거르는 함수
int labelSizeFiltering(Mat frame, int width, int height) {
	if (width > MINWIDTH && height > MINHEIGHT
		&& width < MAXWIDTH && height < MAXHEIGHT)
		return 1; // true
	else
		return 0; // false
}

// Component Labelling(opencv내 함수 connectedComponentsWithStats를 이용하여)
vector<obj_info> connectedComponentsLabelling(Mat frame) {
	vector<obj_info> result;
	result.clear();
	Rect objectRegion(0, 0, 30, 30); // 레이블 저장할 사각형
	obj_info *obj_array = (obj_info*)calloc(999, sizeof(obj_info)); // componentArray에 공간 할당

	Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(frame, img_labels,
		stats, centroids, 8, CV_32S); // label 갯수 반환

	int index = 0;
	for (int i = 1; i < numOfLables; i++) {
		// height, width를 미리 지정
		int height = stats.at<int>(i, CC_STAT_HEIGHT);
		int width = stats.at<int>(i, CC_STAT_WIDTH);

		// 영역박스 그리기, 레이블 크기를 필터링 하여(사람크기에 해당될 만큼)
		if (labelSizeFiltering(frame, width, height)) {
			// 유효한 레이블 인덱스를 저장
			obj_array[index].label = index;

			// Component에 데이터 저장
			obj_array[index] = dataAllocateAtComponent(stats, obj_array[index], i);
			// Rect타입 변수에 레이블된 오브젝트 저장
			objectRegion = savingRectangle(frame, obj_array[index]);
			result.push_back(obj_array[index]);

			index++;
		}
	}

	return result;
}
