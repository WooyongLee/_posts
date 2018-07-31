#include "header.h"
#include<algorithm>

const string folderName = "segment";
void humonDetector(VideoCapture vc_Source);	// 사람 영역을 검출하여 파일로 저장하는 연산
vector<component> humanDetectedProcess(vector<component> humanDetectedVector, vector<component> prevHumanDetectedVector, Mat, int, int, unsigned int, FILE *fp);
void showComposeResult();	//캡쳐된 Components를 합성하는 연산
int getSortedSegmentArray(segment*);
string allocatingComponentFilename(vector<component> humanDetectedVector, int, int, int, int);
Mat morphologicalOperation(Mat img_binary);

int main() {
	// Video Input
	VideoCapture vc_Source("test.mp4");
	if (!vc_Source.isOpened()) { //예외처리. 해당이름의 파일이 없는 경우
		perror("No Such File!");
		exit(1);
	}

	///* Video Capture Property *///(http://docs.opencv.org/2.4/modules/highgui/doc/reading_and_writing_images_and_video.html)
	vc_Source.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	vc_Source.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	//UI
	int selection = 0;	//User input
	while (1) {
		printf("1. Object Segmentation\n2. Get Synthetic Image\n3. Exit  >>");
		scanf("%d", &selection);
		if (selection == 3) 
			break;
		else {
			switch (selection) {
			case 1:
				humonDetector(vc_Source);	//Object Segmentation
				break;
			case 2:
				showComposeResult();	//Get Synthetic Image
				break;
			default:
				printf("\nCheck Again.\n");
				break;
			}
		}
	}
	return 0;
}

void humonDetector(VideoCapture vc_Source)
{
	int videoStartHour = 0;
	int videoStartMin = 0;

	// Input Started Time
	printf("Input video's started time ( PM 04:30 -> 16:30 ) >> ");
	scanf("%d:%d", &videoStartHour, &videoStartMin);
	int videoStartMsec = (videoStartHour * 60 + videoStartMin) * 60 * 1000;
	printf("%d , %d", videoStartHour, videoStartMin);

	unsigned int COLS = (int)vc_Source.get(CV_CAP_PROP_FRAME_WIDTH);	//가로 길이
	unsigned int ROWS = (int)vc_Source.get(CV_CAP_PROP_FRAME_HEIGHT);	//세로 길이

	unsigned char* result = (unsigned char*)malloc(sizeof(unsigned char)* ROWS * COLS);

	/* 영상에 텍스트 출력 */
	char strBuffer[MAX_STR_BUFFER_SIZE] = { 0, }; // fps출력
	char timeBuffer[MAX_STR_BUFFER_SIZE] = { 0, }; // time 출력
	Scalar color(0, 0, 255); // B/G/R
	int thickness = 3;	// line thickness

	vector<component> humanDetectedVector;
	vector<component> prevHumanDetectedVector;
	unsigned int currentMsec;

	/* Mat */
	Mat frame(ROWS, COLS, CV_8UC3); // Mat(height, width, channel)
	Mat frame_g(ROWS, COLS, CV_8UC1);
	Mat background(ROWS, COLS, CV_8UC1); // 배경 프레임과 원본 프레임
	//frame 카운터
	int frameCount = 0;

	// 얻어낸 객체 프레임의 정보를 써 낼 텍스트 파일 정의
	FILE *fp; // frameInfo를 작성할 File Pointer
	fp = fopen("frameInfo.txt", "w");	// 쓰기모드

	vc_Source >> background; // 1 프레임 background 
	cvtColor(background, background, CV_RGB2GRAY);

	while (1) {
		vc_Source >> frame; //get single frame
		if (frame.empty()) {	//예외처리. 프레임이 없음
			perror("Empty Frame");
			break;
		}
		//그레이스케일 변환
		cvtColor(frame, frame_g, CV_RGB2GRAY);

		// 배경 생성
		background = TemporalMedianBg(frame_g, background, ROWS, COLS);

		// 전경 추출
		frame_g = ExtractFg(frame_g, background, ROWS, COLS);

		// 이진화
		threshold(frame_g, frame_g, 5, 255, CV_THRESH_BINARY);

		//노이즈 제거
		frame_g = morphologicalOperation(frame_g);
		blur(frame_g, frame_g, Size(9, 9));

		//MAT형으로 라벨링
		humanDetectedVector.clear();
		humanDetectedVector = connectedComponentLabelling_sequencial(frame_g, ROWS, COLS);

		// 영상의 포착 가져오기
		currentMsec = vc_Source.get(CV_CAP_PROP_POS_MSEC);

		// 영상을 처리하여 파일로 저장하기
		humanDetectedVector = humanDetectedProcess(humanDetectedVector, prevHumanDetectedVector, 
												frame, frameCount, videoStartMsec, currentMsec, fp);
		
		// 현재 검출한 데이터를 이전 데이터에 저장하기
		prevHumanDetectedVector = humanDetectedVector;

		// 영상을 출력하기
		imshow("mov", frame);
		imshow("binary", frame_g);
		//imshow("background", background);

		frameCount++;	//increase frame count
		if (waitKey(1) == 27)
			break; //ESC
	}
	cvDestroyAllWindows();
	fclose(fp);	// 텍스트 파일 닫기
}

