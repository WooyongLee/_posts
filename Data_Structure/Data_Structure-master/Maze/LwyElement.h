#pragma once
#include <stdio.h>

struct CPoint2D{
	int m_x;
	int m_y;
};
typedef CPoint2D CPoint2D;

class CLwyElement
{
protected :
	CPoint2D cp;
public:
	CLwyElement() { cp.m_x = 0, cp.m_y = 0; }
	CLwyElement( int xx , int yy ) { setElement(xx, yy); } // 매개변수가 있는 생성자
	~CLwyElement(void)	{	}
	CPoint2D getElement() { return cp; }
	int getX() { return cp.m_x; }
	int getY() { return cp.m_y; }
	void setElement(int x, int y) {
		if ( (x >= 0) && ( y >= 0 ) ) { // 배열의 크기는 0보다 커야하기 떄문에 예외처리
			cp.m_x = x;
			cp.m_y = y;
		}
		else { 
			cp.m_x = -1;
			cp.m_y = -1;
		}
	}
	CPoint2D ResetElement();
	void Display() { printf("(%d, %d)",cp.m_x, cp.m_y); }
	CPoint2D getNorthpoint(); //북쪽으로 이동
	CPoint2D getWestpoint();
	CPoint2D getSouthpoint();
	CPoint2D getEastpoint();
};

CPoint2D CLwyElement::getNorthpoint()
{
	cp.m_x--;
	return cp;
}
CPoint2D CLwyElement::getWestpoint()
{
	cp.m_y--;
	return cp;
}
CPoint2D CLwyElement::getSouthpoint()
{
	cp.m_x++;
	return cp;
}
CPoint2D CLwyElement::getEastpoint()
{
	cp.m_y++;
	return cp;
}
CPoint2D CLwyElement::ResetElement()
{
	cp.m_x = 00;
	cp.m_y = 0; 
	return cp; 
}