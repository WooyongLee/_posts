#pragma once
#include "LwyElement.h"
#define MAX_LIST_SIZE 100
class CLwyArrayList
{
	CLwyElement m_data[MAX_LIST_SIZE];
	int m_len;
public:
	CLwyArrayList(void) { m_len = 0; }
	~CLwyArrayList(void) { }

	bool IsEmpty( ) { return m_len == 0; } // ���� ����Ʈ�� ��� ����Ʈ�� ���̴� 0
	bool IsFull( ) { return m_len == MAX_LIST_SIZE; } // ����Ʈ�� �ִ� ũ���� ���
	CLwyElement GetEntry(int pos) { return m_data[pos]; } 
	int GetLength() { return m_len; } // ���̿� ���� getter
	void Clear( ) { m_len = 0; } 
	void Replace(int pos, int e) { m_data[pos].SetElement(e); } // ���Ҹ� �����մϴ�.
	void Display(char *); // ���
	void Add(int , int ); // ����
	void AddTail(int e)  { Add(m_len , e); } // ����Ʈ�� �� �� ���� �߰�
	void AddHead(int e) { Add(0, e); } // ����Ʈ�� �� �տ� ���� �߰�
	int Remove(int pos); // ����
	int RemoveTail() { return Remove(m_len - 1); } // ����Ʈ�� ũ�⿡ - 1 ���� �迭 ������ ����Ʈ�� ���� ��
	int RemoveHead() { return Remove(0); } // ����Ʈ�� ó����ġ�� 0
};
void CLwyArrayList::Display(char *c) 
{
	printf("%s", c);
	printf("[��ü �׸��� �� : %2d] : ", m_len);
	for ( int i = 0 ; i < m_len ; i++ )
		printf("%5d ", m_data[i]);
	printf("\n");
}
void CLwyArrayList::Add(int pos, int e)
{
	if ( (!IsFull()) && (pos >= 0) ) {
		for ( int i = m_len ; i > pos ; i-- )
			m_data[i] = m_data[i-1]; // data�� �������� �ϳ��� �о��ݴϴ�.
		m_data[pos].SetElement(e);
		m_len += 1;
	}
}
int CLwyArrayList::Remove(int pos)
{
	if ( (0 <= pos) && (pos < m_len) ) { // ����Ʈ�� ó�� ��ġ 0���� ����Ʈ�� ũ�� 
		int elem = m_data[pos].GetElement(); // - 1(����Ʈ�� ������ ��ġ) ���� �������
		for( int i = pos + 1 ; i < m_len ; i++ )
			m_data[i-1] = m_data[i]; // data�� �������� �ϳ��� �Ű��ݴϴ�.
		m_len--;
		return elem;
	}
	else 
		printf("Error\n");
}
