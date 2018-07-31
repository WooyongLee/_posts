#pragma once
#include "LwyNode.h"
#include <string.h>

class CLwyLinkedStack
{
	CLwyNode m_org; // �����
public:
	CLwyLinkedStack(void) { } // ����Ʈ ������
	~CLwyLinkedStack(void) {  } // ���ÿ� �ƹ��͵� ������ ������ ��ȯ

	CLwyNode *GetHead() { return m_org.Next(); }
	bool IsEmpty() { return GetHead() == NULL; }   // ������ ����ִ��� Ȯ��, ��带 Ȯ���Ͽ� NULL���� �ƴ���
	void AddHead(CLwyNode *n) { m_org.addNext(n); } // Push
	CLwyNode* RemovedHead() { return m_org.RemoveNext(); }

	void Reset();
	void Clear();	
	
	int GetLength(); 
	void DisPlay();

	void Push(CPoint2D ); //  AddHead
	CPoint2D Pop();			//	RemovedHead();
	CPoint2D Peek();      //   GetHead
};
void CLwyLinkedStack::Clear()
{ // �ȿ��� RemovedHead(); ȣ��
	while(!IsEmpty()) 
		delete RemovedHead();
}
void CLwyLinkedStack::Reset()
{ 
	Clear();
	m_org.setLink(NULL);
}  // reset �ȿ� clear ȣ��
int CLwyLinkedStack::GetLength()
{
	int count = 0;
	//for ( int i = 0 ; i < max ; i++ )
	for ( CLwyNode* p = GetHead() ; p!= NULL ; p=p->Next() ) 
		count++;
	return count;
}// ����Ʈ �׸񰹼� ��ȯ
void CLwyLinkedStack::DisPlay()
{
	printf("[%d] ����", GetLength());  // ����Ʈ �׸񰹼� ���
	for ( CLwyNode* p = GetHead() ; p != NULL ; p = p->Next() ) 
		p->Display();
	printf("\n");
}
void CLwyLinkedStack::Push( CPoint2D cp )
{
	AddHead(new CLwyNode(cp)); // new�����ڸ� �̿��Ͽ� Node�� �������ʵ忡 �Ű������� ���� ���� �Ҵ� 
}

CPoint2D CLwyLinkedStack::Pop() // ��ȯ�� ch��
{
	CLwyNode *p = RemovedHead();
	if (p == NULL) return m_org.ResetElement(); // IsEmpty�� ���
	CPoint2D cp = p->getElement();
	delete p;
	return cp;
}
CPoint2D CLwyLinkedStack::Peek()
{
	CLwyNode *p = GetHead(); // GetHead�� �̿��Ͽ� Peek�Լ� ����
	if ( IsEmpty()) return m_org.ResetElement();
	return p->getElement();
}