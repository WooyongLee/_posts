#pragma once
#include "LwyDNode.h"
class CLwyDLinkedList
{
	CLwyDNode m_org;
public:
	CLwyDLinkedList() {	} // 생성자와 소멸자 정의  
	~CLwyDLinkedList(void) { /*Clear();*/ }  // 소멸하면서 Clear 
	//기본함수
	CLwyDNode* GetHead() { return m_org.GetNext(); } // Head를 반환 
	bool IsEmpty( ) { return GetHead() == NULL; } // 공백 리스트 확인 
	CLwyDNode* GetTail(); // Tail을 반환 
	int GetLength(); // Display 함수에서 리스트의 길이를 반환하기 위해 사용 
	void Display(char *); // 출력함수 
	//CLwyLinkedList클래스의 삽입함수들
	void AddHead( CLwyDNode *n) { m_org.AddNext(n); } // 링크를 따라 다음 노드를 n으로 줌
	void AddTail( CLwyDNode *n); 
	void AddNext( CLwyDNode *p, CLwyDNode *n ) { p->AddNext(n); }
	//CLwyLinkedList클래스의 삭제함수들
	void DeleteHead(); // Head를 가리키는 노드 하나 삭제
	void Delete( CLwyDNode *n); // n 노드 삭제
	void DeleteTail(); // 구현!
	void Clear(); // 리스트 초기화
	//CLwyLinkedList크래스의 탐색함수들
	CLwyDNode* FindNodePriority(int ); // 노드의 순번을 받아서 노드 반환
	CLwyDNode* FindPrev(CLwyDNode *); // 이전 노드를 찾는 함수
	//기타 함수들
	void Merge( CLwyDLinkedList &); // List1 + List2 => List1 ,, List2 날려버림
	//출력 함수
	void DisplayRev(char *); //  거꾸로 출력(실제순서변경x) 반복
	void DisplayRevRecur(char *); // 거꾸로 출력(실제순서변경x) 재귀
};
CLwyDNode* CLwyDLinkedList::GetTail()
{
	if (IsEmpty()) return &m_org; // 예외처리, 공백일 때 연산 불가
	CLwyDNode* tail = &m_org;
	for ( ; tail->GetNext() != NULL; tail = tail->GetNext() );
	return tail;
} // 리스트의 tail 반환
int CLwyDLinkedList::GetLength()
{
	int count = 0;
	for ( CLwyDNode* p = GetHead() ; p!= NULL ; p=p->GetNext() ) 
		count++;
	return count;
}// 리스트 항목갯수 반환
void CLwyDLinkedList::Display(char* s)
{
	printf("[%s 의 전체 항목 수 = %2d]\n", s, GetLength());
	for ( CLwyDNode *p = GetHead() ; p != NULL ; p = p->GetNext() )
		p->Display();
	printf("\n");
}
void CLwyDLinkedList::Clear()
{
	for ( CLwyDNode *p = GetHead() ; p != NULL ; p = p->GetNext()) 
		p->Remove();
} 
void CLwyDLinkedList::AddTail( CLwyDNode *n)
{
	if ( IsEmpty() ) // 공백일 경우
		AddHead(n); // 그냥 헤드에다가 받아온 노드를 넣습니다.
	else {
		CLwyDNode *p = GetTail();
		p->AddNext(n);
	}
}
CLwyDNode* CLwyDLinkedList::FindNodePriority(int n)
{
	CLwyDNode *p = GetHead(); // 반환할 헤드 포인터를 가장 첫번째 노드를 지정
	while ( 1 ) {
		if ( p->getOrder() == n ) // 받아들인 정수형 변수와 클래스가 가지고 있던 변수와 같느냐
			break;
		p = p->GetNext();
	}
	return p;
}
void CLwyDLinkedList::DeleteHead() // 반환형 ch로
{
	Delete(GetHead());
}
void CLwyDLinkedList::Delete( CLwyDNode *n)
{
	n->Remove(); // 그 노드의 link를 지워줍니다.
	delete n; // 메모리 해제
}
void CLwyDLinkedList::DeleteTail()
{
	Delete(GetTail()); // tail부분을 바로 Delete
}
CLwyDNode* CLwyDLinkedList::FindPrev(CLwyDNode *n)
{
	if(IsEmpty() || n == GetHead()) return &m_org; // 공백이거나 그냥 n이 헤드를 가리킬 떄는 헤드노드 그냥 반환
	CLwyDNode *p = GetHead(); // 임시 포인터 노드 생성, Head를 받게 함
	while ( p->GetNext() != n ) { // p의 링크가 다음 노드를 가리킬 경우 반복문을 끝냄
		p = p->GetNext();  // 포인터 링크를 따라 이동
	}
	return p;
}
void CLwyDLinkedList::Merge( CLwyDLinkedList &h) // 헤드노드를 매개변수로 받습니다.
{	
	CLwyDNode *p = GetTail(); // 임시로 노드포인터를 기존 헤드노드의 꼬리를 가리키도록 함
	CLwyDNode *q = h.GetHead(); // 임시 노드포인터를 만들어 매개변수로 받아온 리스트의 헤드를 받음
	
	p->SetNext(q); // 기존의 리스트의 tail을 새로받아온 리스트의 head와 연결
	q = p->GetPrev(); // 새로 받아온 리스트의 prev링크를 리스트의 tail로 연결
	h.Clear(); // 받아온 헤드노드를 초기화
}
void CLwyDLinkedList::DisplayRev(char *s)
{
	printf("%s\n" , s);
	CLwyDNode *p = GetTail(); // tail을 임시로 받음
	for (  ; p->GetPrev() != NULL ; p=p->GetPrev() )  // prev가 NULL을 가리킬 때 까지 반복
		p->Display(); // 그대로 출력
}
void CLwyDLinkedList::DisplayRevRecur(char *s)
{
	printf("%s\n", s);
	CLwyDNode *p = GetHead();// Head를 임시로 받고
	p->DisplayRevRecur(); // Node클래스의 ReCur함수를 호출하도록 함니다.
}