void showComposeResult() {
	//큐 초기화
	Queue queue;
	InitQueue(&queue);

	// 고정 배경 프레임 불러오기
	Mat background = imread("background.jpg");
	unsigned int COLS = background.cols;	//가로 길이
	unsigned int ROWS = background.rows;	//세로 길이

	segment *segmentArray = (segment*)calloc(BUFFER, sizeof(segment));	//텍스트 파일에서 읽은 segment 정보를 저장할 배열 초기화
	int segmentCount;

	unsigned int obj1_TimeTag;	//검색할 TimeTag1
	unsigned int obj2_TimeTag;	//검색할 TimeTag2

	segmentCount = getSortedSegmentArray(segmentArray);	//텍스트 파일을 읽어서 segmentArray에 데이터를 저장하는 함수

	while (1) {
		printf("Input TimeTags witch want to compose.\n");
		scanf("%d", &obj1_TimeTag);
		scanf("%d", &obj2_TimeTag);

		bool find1 = false;
		bool find2 = false;

		//출력할 객체를 큐에 삽입하는 부분
		for (int i = 0; i < segmentCount - 1; i++) {
			if (find1 == false && segmentArray[i].timeTag == obj1_TimeTag) {	//아직 찾지 못했고 일치하는 타임태그를 찾았을 경우
				Enqueue(&queue, obj1_TimeTag, i);	//출력해야할 객체의 첫 프레임의 타임태그와 위치를 큐에 삽입
				find1 = true;
			}
			else if (find2 == false && segmentArray[i].timeTag == obj2_TimeTag) {	//아직 찾지 못했고 일치하는 타임태그를 찾았을 경우
				Enqueue(&queue, obj2_TimeTag, i);	//출력해야할 객체의 첫 프레임의 타임태그와 위치를 큐에 삽입
				find2 = true;
			}

			if (find1 == true && find2 == true)	//모두 찾았으면 더 찾을 필요가 없으므로 나옴
				break;
		}

		//예외처리, 하나라도 없을 경우
		if (find1 == false || find2 == false) {
			break;
		}


		Mat tempBackGround;
		//출력
		while (1) {
			//큐가 비었는지 확인한다
			if (IsEmpty(&queue))
				break;

			tempBackGround.setTo(0);
			background.copyTo(tempBackGround);	//임시로 쓸 배경 복사
			int *labelMap = (int*)calloc(COLS * ROWS, sizeof(int));	//겹침을 판단하는 용도
			node tempnode;	//DeQueue한 결과를 받을 node
			int countOfObj = queue.count;	//큐 인스턴스의 노드 갯수

			//DeQueue를 큐에 들어있는 객체 갯수 만큼 한다. 
			for (int i = 0; i < countOfObj; i++) {
				//dequeue한 객체를 출력한다.
				tempnode = Dequeue(&queue);

				//배경에 객체를 올리는 함수
				tempBackGround = printObjOnBG(tempBackGround, segmentArray[tempnode.indexOfSegmentArray], labelMap, COLS, ROWS);

				//다음목록에 같은 타임태그를 가진 객체가 있는지 확인한다. 있으면 EnQueue
				if (segmentArray[tempnode.indexOfSegmentArray + 1].timeTag == segmentArray[tempnode.indexOfSegmentArray].timeTag) {
					Enqueue(&queue, tempnode.timeTag, tempnode.indexOfSegmentArray + 1);
				}
			}

			imshow("Sync Result", tempBackGround);

			if (waitKey(1) == 27)
				break; //ESC

		}
		if (waitKey(1) == 27)
			return; //ESC
	}
	free(segmentArray);
	cvDestroyAllWindows();
}

