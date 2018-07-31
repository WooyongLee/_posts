#pragma once
#include "LwyTNode.h"
class CLwyBSTree
{
	CLwyTNode* m_root; // 루트를 가리키는 노드포인터
public:
	CLwyBSTree(void) { m_root = NULL; }
	~CLwyBSTree(void) { if( m_root != NULL ) delete m_root;}  // root가 비어있지 않다면 메모리 해제

	void PrintPreOrder();
	void PrintInOrder();
	void PrintPostOrder();
	void Add( CLwyTNode *n );
	
	void SearchPriority( int  ); // 아이템의 킷값으로 검색하여 검색된 아이템의 전체정보를 출력하는 함수
	void SearchPriceRange( int, int );
	int GetHeight() { return m_root->GetHeight(m_root); }
	int GetCount() { return m_root->GetCount(m_root); }

};

void CLwyBSTree::PrintPreOrder()
{
	printf("트리내용출력-PreOrder : \n\n" );
	if (m_root != NULL ) m_root->PreOrder(); // m_root가 NULL일 경우 프로그램을 수행할 수 없음
}
void CLwyBSTree::PrintInOrder()
{
	printf("트리내용출력-InOrder : \n\n" );
	if (m_root != NULL ) m_root->InOrder(); // m_root가 NULL일 경우 프로그램을 수행할 수 없음
}
void CLwyBSTree::PrintPostOrder()
{
	printf("트리내용출력-PostOrder : \n\n" );
	if (m_root != NULL ) m_root->PostOrder(); // m_root가 NULL일 경우 프로그램을 수행할 수 없음
}
void CLwyBSTree::Add( CLwyTNode *n )
{
	if ( n == NULL ) return; // 들어온 노드가 NULL일 경우, 아무 것도 수행할 수 없음
	if ( m_root == NULL ) m_root = n; // m_root가 NULL, 조상님노드가 아예 없음
	else m_root->AddNode( n );
}
void CLwyBSTree::SearchPriority( int order )
{
	if ( order == NULL )  // 들어온 우선순위값(order)검사
		printf("노드에 입력한 order값 %d가(이) 잘못 되었습니다.\n", order);

	printf("<재귀>\n");
	CLwyTNode *n = m_root; // 임시로 노드하나를 만듬, root로 지정
	if ( m_root == NULL )
		n = NULL; // 원래 트리의 루트가 NULL일 경우 TNode도 NULL로 지정 
	else
		n = m_root->SearchPriorityRecur(order); // n을 통해 TNode의 재귀 탐색 함수 호출함

	if ( n == NULL ) 		printf("노드에 입력한 priority값 %d가(이) 없습니다.\n", order);
	else					n->Display();

	printf("<반복>\n");
	n = m_root; // 임시 포인터 n 다시 root로 초기화
	n->SearchPriorityRev(n, order); // n을 통해 TNode의 반복적인 탐색 함수 호출
}
void CLwyBSTree::SearchPriceRange( int min , int max)
{
	if ( m_root != NULL ) // 공백트리가 아닐 때 
		m_root->SearchPriceRange(min, max);//함수호출
}