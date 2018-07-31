#include "LwyDeque.h"
#include "LwyDeQueue.h"

void main(){

	printf("\n************* [ 2015년도 2학기 자료구조 실습과제 9 ] *************\n\n");
	printf("                       1. 큐 테스트 프로그램\n\n");

	printf("------------ [ 상속을 이용하지 않은 덱 CDeque 클래스 ] -----------\n\n");
	CLwyDeque q;

	printf(" CDeque 전단삽입 8번 실행 => ");
	for( int i=1 ; i<9 ; i++){
		q.AddFront(i);
	}
	q.Display();
	
	printf(" CDeque 전단삭제 3번 실행 => ");
	q.DelFront();
	q.DelFront();
	q.DelFront();
	
	q.Display();

	printf(" CDeque 후단삽입 3번 실행 => ");
	q.AddRear(9);
	q.AddRear(10);
	q.AddRear(11);
	
	q.Display();

	printf(" CDeque 후단삭제 2번 실행 => ");
	q.DelRear();
	q.DelRear();

	q.Display();

	printf("\n\n---------------- [ 상속을 이용한 CDeQueue 클래스 ] ---------------\n\n");
	CLwyDeQueue q2;

	printf(" CDeQueue 전단삽입 8번 실행 => ");
	for( int i=21 ; i<29 ; i++){
		q2.AddFront(i);
	}
	q2.Display();
	
	printf(" CDeQueue 전단삭제 3번 실행 => ");
	q2.DelFront();
	q2.DelFront();
	q2.DelFront();
	
	q2.Display();

	printf(" CDeQueue 후단삽입 3번 실행 => ");
	q2.AddRear(29);
	q2.AddRear(30);
	q2.AddRear(31);
	
	q2.Display();

	printf(" CDeQueue 후단삭제 2번 실행 => ");
	q2.DelRear();
	q2.DelRear();

	q2.Display();

	getchar();
	getchar();
}