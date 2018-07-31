#pragma once
#include "LwyItemNode.h"
class CLwyLinkedList
{
	CLwyNode m_org;
public:
	CLwyLinkedList() {	} // �����ڿ� �Ҹ��� ����  
	~CLwyLinkedList(void) { Clear(); }  // �Ҹ��ϸ鼭 Clear 
	//�⺻�Լ�
	CLwyNode* GetHead() { return m_org.Next(); } // Head�� ��ȯ 
	bool IsEmpty( ) { return GetHead() == NULL; } // ���� ����Ʈ Ȯ�� 
	CLwyNode* GetTail(); // Tail�� ��ȯ 
	int GetLength(); // Display �Լ����� ����Ʈ�� ���̸� ��ȯ�ϱ� ���� ��� 
	void Display(char *); // ����Լ� 
	CLwyNode *RemovedHead()   { return m_org.DeleteNext(); } // Head�� ����, Clear�Լ��� �����ϱ� ���� 
	//CLwyLinkedListŬ������ �����Լ���
	void AddHead( CLwyNode *n) { m_org.addNext(n); } // ��ũ�� ���� ���� ��带 n���� ��
	void AddTail( CLwyNode *n); 
	void AddNext( CLwyNode *p, CLwyNode *n ) { p->addNext(n); }
	//CLwyLinkedListŬ������ �����Լ���
	void DeleteHead(); // Head�� ����Ű�� ��� �ϳ� ����
	void Delete( CLwyNode *n); // n ��� ����
	void Clear(); // ����Ʈ �ʱ�ȭ
	//CLwyLinkedListũ������ Ž���Լ���
	CLwyNode* FindNodePriority(int ); // ����� ������ �޾Ƽ� ��� ��ȯ
	CLwyNode* FindPrev(CLwyNode *); // ���� ��带 ã�� �Լ�
	//��Ÿ �Լ���
	void Merge( CLwyLinkedList &); // List1 + List2 => List1 ,, List2 ��������
//	void Reverse(); 
};
CLwyNode* CLwyLinkedList::GetTail()
{
	if (IsEmpty()) return &m_org; // ����ó��, ������ �� ���� �Ұ�
	CLwyNode* tail = &m_org;
	for ( ; tail->Next() != NULL; tail = tail->Next() );
	return tail;
} // ����Ʈ�� tail ��ȯ
int CLwyLinkedList::GetLength()
{
	int count = 0;
	//for ( int i = 0 ; i < max ; i++ )
	for ( CLwyNode* p = GetHead() ; p!= NULL ; p=p->Next() ) 
		count++;
	return count;
}// ����Ʈ �׸񰹼� ��ȯ
void CLwyLinkedList::Display(char* s)
{
	printf("[%s �� ��ü �׸� �� = %2d]\n", s, GetLength());
	for ( CLwyNode *p = GetHead() ; p != NULL ; p = p->Next() )
		p->Display();
	printf("\n");
}
void CLwyLinkedList::Clear()
{ // �ȿ��� RemovedHead(); ȣ��
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
	CLwyNode *p = GetHead(); // ��ȯ�� ��� �����͸� ���� ù��° ��带 ����
	while ( 1 ) {
		if ( p->getOrder() == n ) // �޾Ƶ��� ������ ������ Ŭ������ ������ �ִ� ������ ������
			break;
		p = p->Next();
	}
	return p;
}
void CLwyLinkedList::DeleteHead() // ��ȯ�� ch��
{
	CLwyNode *p = RemovedHead(); // ��� �����Ͱ� ����Ʈ�� ��带 ����Ű�� ��
	if (p == NULL) return; // IsEmpty�� ��� ����ó��
	delete p; // �޸� ����
}
void CLwyLinkedList::Delete( CLwyNode *n)
{
	CLwyNode *p = FindPrev(n); // ������� ����� ���� ���� ��带 ����Ű�� �� ��
	p->DeleteNext(); // �� ����� link�� �����ݴϴ�.
}
CLwyNode* CLwyLinkedList::FindPrev(CLwyNode *n)
{
	if(IsEmpty() || n == GetHead()) return &m_org; // �����̰ų� �׳� n�� ��带 ����ų ���� ����� �׳� ��ȯ
	CLwyNode *p = GetHead(); // �ӽ� ������ ��� ����, Head�� �ް� ��
	while ( p->Next() != n ) { // p�� ��ũ�� ���� ��带 ����ų ��� �ݺ����� ����
		p = p->Next();  // ������ ��ũ�� ���� �̵�
	}
	return p;
}
void CLwyLinkedList::Merge( CLwyLinkedList &h) // ����带 �Ű������� �޽��ϴ�.
{	
	CLwyNode *p = GetTail(); // �ӽ÷� ��������͸� ���� ������� ������ ����Ű���� ��
	CLwyNode *q = h.GetHead(); // �ӽ� ��������͸� ����� �Ű������� �޾ƿ� ����Ʈ�� ��带 ����
	
	p->setLink(q); // ���� �޾ƿ� ����Ʈ�� ��带 ���� ����Ʈ�� tail�� ����
	h.Clear(); // �޾ƿ� ����带 �ʱ�ȭ
}
