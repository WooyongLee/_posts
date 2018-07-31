#pragma once
#include "lwyitem.h"
class CLwyDNode :
	public CLwyItem // 상속으로 item을 만들은게 있음
{
	CLwyDNode* m_prev; // 이전노드를 가리키는 포인터
	CLwyDNode* m_next; // 다음노드를 가리키는 포인터
public:
	CLwyDNode( char* name ="", int price = 0, int order = 0, char* memo = "")
		: CLwyItem(name, price, order, memo), m_prev(NULL), m_next(NULL) { } // 상속받은거 부르려면 초기화리스트ㅡ 호출
	~CLwyDNode(void) {	}

	//getter, setter
	CLwyDNode* GetPrev() { return m_prev; }
	CLwyDNode* GetNext() { return m_next; }
	void SetPrev(CLwyDNode *n) { m_prev = n; }
	void SetNext(CLwyDNode *n) { m_next = n; }
	// Add/Remove 함수
	void AddNext (CLwyDNode *n) {
		if( n != NULL ) { // n이 NULL인지아닌지 예외처ㅣㄹ
			n->m_prev = this; // 나의 주소로, n->SetPrev(this);
			n->m_next = m_next; // 나의 다음은 다음이다n->SetNext(m_next);
			if ( m_next != NULL )
				m_next->m_prev = n; // m_next=>SetPrev(n);
			m_next = n; // SetNext(n);
		}
	}
	void Remove () {
		if ( m_prev != NULL ) // m_prev->SetNext(m_next);
			m_prev->m_next = m_next;
		if ( m_next != NULL )
			m_next->m_prev = m_prev;
	}
	void DisplayRevRecur( ) {
		if ( GetNext() != NULL ) // 다음 노드가 NULL이 아니라면
			GetNext()->DisplayRevRecur(); // 다음노드에서 또 함수를 호출
		Display(); // 재귀가 모두 끝나면 출력을 하도록 함
	}
};