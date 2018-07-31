#include <stdio.h>
#include <stdlib.h>

int lwy_hanoi(int size, char from, char temp, char to); // 하노이탑 함수
int lwy_hanoiFrequency(int size, char from, char temp, char to); // 탑이 옮겨지는 것을 출력하지 않고, 값만 반환하는 함수
// 원판의 크기, 처음위치, 임시변수, 옮겨질 위치를 매개변수로 받음
int main()
{
	int number = 0; // 넘길 원반의 갯수
	int moveNumber = 0, temp = 0; // 원반 넘겨지는 횟수와 임시변수
	char c; // exe파일의 종료를 위한 변수
	printf("넘길 원반의 갯수를 입력받습니다 : ");
	scanf("%d", &number); // 표준입력
	moveNumber = lwy_hanoi(number, 'A', 'B', 'C'); // 함수호출
	printf("\n %d개의 원반이 총 옮겨진 횟수 = %d\n", number, moveNumber);

	printf("\n3부터 15개가지의원반이 옮겨지는 횟수를 출력합니다 >> \n");
	for ( int i = 3 ; i < 16 ; i++ ) {
		moveNumber = lwy_hanoiFrequency(i, 'A', 'b', 'C');// 한번 반복하고 얻은 횟수값은 0으로 초기화 되지 않고
		// 계속 전의 값이 남아있는 상태에서 다음 함수 수행후 더함
		printf("%d 개의 원반이 움직인 횟수 : %d\n", i, moveNumber - temp); // 새로 얻은값에 이전에 값의 차이가 현재 횟수, 이를 출력함
		temp = moveNumber;// 임시변수를 지정하여 전에 얻은 횟수의 값을 저장해 놓음
	}
	printf("x를 누르시면 프로그램이 종료됩니다");
	do {
        c=getchar();
	} while (c != 'x');
	return 0;
}
int lwy_hanoi(int size, char from, char temp, char to) 
{
	static int frequency_number = 0; // 옮겨질 횟수를 받는 변수
	// 함수를 계속 돌리기 때문에 한번만 초기화 해주려고 static변수사용 
	if ( size == 1 )  {
		printf("%c => %c (크기 %d인 원반)\n", from, to, size);
		frequency_number++; // 옮긴 문구를 출력하고 바로 횟수를 증가시킴
	}
	else {
		lwy_hanoi(size-1, from, to, temp); 
		printf("%c => %c (크기 %d인 원반)\n", from, to, size);
		frequency_number++;
		lwy_hanoi(size-1, temp, from, to);	
	}
	return frequency_number; // 옮겨질 변수 반환
}

int lwy_hanoiFrequency(int size, char from, char temp, char to)
{
	static int frequency_number = 0; // 옮겨질 횟수를 받는 변수
	if ( size == 1 )  {
		frequency_number++; // 횟수를 증가시킴
	}
	else {
		lwy_hanoiFrequency(size-1, from, to, temp); 
		frequency_number++;
		lwy_hanoiFrequency(size-1, temp, from, to);	
	}
	return frequency_number; // 옮겨질 변수 반환
}