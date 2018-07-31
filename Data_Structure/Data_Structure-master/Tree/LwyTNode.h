#pragma once
#include <stdio.h>
#include "LwyItem.h"
int MAX(int num1, int num2) // �ִ밪�� ��ȯ�ϴ� �����Լ� ����
{
	return ( num1 > num2 ? num1 : num2 );
} // ���̸� ���ϴ� �Լ� getHeight()���� �ʿ���
class CLwyTNode : public CLwyItem
{
	CLwyTNode* m_left; // Ʈ���� left
	CLwyTNode* m_right; // Ʈ���� right
public: 
	CLwyTNode( int order = 0,  char* name ="", int price = 0, char* memo = "" )
		: CLwyItem(order, name, price, memo), m_left(NULL), m_right(NULL) { } // ��ӹ����� �θ����� �ʱ�ȭ����Ʈ�� ȣ��
	~CLwyTNode(void) {
		if ( m_left != NULL ) delete m_left;
		if ( m_right != NULL ) delete m_right;
	}

	CLwyTNode* GetLeft() { return m_left; }
	CLwyTNode* GetRight() { return m_right; }
	void SetLeft(CLwyTNode *n) { m_left = n; }
	void SetRight(CLwyTNode *n) { m_right = n; } // Getter, Setter ����
	
	void AddNode( CLwyTNode * );
	
	void PreOrder();
	void InOrder();
	void PostOrder();

	CLwyTNode* SearchPriorityRecur( int  ); // �������� Ŷ������ �˻��Ͽ� �˻��� �������� ��ü������ ����ϴ� �Լ�
	void SearchPriorityRev( CLwyTNode *, int );
	void SearchPriceRange( int, int );
	int GetHeight(CLwyTNode* );
	int GetCount(CLwyTNode* );

};
void CLwyTNode::PreOrder()
{ 
	Display();  // element class�� data���� ���� �������
	// ���� �ǽ����� element�� display�Լ��� �ҷ��ָ� ��
	if ( m_left != NULL ) m_left->PreOrder(); // ���ʾ� ���� �ڽ��� �ҷ���
	if ( m_right != NULL ) m_right->PreOrder(); // �����ʾ� ���� �ڽ��� �ҷ���
// �� �ڽĳ�尡 ���� �θ� �ڽĳ�尡 ���� ��쿡��, �ڽ��� NULL�� �ƴ� ��쿡��
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
	if ( n->m_order < m_order ) { // ������q�� ���� ���, ���� n�� ���� data���� ����
		if ( m_left == NULL )	m_left = n; // ���ʿ� ��� ���ٰ� ����
		else	m_left->AddNode( n ); // m_left���� �˾Ƽ� ������� ��Ŵ
	}
	else {
		if ( m_right == NULL )	m_right = n;
		else	m_right->AddNode( n );
	}
}
CLwyTNode* CLwyTNode::SearchPriorityRecur( int order )
{	
	if(order == m_order) // ���� �켱������ ���� ����� �켱�������� ���� ��� 
		return this;//	���� ��� �ٷ� ��ȯ

 	if(order > m_order) { // ���� �켱������ �� ���� ��� �θ��� ���� ��带 Ž��
		if (m_right == NULL) // Ž���� ���� ��尡 NULL�� ��� �׳� NULL ��ȯ
			return NULL;
		else // �Ϲ����� ���� ������忡�� �Լ��� ���ȣ����
			return m_right->SearchPriorityRecur(order);
	}
	else {	// (order < m_order) 
		if ( m_left == NULL ) // Ž���� ���� ��尡 NULL�� ��� �׳� NULL ��ȯ�� ��
			return NULL;
		else // ���� ��忡�� �Լ��� ��� ȣ���ϰ� ��
			return m_left->SearchPriorityRecur(order);
	}
}
void CLwyTNode::SearchPriorityRev( CLwyTNode *n, int order )
{
	bool tempSearch = false; // �ѹ��� ��ã�� ��� �׳� false��ȯ, Ž�� Ȯ�κ���
	while ( 1 ) {	// ���� ��尡 NULL���� �׻� Ȯ��
		if( order == n->getOrder() ) { // ���� �켱������ ������ �켱������ ���� ���
			n->Display(); // ����ϰ� ������ �������� �ݺ��� Ż��
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
		printf("��忡 �Է��� priority�� %d��(��) �����ϴ�.\n", order);
}
void CLwyTNode::SearchPriceRange( int minPrice, int maxPrice )
{
	if(m_price >= minPrice && m_price <= maxPrice) // price�� ���ǿ� �����ϸ�
		Display();
	if(m_left != NULL) m_left->SearchPriceRange(minPrice, maxPrice); 
	// tree�� ���� ���� �̵� �����ϸ� �� ��忡�� �Լ��� ���ȣ��
	if(m_right != NULL) m_right->SearchPriceRange(minPrice, maxPrice); 
	// tree�� ������ ���� �̵� �����ϸ� ������ ��忡�� �Լ��� ���ȣ��
	
}
int CLwyTNode::GetHeight(CLwyTNode *n)
{
	int height = 0; // �ӽø�� height ����
	if ( n != NULL )
		height = 1 + MAX(GetHeight(n->m_left), GetHeight(n->m_right));
	// height�� ����������, �������� �Լ��� ���ȣ���Ͽ� ���� ū ���� ��ȯ�Ͽ� ��Ʈ ��带 ���� ũ�⸦ ��ȯ
	return height;
}
int CLwyTNode::GetCount(CLwyTNode *n)
{
	int count = 0; // �ӽú��� count ����
	if ( n != NULL ) // ���� ��尡 NULL�� �ƴ��̻� 
		count = 1 + GetCount(n->m_left) + GetCount(n->m_right);
	// root��忡 ������ ,������ ���� ��� �Լ��� ��� ȣ���Ͽ� ���س���
	return count; 
}