
#include "LwyPoly.h"
void main()
{

	printf("\n************* [ 2015년도 2학기 자료구조 실습과제 3 ] *************\n\n");
	printf("                         1. 다항식 계산\n\n");

	CLwyPoly a, b, c, d;
	a.Read(); // 첫 번째 다항식을 입력 받음
	b.Read(); // 두 번째 다항식을 입력 받음

	printf("\n******************************************************************\n\n");

	a.Print("    Print(A) = ");
	b.Print("    Print(B) = ");

	a.Print2("   Print2(A) = ");
	b.Print2("   Print2(B) = ");
	

	c.Add (a, b); // 두 다항식의 합을 계산
	c.Print2("      A + B  = ");
	c.Trim();
	c.Print2(" Trim(A + B) = ");

	d.Mult (a, b); // 두 다항식의 합을 계산
	d.Print2("      A * B  = ");
	d.Trim();
	d.Print2(" Trim(A * B) = ");
	getchar();
	getchar();
}