#include <stdio.h>
#include <time.h>
#include <windows.h>

double lwy_PowerIter(double x, int n);//�ݺ����� ���
double lwy_PowerRecur(double x, int n);//��ȯ���� ���

int main() {
	clock_t t0, t1, t2; // �ð����� 
	double t_Iter, t_Recur; // �ݺ����� ����� ��ȯ���� ��� ������ ó���ð�
	double x_num = 0.0, temp; // ������ ����� ������ ������� �ӽ÷� �ִ� ����
	int num = 0; // ������ �ߴ����� ���� ����
	
	x_num = 5; // ���� 5����
	num = 3; // �ϴ� ������ 3�� �����غ�
	temp = lwy_PowerIter(x_num, num); // �ݺ� �Լ��� ȣ��
	printf("%.3f^%d = %.15f\n", x_num, num, temp);
	temp = lwy_PowerRecur(x_num, num); // ��ȯ �Լ��� ȣ��
	printf("%.3f^%d = %.15f\n", x_num, num, temp);
	
	printf("x�� �� : %f\n", x_num);
	printf("n�� ��   PowerIter   PowerRecur �� ����ð�\n");
	for ( num = 1000 ; num < 30000 ; num += 100 ) {
		t0 = clock(); // ó�� �ð�
		temp = lwy_PowerIter(x_num, num); //
		t1 = clock(); //  �ݺ����� ����� �����ϰ� �� ���� �ð�
		temp = lwy_PowerRecur(x_num, num);
		t2 = clock(); //  ��ȯ���� ����� �����ϰ� �� ���� �ð�

		t_Iter = (double)(t1 - t0) / CLOCKS_PER_SEC;
		t_Recur = (double)(t2 - t1) / CLOCKS_PER_SEC; // �� ����ð��� ���� �ð������� ����
		printf("%d  %8.3f  %11.3f \n", num, t_Iter, t_Recur); // ��¹���
	}
	return 0;
}

double lwy_PowerIter(double x, int n)
{
	double result_PowerIter = 1; // ����� ��ȯ�� double�� ����
	if (n == 0) { // � ���� 0������ �׻� 1�̳���
		return 1;
	}
	else {
		for ( int i = 0; i < n ; i++ ) { // n�����̴� nȸ �ݺ�
			result_PowerIter *= x;// ������� ��� ������
			Sleep(1); // ��¿� ���� Sleep�� �ɾ���
		}
	}
	return result_PowerIter; // �����ȯ
}

double lwy_PowerRecur(double x, int n)
{
	double result_PowerRecur = 1;// ����� ��ȯ�� double�� ����
	if ( n == 0 ) {// n�� 0�ϰ�� 1�� ��ȯ
		Sleep(1); // ���� ���Ǹ� ���� Sleep �Լ�
		return result_PowerRecur;
	}
	else if ( ( n % 2) == 0) { // n�� ¦��
		Sleep(1);
		return lwy_PowerRecur(x*x, n / 2); // �������� �������� �� ���ϰ� �Լ��� �ѹ� �� ȣ���Ͽ� n�� ������ ����
	}
	else { // n�� Ȧ��
		Sleep(1);	
		return x * lwy_PowerRecur(x*x, (n - 1) / 2 ); // �Լ��� �ѹ� �� ȣ�� �ϸ鼭  
	}
}