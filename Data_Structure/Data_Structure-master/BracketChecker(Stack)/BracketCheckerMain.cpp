#include "BracketChecker.h"
void main(){
	CBracketChecker checker;
	printf("Check1함수 실험\n");
	checker.Check("LwyStack.h");
	checker.Check("BracketChecker.h"); // 괄호닫기 문제가 발생함
	checker.Check("2012136096_이우용_1006.cpp");

	printf("Check2함수 실험\n");
	checker.Check2("BracketChecker.h");

	getchar();
	getchar();
}