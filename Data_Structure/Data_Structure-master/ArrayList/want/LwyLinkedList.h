#pragma once
#include "LwyItemNode.h"
class CLwyLinkedList
{
	CLwyNode m_org;
public:
	CLwyLinkedList() {	} // 생성자와 소멸자 정의  
	~CLwyLinkedList(void) { Clear(); }  // 소멸하면서 Clear 
	//기본함수
	CLwyNode* GetHead() { return m_org.Next(); } // Head를 반환 
	bool IsEmpty( ) { return GetHead() == NULL; } // 공백 리스트 확인 
	CLwyNode* GetTail(); // Tail을 반환 
	int GetLength(); // Display 함수에서 리스트의 길이를 반환하기 위해 사용 
	void Display(char *); // 출력함수 
	CLwyNode *RemovedHead()   { return m_org.DeleteNext(); } // Head를 삭제, Clear함수를 구현하기 위함 
	//CLwyLinkedList클래스의 삽입함수들
	void AddHead( CLwyNode *n) { m_org.addNext(n); } // 링크를 따라 다음 노드를 n으로 줌
	void AddTail( CLwyNode *n); 
	void AddNext( CLwyNode *p, CLwyNode *n ) { p->addNext(n); }
	//CLwyLinkedList클래스의 삭제함수들
	void DeleteHead(); // Head를 가리키는 노드 하나 삭제
	void Delete( CLwyNode *n); // n 노드 삭제
	void Clear(); // 리스트 초기화
	//CLwyLinkedList크래스의 탐색함수들
	CLwyNode* FindNodePriority(int ); // 노드의 순번을 받아서 노드 반환
	CLwyNode* FindPrev(CLwyNode *); // 이전 노드를 찾는 함수
	//기타 함수들
	void Merge( CLwyLinkedList &); // List1 + List2 => List1 ,, List2 날려버림
//	void Reverse(); 
};
CLwyNode* CLwyLinkedList::GetTail()
{
	if (IsEmpty()) return &m_org; // 예외처리, 공백일 때 연산 불가
	CLwyNode* tail = &m_org;
	for ( ; tail->Next() != NULL; tail = tail->Next() );
	return tail;
} // 리스트의 tail 반환
int CLwyLinkedList::GetLength()
{
	int count = 0;
	//for ( int i = 0 ; i < max ; i++ )
	for ( CLwyNode* p = GetHead() ; p!= NULL ; p=p->Next() ) 
		count++;
	return count;
}// 리스트 항목갯수 반환
void CLwyLinkedList::Display(char* s)
{
	printf("[%s 의 전체 항목 수 = %2d]\n", s, GetLength());
	for ( CLwyNode *p = GetHead() ; p != NULL ; p = p->Next() )
		p->Display();
	printf("\n");
}
void CLwyLinkedList::Clear()
{ // 안에서 RemovedHead(); 호출
	while(!IsEmpty()) 
		delete RemovedHead();
}
void CLwyLinkedList::AddTail( CLwyNode *n)
{
	if ( IsEmpty() )
		AddHead(n);
	else {
		CLwyNode *p = GetTail();
		p->addNext(n);
	}
}
CLwyNode* CLwyLinkedList::FindNodePriority(int n)
{
	CLwyNode *p = GetHead(); // 반환할 헤드 포인터를 가장 첫번째 노드를 지정
	while ( 1 ) {
		if ( p->getOrder() == n ) // 받아들인 정수형 변수와 클래스가 가지고 있던 변수와 같느냐
			break;
		p = p->Next();
	}
	return p;
}
void CLwyLinkedList::DeleteHead() // 반환형 ch로
{
	CLwyNode *p = RemovedHead(); // 노드 포인터가 리스트의 헤드를 가리키게 함
	if (p == NULL) return; // IsEmpty일 경우 예외처리
	delete p; // 메모리 해제
}
void CLwyLinkedList::Delete( CLwyNode *n)
{
	CLwyNode *p = FindPrev(n); // 지우려는 노드의 앞을 이전 노드를 가리키고 난 후
	p->DeleteNext(); // 그 노드의 link를 지워줍니다.
}
CLwyNode* CLwyLinkedList::FindPrev(CLwyNode *n)
{
	if(IsEmpty() || n == GetHead()) return &m_org; // 공백이거나 그냥 n이 헤드를 가리킬 떄는 헤드노드 그냥 반환
	CLwyNode *p = GetHead(); // 임시 포인터 노드 생성, Head를 받게 함
	while ( p->Next() != n ) { // p의 링크가 다음 노드를 가리킬 경우 반복문을 끝냄
		p = p->Next();  // 포인터 링크를 따라 이동
	}
	return p;
}
void CLwyLinkedList::Merge( CLwyLinkedList &h) // 헤드노드를 매개변수로 받습니다.
{	
	CLwyNode *p = GetTail(); // 임시로 노드포인터를 기존 헤드노드의 꼬리를 가리키도록 함
	CLwyNode *q = h.GetHead(); // 임시 노드포인터를 만들어 매개변수로 받아온 리스트의 헤드를 받음
	
	p->setLink(q); // 새로 받아온 리스트의 헤드를 기존 리스트의 tail에 연결
	h.Clear(); // 받아온 헤드노드를 초기화
}
