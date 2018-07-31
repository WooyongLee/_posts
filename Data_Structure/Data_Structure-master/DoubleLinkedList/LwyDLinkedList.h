#pragma once
#include "LwyDNode.h"
class CLwyDLinkedList
{
	CLwyDNode m_org;
public:
	CLwyDLinkedList() {	} // �����ڿ� �Ҹ��� ����  
	~CLwyDLinkedList(void) { /*Clear();*/ }  // �Ҹ��ϸ鼭 Clear 
	//�⺻�Լ�
	CLwyDNode* GetHead() { return m_org.GetNext(); } // Head�� ��ȯ 
	bool IsEmpty( ) { return GetHead() == NULL; } // ���� ����Ʈ Ȯ�� 
	CLwyDNode* GetTail(); // Tail�� ��ȯ 
	int GetLength(); // Display �Լ����� ����Ʈ�� ���̸� ��ȯ�ϱ� ���� ��� 
	void Display(char *); // ����Լ� 
	//CLwyLinkedListŬ������ �����Լ���
	void AddHead( CLwyDNode *n) { m_org.AddNext(n); } // ��ũ�� ���� ���� ��带 n���� ��
	void AddTail( CLwyDNode *n); 
	void AddNext( CLwyDNode *p, CLwyDNode *n ) { p->AddNext(n); }
	//CLwyLinkedListŬ������ �����Լ���
	void DeleteHead(); // Head�� ����Ű�� ��� �ϳ� ����
	void Delete( CLwyDNode *n); // n ��� ����
	void DeleteTail(); // ����!
	void Clear(); // ����Ʈ �ʱ�ȭ
	//CLwyLinkedListũ������ Ž���Լ���
	CLwyDNode* FindNodePriority(int ); // ����� ������ �޾Ƽ� ��� ��ȯ
	CLwyDNode* FindPrev(CLwyDNode *); // ���� ��带 ã�� �Լ�
	//��Ÿ �Լ���
	void Merge( CLwyDLinkedList &); // List1 + List2 => List1 ,, List2 ��������
	//��� �Լ�
	void DisplayRev(char *); //  �Ųٷ� ���(������������x) �ݺ�
	void DisplayRevRecur(char *); // �Ųٷ� ���(������������x) ���
};
CLwyDNode* CLwyDLinkedList::GetTail()
{
	if (IsEmpty()) return &m_org; // ����ó��, ������ �� ���� �Ұ�
	CLwyDNode* tail = &m_org;
	for ( ; tail->GetNext() != NULL; tail = tail->GetNext() );
	return tail;
} // ����Ʈ�� tail ��ȯ
int CLwyDLinkedList::GetLength()
{
	int count = 0;
	for ( CLwyDNode* p = GetHead() ; p!= NULL ; p=p->GetNext() ) 
		count++;
	return count;
}// ����Ʈ �׸񰹼� ��ȯ
void CLwyDLinkedList::Display(char* s)
{
	printf("[%s �� ��ü �׸� �� = %2d]\n", s, GetLength());
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
	if ( IsEmpty() ) // ������ ���
		AddHead(n); // �׳� ��忡�ٰ� �޾ƿ� ��带 �ֽ��ϴ�.
	else {
		CLwyDNode *p = GetTail();
		p->AddNext(n);
	}
}
CLwyDNode* CLwyDLinkedList::FindNodePriority(int n)
{
	CLwyDNode *p = GetHead(); // ��ȯ�� ��� �����͸� ���� ù��° ��带 ����
	while ( 1 ) {
		if ( p->getOrder() == n ) // �޾Ƶ��� ������ ������ Ŭ������ ������ �ִ� ������ ������
			break;
		p = p->GetNext();
	}
	return p;
}
void CLwyDLinkedList::DeleteHead() // ��ȯ�� ch��
{
	Delete(GetHead());
}
void CLwyDLinkedList::Delete( CLwyDNode *n)
{
	n->Remove(); // �� ����� link�� �����ݴϴ�.
	delete n; // �޸� ����
}
void CLwyDLinkedList::DeleteTail()
{
	Delete(GetTail()); // tail�κ��� �ٷ� Delete
}
CLwyDNode* CLwyDLinkedList::FindPrev(CLwyDNode *n)
{
	if(IsEmpty() || n == GetHead()) return &m_org; // �����̰ų� �׳� n�� ��带 ����ų ���� ����� �׳� ��ȯ
	CLwyDNode *p = GetHead(); // �ӽ� ������ ��� ����, Head�� �ް� ��
	while ( p->GetNext() != n ) { // p�� ��ũ�� ���� ��带 ����ų ��� �ݺ����� ����
		p = p->GetNext();  // ������ ��ũ�� ���� �̵�
	}
	return p;
}
void CLwyDLinkedList::Merge( CLwyDLinkedList &h) // ����带 �Ű������� �޽��ϴ�.
{	
	CLwyDNode *p = GetTail(); // �ӽ÷� ��������͸� ���� ������� ������ ����Ű���� ��
	CLwyDNode *q = h.GetHead(); // �ӽ� ��������͸� ����� �Ű������� �޾ƿ� ����Ʈ�� ��带 ����
	
	p->SetNext(q); // ������ ����Ʈ�� tail�� ���ι޾ƿ� ����Ʈ�� head�� ����
	q = p->GetPrev(); // ���� �޾ƿ� ����Ʈ�� prev��ũ�� ����Ʈ�� tail�� ����
	h.Clear(); // �޾ƿ� ����带 �ʱ�ȭ
}
void CLwyDLinkedList::DisplayRev(char *s)
{
	printf("%s\n" , s);
	CLwyDNode *p = GetTail(); // tail�� �ӽ÷� ����
	for (  ; p->GetPrev() != NULL ; p=p->GetPrev() )  // prev�� NULL�� ����ų �� ���� �ݺ�
		p->Display(); // �״�� ���
}
void CLwyDLinkedList::DisplayRevRecur(char *s)
{
	printf("%s\n", s);
	CLwyDNode *p = GetHead();// Head�� �ӽ÷� �ް�
	p->DisplayRevRecur(); // NodeŬ������ ReCur�Լ��� ȣ���ϵ��� �Դϴ�.
}