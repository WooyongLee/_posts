#pragma once
#include <stdio.h>
#include "LwyItem.h"
int MAX(int num1, int num2) // 최대값을 반환하는 전역함수 정의
{
	return ( num1 > num2 ? num1 : num2 );
} // 높이를 구하는 함수 getHeight()에서 필요함
class CLwyTNode : public CLwyItem
{
	CLwyTNode* m_left; // 트리의 left
	CLwyTNode* m_right; // 트리의 right
public: 
	CLwyTNode( int order = 0,  char* name ="", int price = 0, char* memo = "" )
		: CLwyItem(order, name, price, memo), m_left(NULL), m_right(NULL) { } // 상속받은거 부르려면 초기화리스트ㅡ 호출
	~CLwyTNode(void) {
		if ( m_left != NULL ) delete m_left;
		if ( m_right != NULL ) delete m_right;
	}

	CLwyTNode* GetLeft() { return m_left; }
	CLwyTNode* GetRight() { return m_right; }
	void SetLeft(CLwyTNode *n) { m_left = n; }
	void SetRight(CLwyTNode *n) { m_right = n; } // Getter, Setter 정의
	
	void AddNode( CLwyTNode * );
	
	void PreOrder();
	void InOrder();
	void PostOrder();

	CLwyTNode* SearchPriorityRecur( int  ); // 아이템의 킷값으로 검색하여 검색된 아이템의 전체정보를 출력하는 함수
	void SearchPriorityRev( CLwyTNode *, int );
	void SearchPriceRange( int, int );
	int GetHeight(CLwyTNode* );
	int GetCount(CLwyTNode* );

};
void CLwyTNode::PreOrder()
{ 
	Display();  // element class의 data들을 먼저 출력해줌
	// 실제 실습때는 element의 display함수를 불러주면 됨
	if ( m_left != NULL ) m_left->PreOrder(); // 왼쪽아 너의 자식을 불러라
	if ( m_right != NULL ) m_right->PreOrder(); // 오른쪽아 너의 자식을 불러라
// 단 자식노드가 이후 부를 자식노드가 있을 경우에만, 자식이 NULL이 아닐 경우에만
}
void CLwyTNode::InOrder() 
{
	if ( m_left != NULL ) m_left->InOrder();
	Display();
	if ( m_right != NULL ) m_right->InOrder();
}
void CLwyTNode::PostOrder()
{
	if ( m_left != NULL ) m_left->InOrder();
	if ( m_right != NULL ) m_right->InOrder();
	Display();
}
void CLwyTNode::AddNode( CLwyTNode *n )
{
	if ( n->m_order < m_order ) { // 왼쪽으q로 들어가는 경우, 들어온 n이 기존 data보다 작음
		if ( m_left == NULL )	m_left = n; // 왼쪽에 노드 갖다가 넣음
		else	m_left->AddNode( n ); // m_left보고 알아서 넣으라고 시킴
	}
	else {
		if ( m_right == NULL )	m_right = n;
		else	m_right->AddNode( n );
	}
}
CLwyTNode* CLwyTNode::SearchPriorityRecur( int order )
{	
	if(order == m_order) // 들어온 우선순위가 현재 노드의 우선순위값이 같은 경우 
		return this;//	지금 노드 바로 반환

 	if(order > m_order) { // 들어온 우선순위가 더 높을 경우 부모의 우측 노드를 탐색
		if (m_right == NULL) // 탐색한 우측 노드가 NULL일 경우 그냥 NULL 반환
			return NULL;
		else // 일반적인 경우는 우측노드에서 함수를 재귀호출함
			return m_right->SearchPriorityRecur(order);
	}
	else {	// (order < m_order) 
		if ( m_left == NULL ) // 탐색한 좌측 노드가 NULL인 경우 그냥 NULL 반환케 함
			return NULL;
		else // 좌측 노드에서 함수를 재귀 호출하게 함
			return m_left->SearchPriorityRecur(order);
	}
}
void CLwyTNode::SearchPriorityRev( CLwyTNode *n, int order )
{
	bool tempSearch = false; // 한번도 못찾을 경우 그냥 false반환, 탐색 확인변수
	while ( 1 ) {	// 들어온 노드가 NULL인지 항상 확인
		if( order == n->getOrder() ) { // 받은 우선순위와 기존의 우선순위가 같은 경우
			n->Display(); // 출력하고 목적을 끝냈으니 반복문 탈출
			tempSearch = true;
			break;
		}
		else if ( order > n->getOrder() ) {
			if ( n->m_right == NULL )
				break;
			else
				n = n->m_right; 
		}
		else {
			if ( n->m_left == NULL ) 
				break;
			else
				n = n->m_left;
		}
	}
	if (tempSearch == false)
		printf("노드에 입력한 priority값 %d가(이) 없습니다.\n", order);
}
void CLwyTNode::SearchPriceRange( int minPrice, int maxPrice )
{
	if(m_price >= minPrice && m_price <= maxPrice) // price가 조건에 만족하면
		Display();
	if(m_left != NULL) m_left->SearchPriceRange(minPrice, maxPrice); 
	// tree의 왼쪽 노드로 이동 가능하면 왼 노드에서 함수를 재귀호출
	if(m_right != NULL) m_right->SearchPriceRange(minPrice, maxPrice); 
	// tree의 오른쪽 노드로 이동 가능하면 오른쪽 노드에서 함수를 재귀호출
	
}
int CLwyTNode::GetHeight(CLwyTNode *n)
{
	int height = 0; // 임시면수 height 선언
	if ( n != NULL )
		height = 1 + MAX(GetHeight(n->m_left), GetHeight(n->m_right));
	// height의 오른쪽으로, 왼쪽으로 함수를 재귀호출하여 그중 큰 수를 반환하여 루트 노드를 더한 크기를 반환
	return height;
}
int CLwyTNode::GetCount(CLwyTNode *n)
{
	int count = 0; // 임시변수 count 선언
	if ( n != NULL ) // 들어온 노드가 NULL이 아닌이상 
		count = 1 + GetCount(n->m_left) + GetCount(n->m_right);
	// root노드에 오른쪽 ,왼쪽의 노드로 계속 함수를 재귀 호출하여 더해나감
	return count; 
}