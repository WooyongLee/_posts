#pragma once
#include <stdio.h>
#include <string.h>
class CLwyElement
{
	int element;
public:
	CLwyElement(void) { }//  { SetElement(e);}
//	CLwyElement(int e) : element(e) {}
	~CLwyElement(void) { }
	int GetElement() { return element; }
	void SetElement(int e) { element = e; } // element에 대한 setter와 getter 정의
	void print(void) { printf("%2d ", element); } // 출력문
};

