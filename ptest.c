#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main() {
	int n = 0; // test를 위한 임시변수
	time_t tm;
	time(&tm); // 시스템 시간으로 초기화
	while (1) {
		printf("system local time : %ld\n", tm);	
		sleep(2); // 2초간 대기
		time(&tm); // 다시 초기화i
		if ( n++ > 50 ) break;
	}
	return 0;	
}
