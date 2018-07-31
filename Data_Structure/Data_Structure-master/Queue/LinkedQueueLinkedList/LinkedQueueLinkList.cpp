#include "LwyLinkedQueue.h"
// 과제 8에 했던 cpp파일을 옮겨왔습니다
#include <stdlib.h>
void main(){

	printf("\n***************** [ 2015년도 2학기 자료구조 실습과제 9 ] *****************\n\n");
	printf("                       2. 연결 큐 테스트 프로그램   \n\n");

	CLwyLinkedQueue que;

	printf(" CLinkedQueue 삽입 8번 실행 => ");
	for( int i=1 ; i<9 ; i++){
		que.EnQueue(new CLwyNode(i));
	}
	que.DisPlay();
	
	printf(" CLinkedQueue 삭제 3번 실행 => ");
	CLwyNode* n;
	//int n = 0;
	n = que.DeQueue(); delete n;
	n = que.DeQueue(); delete n;
	n = que.DeQueue(); delete n;

	que.DisPlay();

	printf(" CLinkedQueue 반환 Peek() 실행 => %2c", que.Peek()->GetInt());

	getchar();
	getchar();
}