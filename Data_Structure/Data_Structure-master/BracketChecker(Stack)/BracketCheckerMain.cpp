#include "BracketChecker.h"
void main(){
	CBracketChecker checker;
	printf("Check1�Լ� ����\n");
	checker.Check("LwyStack.h");
	checker.Check("BracketChecker.h"); // ��ȣ�ݱ� ������ �߻���
	checker.Check("2012136096_�̿��_1006.cpp");

	printf("Check2�Լ� ����\n");
	checker.Check2("BracketChecker.h");

	getchar();
	getchar();
}