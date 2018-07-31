#pragma once
#include "LwyStack.h"
#include <string.h>
class CBracketChecker
{
	CLwyStack m_st; // 스택을 구현한 클래스
	int m_nLine;
	int m_nChar;
	char m_filename[200]; // 파일 이름을 복사해다가 씀

public:
	CBracketChecker(void){ }
	~CBracketChecker(void) { }
	bool Check(char* );
	bool Check2(char* ); 
	void PrintResult();
};

bool CBracketChecker::Check(char *filename)
{
	strcpy(m_filename, filename ); // 문자열 복사연산
	FILE *fp = fopen (m_filename, "r"); // 파일을 열어봅니다.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return 0;
	}
	m_nLine = 1;
	m_nChar = 0;
	m_st.Reset();
	printf("[%s] 파일 검사결과\n" , m_filename);
	char ch;
	while ( (ch = getc(fp)) != EOF ) { // 파일의 끝까지
		m_nChar++; // 파일에 문자의 수를 하나 증가시킴
		if ( ch == '\n' ) m_nLine++; // 계행일 경우 Line수를 하나 증가시킴
		if ( ch == '[' || ch == '(' || ch == '{' ) m_st.Push(ch); // 여는괄호일경우
		else if ( ch == ']' || ch == ')' || ch == '}' ) {
			char prev = m_st.Pop();
			if ( ( (ch == ']')& (prev != '[') ) || ( (ch == '}') && (prev != '{') ) || ( (ch == ')') && (prev != '(' ) ) )  {
				break;
			}
		}
	}
	fclose(fp); // 파일 닫기
	PrintResult(); // 파일의 괄호 체크결과를 화면에 출력
	return m_st.IsEmpty();
}
bool CBracketChecker::Check2(char *filename)
{
	char ch;
	strcpy(m_filename, filename ); // 문자열 복사연산
	FILE *fp = fopen (m_filename, "r"); // 파일을 열어봅니다.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return 0;
	}
	m_nLine = 1;
	m_nChar = 0;
	m_st.Reset();
	printf("[%s] 파일 검사결과\n" , m_filename);
	while ( (ch = getc(fp)) != EOF ) { // 파일의 끝까지
		
		if ( ch == '\n' ) m_nLine++; // 계행일 경우 Line수를 하나 증가시킴
		m_nChar++; // 파일에 문자의 수를 하나 증가시킴

		if ( ch == 39 ) { // '의  아스키코드값 39
			while ( 1 ) {// 일경우 바로 반복문을 돌리고
				ch = getc(fp); // 거기에 대해 file에 있는 문자를 계속 get해서 ch에 집어넣음
				m_nChar++;
				if ( ch == 39 ) // 한번더 '가 나오면 루틴을 벗어남
					break;
			}
		}
		if ( ch == 34 ) { // "의 아스키코드 값 34 이용
			while ( 1 ) {
				ch = getc(fp);
				m_nChar++;
				if ( ch == 34 ) // 한번더 "가 나오면 루틴을 벗어남
					break;
			}
		}
		if ( ch == 47 ) { // 문자 / 의 아스키코드값 47
			ch = getc(fp);
			m_nChar++;
			if ( ch == 47 ) { // 두개의 /를 받아야함
				while ( 1 ) {
					ch = getc(fp);
					m_nChar++;
					if ( ch == '\n' ){ // 줄이 띄워주면 주석의 범위가 벗어나기 때문에 바로 반복문 탈출
						m_nLine++;
						break;
					}
				}
			}
			else if ( ch == 42 ) { // *의 아스키코드는 42
				while ( 1 ) {
					ch = getc(fp);
					m_nChar++; // 문자를 한개씩 증가시켜주는건 필수
					if ( ch == '\n' ) m_nLine++;
					if ( ch == 42 ) { // *를 받을경우
						ch = getc(fp);
						m_nChar++;
						if ( ch == 47 ) // */가 나올경우 바로 반복문 탈출
							break;
					}
				}
			} 
		}

		if ( ch == '[' || ch == '(' || ch == '{' )
			m_st.Push(ch); // 여는괄호일경우
		else if ( ch == ']' || ch == ')' || ch == '}' ) {
			char prev = m_st.Pop();
			if ( ( ch == ']' && prev != '[' ) || ( ch == '}' && prev != '{' ) || ( ch == ')' && prev != '(' )  ) break;
		}

	}
	fclose(fp); // 파일 닫기
	PrintResult(); // 파일의 괄호 체크결과를 화면에 출력
	return m_st.IsEmpty();
}
void CBracketChecker::PrintResult()
{
	if (m_st.IsEmpty()==false) // 스택이 비어있지 않고 인자가 남아있을 경우
		printf("Error (Line %d) : 괄호닫기 문제 발견\n\n", m_nLine++);	

	else {
		printf("파일의 라인개수 : %d\n", m_nLine);
		printf("파일의 문자개수 : %d\n\n", m_nChar);
	}
}