//텍스트 파일을 읽어서 segmentArray에 데이터를 저장하는 함수
//returns 세그먼트 수
int getSortedSegmentArray(segment* segmentArray){
	char txtBuffer[100] = { 0, };	//텍스트파일 읽을 때 사용할 buffer

	// frameInfo.txt 파일에서 데이터를 추출 하여 segment array 초기화
	FILE *fp = NULL;
	fp = fopen("frameInfo.txt", "r");
	if (fp == NULL) {	//예외처리. 텍스트 파일을 찾을 수 없음
		perror("No File!");
		exit(1);
	}

	int segmentCount = 0;
	while (!feof(fp)) {
		fgets(txtBuffer, 99, fp);

		// txt파일에 있는 프레임 데이터들 segmentArray 버퍼로 복사
		sscanf(txtBuffer, "%d_%d_%d_%d %d %d %d %d %d %d",
			&segmentArray[segmentCount].timeTag, &segmentArray[segmentCount].msec,
			&segmentArray[segmentCount].frameCount, &segmentArray[segmentCount].index,
			&segmentArray[segmentCount].left, &segmentArray[segmentCount].top,
			&segmentArray[segmentCount].right, &segmentArray[segmentCount].bottom,
			&segmentArray[segmentCount].width, &segmentArray[segmentCount].height);

		// filename 저장
		segmentArray[segmentCount].fileName
			.append(to_string(segmentArray[segmentCount].timeTag)).append("_")
			.append(to_string(segmentArray[segmentCount].msec)).append("_")
			.append(to_string(segmentArray[segmentCount].frameCount)).append("_")
			.append(to_string(segmentArray[segmentCount].index)).append(".jpg");

		// segmentArray의 인덱스 증가
		segmentCount++;
	}

	// 버블 정렬 사용하여 SegmentArray를 TimeTag순으로 정렬
	segment tmp_segment;
	for (int i = 0; i < segmentCount - 1; i++) {
		for (int j = 0; j < segmentCount - 2; j++) {
			if (segmentArray[j].timeTag > segmentArray[j + 1].timeTag) {
				// segmentArray[segmentCount]와 segmentArray[segmentCount + 1]의 교체
				memcpy(&tmp_segment, &segmentArray[j + 1], sizeof(segment));// tmp_segment <- segmentArray[segmentCount - 1]
				memcpy(&segmentArray[j + 1], &segmentArray[j], sizeof(segment));// segmentArray[segmentCount - 1] <- segmentArray[segmentCount]
				memcpy(&segmentArray[j], &tmp_segment, sizeof(segment));// segmentArray[segmentCount] <- tmp_segment
			}
		}
	}

	//정렬 확인용
	{
		//for (int i = 0; i < segmentCount; i++)
		//	cout << segmentArray[i].fileName <<endl;
	}
	fclose(fp);
	return segmentCount;
}

