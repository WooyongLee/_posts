#pragma once
#include <stdio.h>
class CLwyElement
{
protected :
	char m_char;
public:
	CLwyElement(char ch = 0) : m_char(ch) { }
	~CLwyElement(void) { }
	void setElement(char ch) { this->m_char = ch; }
	char getElement() {return m_char;}
	void Display() { printf("%c ", m_char); }
};


