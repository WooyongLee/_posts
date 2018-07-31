
#include "LwyDLinkedList.h"

void main() {

	printf("\n******************* [ 2015년도 2학기 자료구조 실습과제 11 ] *******************\n\n");
	printf("                1. 이중리스트로 구현한 Wish List 구현 프로그램   \n\n");

	printf("-------------------         Addtail 2회, AddHead 2회        -------------------\n\n");
	CLwyDLinkedList list1;													// CLinkedList 클래스의 list 객체 생성
	list1.AddTail(new CLwyDNode("정장", 8000000, 4, "엄마카드로"));		// 마지막 위치에 리스트 추가
	list1.AddTail(new CLwyDNode("노트북", 9500000, 5, "내년에"));		// 마지막 위치에 리스트 추가
	list1.AddHead(new CLwyDNode("안경", 150000, 2, "다음달에"));		// 맨 처음 위치에 리스트 추가
	list1.AddHead(new CLwyDNode("신발", 100000, 1));					// 맨 처음 위치에 리스트 추가
	list1.Display( "list1 " );											// 리스트 전체 출력

	printf("-------------------   우선순위값이 2인 노드 탐색 & AddNext  -------------------\n\n");
	CLwyDNode *n = list1.FindNodePriority( 2 );							// 우선순위값이 2인 노드 탐색
	list1.AddNext(n, new CLwyDNode("외투", 100000, 3, "12월 전에"));	// 우선순위값이 2인 노드 뒤에 새로운 노드 삽입
	list1.Display( "list1 " );			
	
	printf("------- RemoveHead() , 우선순위값이 2인 노드 탐색 & 삭제, RemoveTail() --------\n\n");
	list1.DeleteHead();													// 리스트 맨 앞 노드 삭제
	n = list1.FindNodePriority( 2 );									// 우선순위값이 2인 노드 탐색
	list1.Delete( n );													// 그 노드 삭제
	list1.DeleteTail();													// 리스트 맨 뒤 노드 삭제
	list1.Display( "list1 " );											// 리스트내용 화면출력													

	printf("------------- List1 DisplayRev() : 거꾸로 출력(실제순서변경x) 반복 ------------\n\n");
	list1.DisplayRev( "list1 " );										// 리스트내용 역순 화면출력

	printf("------------- List1 DisplayRevRe() : 거꾸로 출력(실제순서변경x) 재귀 ------------\n\n");
	list1.DisplayRevRecur( "list1 " );										// 리스트내용 역순 화면출력

/*	CLwyDLinkedList list2;													// CLinkedList 클래스의 list 객체 생성
	list2.AddTail(new CLwyDNode("정장", 8000000, 4, "엄마카드로"));		// 마지막 위치에 리스트 추가
	list2.AddTail(new CLwyDNode("노트북", 9500000, 5, "내년에"));		// 마지막 위치에 리스트 추가
	list2.AddHead(new CLwyDNode("안경", 150000, 2, "다음달에"));		// 맨 처음 위치에 리스트 추가
	list2.AddHead(new CLwyDNode("신발", 100000, 1));					// 맨 처음 위치에 리스트 추가

	list1.Merge(list2);
	list1.Display("List1 merge");  */

	printf("-------------------   list1의 모든 항목 삭제 & list1 출력  -------------------\n\n");
	list1.Clear();													// 리스트의 모든 항목 삭제
	list1.Display( "list1 " );													// 리스트내용 화면출력

	getchar();
	getchar();


}
