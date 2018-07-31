#pragma once
#include "LwyTNode.h"
class CLwyBSTree
{
	CLwyTNode* m_root; // ��Ʈ�� ����Ű�� ���������
public:
	CLwyBSTree(void) { m_root = NULL; }
	~CLwyBSTree(void) { if( m_root != NULL ) delete m_root;}  // root�� ������� �ʴٸ� �޸� ����

	void PrintPreOrder();
	void PrintInOrder();
	void PrintPostOrder();
	void Add( CLwyTNode *n );
	
	void SearchPriority( int  ); // �������� Ŷ������ �˻��Ͽ� �˻��� �������� ��ü������ ����ϴ� �Լ�
	void SearchPriceRange( int, int );
	int GetHeight() { return m_root->GetHeight(m_root); }
	int GetCount() { return m_root->GetCount(m_root); }

};

void CLwyBSTree::PrintPreOrder()
{
	printf("Ʈ���������-PreOrder : \n\n" );
	if (m_root != NULL ) m_root->PreOrder(); // m_root�� NULL�� ��� ���α׷��� ������ �� ����
}
void CLwyBSTree::PrintInOrder()
{
	printf("Ʈ���������-InOrder : \n\n" );
	if (m_root != NULL ) m_root->InOrder(); // m_root�� NULL�� ��� ���α׷��� ������ �� ����
}
void CLwyBSTree::PrintPostOrder()
{
	printf("Ʈ���������-PostOrder : \n\n" );
	if (m_root != NULL ) m_root->PostOrder(); // m_root�� NULL�� ��� ���α׷��� ������ �� ����
}
void CLwyBSTree::Add( CLwyTNode *n )
{
	if ( n == NULL ) return; // ���� ��尡 NULL�� ���, �ƹ� �͵� ������ �� ����
	if ( m_root == NULL ) m_root = n; // m_root�� NULL, ����Գ�尡 �ƿ� ����
	else m_root->AddNode( n );
}
void CLwyBSTree::SearchPriority( int order )
{
	if ( order == NULL )  // ���� �켱������(order)�˻�
		printf("��忡 �Է��� order�� %d��(��) �߸� �Ǿ����ϴ�.\n", order);

	printf("<���>\n");
	CLwyTNode *n = m_root; // �ӽ÷� ����ϳ��� ����, root�� ����
	if ( m_root == NULL )
		n = NULL; // ���� Ʈ���� ��Ʈ�� NULL�� ��� TNode�� NULL�� ���� 
	else
		n = m_root->SearchPriorityRecur(order); // n�� ���� TNode�� ��� Ž�� �Լ� ȣ����

	if ( n == NULL ) 		printf("��忡 �Է��� priority�� %d��(��) �����ϴ�.\n", order);
	else					n->Display();

	printf("<�ݺ�>\n");
	n = m_root; // �ӽ� ������ n �ٽ� root�� �ʱ�ȭ
	n->SearchPriorityRev(n, order); // n�� ���� TNode�� �ݺ����� Ž�� �Լ� ȣ��
}
void CLwyBSTree::SearchPriceRange( int min , int max)
{
	if ( m_root != NULL ) // ����Ʈ���� �ƴ� �� 
		m_root->SearchPriceRange(min, max);//�Լ�ȣ��
}