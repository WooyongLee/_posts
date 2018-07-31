#include <stdio.h>
#include <time.h>
#include <windows.h>

double lwy_PowerIter(double x, int n);//반복적인 방법
double lwy_PowerRecur(double x, int n);//순환적인 방법

int main() {
	clock_t t0, t1, t2; // 시간변수 
	double t_Iter, t_Recur; // 반복적인 방법과 순환적인 방법 각각의 처리시간
	double x_num = 0.0, temp; // 제곱을 계산할 변수와 결과값을 임시로 넣는 변수
	int num = 0; // 몇제곱 했는지를 넣을 변수
	
	x_num = 5; // 밑을 5대입
	num = 3; // 일단 지수에 3을 대입해봄
	temp = lwy_PowerIter(x_num, num); // 반복 함수를 호출
	printf("%.3f^%d = %.15f\n", x_num, num, temp);
	temp = lwy_PowerRecur(x_num, num); // 순환 함수를 호출
	printf("%.3f^%d = %.15f\n", x_num, num, temp);
	
	printf("x의 값 : %f\n", x_num);
	printf("n의 값   PowerIter   PowerRecur 의 수행시간\n");
	for ( num = 1000 ; num < 30000 ; num += 100 ) {
		t0 = clock(); // 처음 시각
		temp = lwy_PowerIter(x_num, num); //
		t1 = clock(); //  반복적인 방법을 수행하고 난 후의 시간
		temp = lwy_PowerRecur(x_num, num);
		t2 = clock(); //  순환적인 방법을 수행하고 난 후의 시간

		t_Iter = (double)(t1 - t0) / CLOCKS_PER_SEC;
		t_Recur = (double)(t2 - t1) / CLOCKS_PER_SEC; // 각 수행시간의 차를 시간변수에 저장
		printf("%d  %8.3f  %11.3f \n", num, t_Iter, t_Recur); // 출력문구
	}
	return 0;
}

double lwy_PowerIter(double x, int n)
{
	double result_PowerIter = 1; // 결과를 반환할 double형 변수
	if (n == 0) { // 어떤 수의 0제곱은 항상 1이나옴
		return 1;
	}
	else {
		for ( int i = 0; i < n ; i++ ) { // n제곱이니 n회 반복
			result_PowerIter *= x;// 결과값에 계속 곱해줌
			Sleep(1); // 출력에 좋게 Sleep을 걸어줌
		}
	}
	return result_PowerIter; // 결과반환
}

double lwy_PowerRecur(double x, int n)
{
	double result_PowerRecur = 1;// 결과를 반환할 double형 변수
	if ( n == 0 ) {// n이 0일경우 1을 반환
		Sleep(1); // 역시 편의를 위한 Sleep 함수
		return result_PowerRecur;
	}
	else if ( ( n % 2) == 0) { // n이 짝수
		Sleep(1);
		return lwy_PowerRecur(x*x, n / 2); // 원래수를 원래수와 더 곱하고 함수를 한번 더 호출하여 n을 반으로 줄임
	}
	else { // n이 홀수
		Sleep(1);	
		return x * lwy_PowerRecur(x*x, (n - 1) / 2 ); // 함수를 한번 더 호출 하면서  
	}
}