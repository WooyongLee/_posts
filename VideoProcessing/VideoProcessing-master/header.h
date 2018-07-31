#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#include <opencv\cv.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>
#include <io.h>


const int BUFFER_SYNCFRAME = 16; // �ռ��� ������ �����͸� ������ ������ ũ��
#define BUFFER 8096 // ��ü ������ �����͸� ������ ������ ũ�� 
#define MAX_STR_BUFFER_SIZE  128 // ���ڿ� ��¿� �� ���� ����

#define CV_CAP_PROP_POS_MSEC 0	//���󿡼� ���� ��ġ�� msec
#define CV_CAP_PROP_POS_FRAME 1	//���󿡼� ���� �������� ��ġ
#define CV_CAP_PROP_FRAME_WIDTH 3
#define CV_CAP_PROP_FRAME_HEIGHT 4
#define CV_CAP_PROP_FPS 5
#define CV_CAP_PROP_FRAME_COUNT 7 //��ü ������ �� ( ��Ȯ���� �ʴٰ� �� )

// ������ �ʺ�� ����
// test.avi : 768x576, test.mp4 : 640x480 (���� ��� ����)

const int COLS = 640; // width
const int ROWS = 480; // height

// namespade
using namespace cv;
using namespace std;

// 3 channel color
struct colorAttribute {
	int blue;
	int red;
	int green;
};

// segmentation structure
typedef struct _segment {
	string fileName;
	unsigned int timeTag;
	unsigned int msec;
	unsigned int frameCount;
	unsigned int index;
	int left;
	int top;
	int right;
	int bottom;
	int width;
	int height;
	 _segment() {
		fileName = "";
		timeTag = 0;
		msec = 0;
		frameCount = 0;
		index = 0;
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
		width = 0;
		height = 0;
	}
}segment;

//component model
typedef struct _component {
	string fileName;
	unsigned int timeTag;
	unsigned int label;
	unsigned int sumOfX;
	unsigned int sumOfY;
	unsigned int size;
	float centerOfX;
	float centerOfY;
	unsigned int firstPixel;
	unsigned int left;
	unsigned int right;
	unsigned int top;
	unsigned int bottom;
	unsigned int width;
	unsigned int height;
	_component() {
		fileName = "";
		timeTag = 0;
		label = 0;
		sumOfX = 0;
		sumOfY = 0;
		size = 0;
		centerOfX = 0.0;
		centerOfY = 0.0;
		firstPixel = 0;
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
		width = 0;
		height = 0;
	}
}component;

// Find background, foreground
Mat TemporalMeanBg(Mat frameimg, Mat bgimg, int row, int col, double);
Mat TemporalMedianBg(Mat frameimg, Mat bgimg, int row, int col);
Mat ExtractFg(Mat, Mat, int, int);

// Image Synthetic
Mat Syn_Background_Foreground(Mat , Mat , Mat , int , int );
Mat printObjOnBG(Mat , segment , int* , int , int );

// pixelValueOp
double SumOfPixel(Mat , int , int );
Point* SaveOfPixel(Mat , int , int  );

// Save Segment In File
void saveSegmentation_JPG(component , Mat , int , int , int , unsigned int );	//ĸ���� Components�� jpg���Ϸ� �����ϴ� �Լ�
void saveSegmentation_TXT(component , int , int , FILE *, int );	//components�� Data�� txt�� �����ϴ� �Լ�

// Connected Component Labelling Operators
vector<component> connectedComponentLabelling_sequencial(Mat , int , int );
Mat objectCutting(component , Mat , unsigned int , unsigned int );

// connectedComponentsWithStats Labelling Operators
Mat objectHistogram;
Mat globalHistogram;

// Data structure
typedef struct node //��� ����
{
	unsigned int timeTag;
	int indexOfSegmentArray;
	struct node *next;
}node;
typedef struct Queue //Queue ����ü ����
{
	node *front; //�� ��(���� ��ġ)
	node *rear; //�� ��(������ ��ġ)
	int count;//���� ����
}Queue;
void InitQueue(Queue *);
int IsEmpty(Queue *);
void Enqueue(Queue *, int , int );
node Dequeue(Queue *);