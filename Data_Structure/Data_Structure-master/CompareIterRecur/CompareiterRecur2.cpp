#include <stdio.h>
#include <stdlib.h>

int lwy_FiboIter(int n); // 반복적인 방법
int lwy_FiboRecur(int n); // 순환적인 방법

int count_FiboRecur[] = {0, }; // lwy_FiboRecur함수의 수행횟수를 저장하는 변수, 
// 모두 0 으로 초기화했음
int main() { 
	int result_FiboIter = 0, result_FiboRecur = 0, i; // 각 함수의 리턴되는 결과값을 알아보는 변수
	int number = 0; // 구할 피보나치 수
	char c; // exe파일의 종료를 위한 변수
	printf("구할 피보나치 수를 입력하시오 >> ");
	scanf("%d", &number);
	printf("number값  FiboIter   FiboRecur \n");
	for ( i = 0 ; i <= number ; i++ ) {
		result_FiboIter = lwy_FiboIter(i);
		result_FiboRecur = lwy_FiboRecur(i);
		printf("n= %d          %d          %d\n", i, result_FiboIter , result_FiboRecur);
	}

	for ( i = 0 ; i < number ; i++ ) {
		count_FiboRecur[i] = 0; // 앞에서 이미 연산을 했기 때문에 저장된 횟수를 일단 모두 초기화 
	}
	printf("호출횟수를 출력합니다 >>> \n");
	
	result_FiboRecur = lwy_FiboRecur(number); // 함수 호출후
	count_FiboRecur[number] = 1; // number이 가장 큰 수일때를 매개변수로 받는 순환 함수는 단 한번 반복함
	for ( i = 0 ; i <= number; i++ ) {
		printf("lwy_FiboRecur(%d)호출횟수 : %d\n", i, count_FiboRecur[i]); // 호출횟수 출력하기
	}
	
	printf("\n");

	printf("x를 누르시면 프로그램이 종료됩니다 >> ");
	do {
        c=getchar();
	} while (c != 'x');
	return 0;
}
int lwy_FiboIter(int n)
{ 
	int temp, current = 1 , last = 0; // 임시변수와 현재수, 이전 수를 선언
	if ( n < 2 ) // n이 0이나 1인 경우 
		return n; // 그대로 반환하면 됨
	else { // n번째 수는 n-1번째 수와 n-2번째 수를 더해 만든 것이다.
		for ( int i = 2 ; i <= n ; i++ ) {
			temp = current; // 임시변수에 n-1번쨰 수를 넣고
			current += last; // n-2번쨰 수와 n-1번째 수를 더하여 n번째 수를 만든다.
			last = temp; // n-2번째 수를 n-1번째 수로 옮겨준다.
		}
	}
	return current; // 마지막 수를 반환한다.
}	

int lwy_FiboRecur(int n)
{
	count_FiboRecur[n] += 1; // 함수를 수행할 때 마다 n배열 부터 계속 1씩 더해감
	//함수가 계속 재귀적으로 호출되면서 n의 값이 계속 하나, 둘씩 빠지면서 결국 0번째 배열까지 연산이 됨
	if ( n < 2 ) 
		return n; // n이 0이나 1일경우 n의값은 0과 1이므로 바로 반환한다.
	else
		return (lwy_FiboRecur(n-1) + lwy_FiboRecur(n-2)); // 전에 수와 전전의 수를 한번 더 호출해서 더한다.
}