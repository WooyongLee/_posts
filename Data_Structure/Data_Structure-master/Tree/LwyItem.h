#pragma once
#include <stdio.h>
#include <string.h>

class CLwyItem
{
protected :
	int m_order; // ����
	char m_name[40]; // ��ǰ�̸�
	int m_price; // ����
	char m_memo[40]; // �޸�
public:
	CLwyItem( int order = 0, char* name = " ", int price = 0, char* memo = " ") {
		m_order = order;
		strcpy(m_name, name);
		m_price = price;
		strcpy(m_memo, memo);
	}
	~CLwyItem(void) { }
	int getPrice() { return m_price; }
	char *getName() { return m_name; }
	int getOrder() { return m_order; }
	char *getMemo() { return m_memo; }
	bool IsSame( char* name, int price, int order, char* memo) { // �����׸����� �Ǻ��ϴ� �Լ�
		if ( (m_price == price) && (m_order == order) && 
			(strcmp(name,m_name) == 0) && (strcmp(memo, m_memo)) )
			return true;
		else
			return false;
	}
	void Display() { printf("[�켱����] : %4d [����] : %8d [����] : %10s [�޽���] : %8s\n",  m_order, m_price, m_name, m_memo); }
};