vector<component> humanDetectedProcess(vector<component> humanDetectedVector, vector<component> prevHumanDetectedVector
	, Mat frame, int frameCount, int videoStartMsec, unsigned int currentMsec, FILE *fp) 
{
	int prevTimeTag;
	for (int i = 0; i < humanDetectedVector.size(); i++) {
		// TODO : 현재 프레임에서 이전프레임과 겹치는 obj가 있는지 판단한다. 
		// 이전 오브젝트에 다음오브젝트가 두개가 걸칠 경우 어떻게 처리할 것인가?
		if (prevHumanDetectedVector.empty() == 0) {	//이전 프레임의 검출된 객체가 있을 경우
			bool findFlag = false;
			for (int j = 0; j < prevHumanDetectedVector.size(); j++) {
				if (humanDetectedVector[i].left < prevHumanDetectedVector[j].right
					&& humanDetectedVector[i].right > prevHumanDetectedVector[j].left
					&& humanDetectedVector[i].top < prevHumanDetectedVector[j].bottom
					&& humanDetectedVector[i].bottom > prevHumanDetectedVector[j].top) {	// 두 ROI가 겹칠 경우

					prevTimeTag = prevHumanDetectedVector[j].timeTag;
					humanDetectedVector[i].fileName = allocatingComponentFilename(humanDetectedVector, prevTimeTag, currentMsec, frameCount, i);

					humanDetectedVector[i].timeTag = prevTimeTag;
					printf("\n@@@@@@@@@@@@@@@@@@@@@\n %s와 현재 %s 가 겹침%d, %d\n@@@@@@@@@@@@@@@@\n", prevHumanDetectedVector[j].fileName.c_str(), humanDetectedVector[i].fileName.c_str());
					saveSegmentation_JPG(humanDetectedVector[i], frame, frameCount, currentMsec, i, videoStartMsec);
					saveSegmentation_TXT(humanDetectedVector[i], frameCount, currentMsec, fp, i);
					findFlag = true;
					//break;
				}
			}

			if (findFlag == false) {
				humanDetectedVector[i].timeTag = currentMsec;
				humanDetectedVector[i].fileName = allocatingComponentFilename(humanDetectedVector, currentMsec, currentMsec, frameCount, i);
				printf("\n*********************************\n 새객채 %s 출현\n*********************************\n"
					, humanDetectedVector[i].fileName.c_str());

				saveSegmentation_JPG(humanDetectedVector[i], frame, frameCount, currentMsec, i, videoStartMsec);
				saveSegmentation_TXT(humanDetectedVector[i], frameCount, currentMsec, fp, i);
			}
		}
		else {	//첫 시행이거나 이전 프레임에 검출된 객체가 없을 경우
				//새로운 이름 할당
			humanDetectedVector[i].timeTag = currentMsec;
			humanDetectedVector[i].fileName = allocatingComponentFilename(humanDetectedVector, currentMsec, currentMsec, frameCount, i);
			printf("\n*********************************\n 새객채 %s 출현\n*********************************\n", humanDetectedVector[i].fileName.c_str());
			saveSegmentation_JPG(humanDetectedVector[i], frame, frameCount, currentMsec, i, videoStartMsec);
			saveSegmentation_TXT(humanDetectedVector[i], frameCount, currentMsec, fp, i);
		}
	}
	return humanDetectedVector;
}

string allocatingComponentFilename(vector<component> humanDetectedVector, int timeTag, int currentMsec, int frameCount, int indexOfhumanDetectedVector) {
	string name;
	name.append(to_string(timeTag)).append("_")
		.append(to_string(currentMsec)).append("_")
		.append(to_string(frameCount)).append("_")
		.append(to_string(indexOfhumanDetectedVector));
	return name;
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


//float calcFPS(DWORD startTime, long frameCount) {
//	return ((float)(1000 * frameCount) / (timeGetTime() - startTime));
//	// time 단위가 ms이기 때문에 전체에 1000 곱해야함;
//}