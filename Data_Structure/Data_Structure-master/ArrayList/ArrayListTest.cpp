#include "LwyArrayList.h"

void main(){
	printf("\n******************* [ 2015년도 2학기 자료구조 실습과제 10 ] *******************\n\n");
	printf("                          1. Array List 구현 프로그램   \n\n");

	CLwyArrayList list1;			// 리스트 객체 List1 생성

	printf("Add() 3회, AddHead() 1회, AddTail() 1회\n\n");
	list1.Add( 0, 10 );			// 리스트 0 위치에 10 삽입
	list1.Add( 0, 20 );			// 리스트 0 위치에 20 삽입
	list1.Add( 0, 30 );			// 리스트 0 위치에 30 삽입
	list1.AddHead( 40 );		// 리스트 맨 앞에 40 삽입
	list1.AddTail( 50 );		// 리스트 맨 뒤에 50 삽입
	list1.Display( "list1 " );	// list1 출력

	printf("Remove( 2 ), RemoveHead() 1회, RemoveTail() 1회\n\n");
	list1.Remove( 2 );			// 리스트 2번째 위치 항목 삭제
	list1.RemoveHead();			// 리스트 맨 앞의 위치 항목 삭제
	list1.RemoveTail();			// 리스트 맨 뒤 위치 항목 삭제
	list1.Display( "list1 " );	// list1 출력

	printf("Replace( 1, 90)\n\n");
	list1.Replace( 1, 90);		// 1번 위치의 항목값 90으로 변경
	list1.Display( "list1 " );	// list1 출력
	
	printf("Clear()\n\n");
	list1.Clear();				// 리스트의 모든 항목 삭제
	list1.Display( "list1 " );	// list1 출력
	
	getchar();
	getchar();
}