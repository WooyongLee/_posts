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
	// Ÿ���±��� �������
	// (min�� 100 max�� 5000�̸� �迭�� �տ� 100���� ���������� 5000�� �����Ѱŷ� ������)

	for (int i = 0; i < 30; i++)
		numOfTimetag[i] = -1;
	// numOfTimetag �迭 ����Ʈ ������ �ʱ�ȭ

	numOfTimetag[0] = 150; // 0���±�
	numOfTimetag[1] = 80; // 1���±�
	numOfTimetag[2] = 70; // 2���±�
	numOfTimetag[3] = 240;

	// numOfTimetag �迭 Ư�� ����� �ʱ�ȭ

	for (int i = 0; numOfTimetag[i] != -1; i++) {
		if (maxOfTimetag < numOfTimetag[i])
			maxOfTimetag = numOfTimetag[i];
		numOfTimetagSize++;
	} // numOfTimetag ������ ��� �� maxNumOfTimetag ���ϱ�

	queue<int> Queue;
	double tmp = 0; // ����ȭ�� ����� �Ǽ��� ����
	double tmp2 = 0; // tmp2�� ���������� ��ȯ�Ѱ�
	int prevtmp2 = -1;
	int numOfShowingFrame = 0;
	for (int j = 0; j < numOfTimetagSize; j++) {
		if (maxOfTimetag == numOfTimetag[j]) {}// Ÿ���±� ũ�Ⱑ �ִ� Ÿ���±׿� ������ ����ȭ ������ �� �ʿ䰡 ����
		else {
			printf("numOfTimetag[%d] Ÿ���±� ����ȭ\n", j);
			for (int i = 0; i < maxOfTimetag; i++) {
				tmp = (double)i / (double)numOfTimetag[j] * (double)maxOfTimetag;
				// printf("%.2lf, ", tmp);

				tmp2 = (int)tmp; // tmp�� ������ ���� tmp2�� ����
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
	
	//  max���� ���� ��ġ ����ȭ

}