#pragma once
#include <stdio.h>
class CLwyElement
{
protected :
	int m_element;
public:
	CLwyElement(int el = 0) : m_element(el) { }
	~CLwyElement(void) { }
	void setElement(int element) { this->m_element = element; }
	int getElement() {return m_element;}
	void Display() { printf("%d ", m_element); }
};

