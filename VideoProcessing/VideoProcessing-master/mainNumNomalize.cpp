#include <stdio.h>
#include <iostream>
#include <queue>
#include <Windows.h>

using namespace std;

void main()
{
	int numOfTimetag[30] = { -1 };
	int numOfTimetagSize = 0;
	int maxOfTimetag = 0;
	// 타임태그의 순서대로
	// (min이 100 max가 5000이면 배열의 앞에 100부터 마지막에는 5000에 근접한거로 들어가도록)

	for (int i = 0; i < 30; i++)
		numOfTimetag[i] = -1;
	// numOfTimetag 배열 디폴트 값으로 초기화

	numOfTimetag[0] = 150; // 0번태그
	numOfTimetag[1] = 80; // 1번태그
	numOfTimetag[2] = 70; // 2번태그
	numOfTimetag[3] = 240;

	// numOfTimetag 배열 특정 값들로 초기화

	for (int i = 0; numOfTimetag[i] != -1; i++) {
		if (maxOfTimetag < numOfTimetag[i])
			maxOfTimetag = numOfTimetag[i];
		numOfTimetagSize++;
	} // numOfTimetag 사이즈 계산 및 maxNumOfTimetag 구하기

	queue<int> Queue;
	double tmp = 0; // 정규화에 사용할 실수형 변수
	double tmp2 = 0; // tmp2는 정수형으로 변환한거
	int prevtmp2 = -1;
	int numOfShowingFrame = 0;
	for (int j = 0; j < numOfTimetagSize; j++) {
		if (maxOfTimetag == numOfTimetag[j]) {}// 타임태그 크기가 최대 타임태그와 같으면 정규화 연산을 할 필요가 없음
		else {
			printf("numOfTimetag[%d] 타임태그 정규화\n", j);
			for (int i = 0; i < maxOfTimetag; i++) {
				tmp = (double)i / (double)numOfTimetag[j] * (double)maxOfTimetag;
				// printf("%.2lf, ", tmp);

				tmp2 = (int)tmp; // tmp를 내림한 값을 tmp2에 넣음
				// printf("%d, ", (int)tmp2);
				
				tmp = tmp - (double)tmp2;
				// printf("%.2lf, ", tmp);

				numOfShowingFrame = (int)tmp2 - prevtmp2;
				printf("%d, ", numOfShowingFrame);

				prevtmp2 = (int)tmp2;
			}
			prevtmp2 = -1;
			printf("\n");
		}
	}
	
	//  max값에 따라서 수치 정규화

}