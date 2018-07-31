#pragma once //다른 많은 파일들이 #include 할때 필요함
#include <stdio.h>

const int MAX_DEGREE = 100;
class CLwyPoly
{
	int m_degree; // 최고차항의 지수
	double coef[MAX_DEGREE]; // 다항식의 계수
public:
	CLwyPoly(void) : m_degree(0) {  } // 멤버 초기화 리스트
	~CLwyPoly(void) { } // 소멸자
	void Read();// 다항식의 내용을 입력받는  함수
	void Print( const char * ); // 다항식의 내용을 화면에 출력해 주는 함수
	void Print2( const char * );
	void Add(CLwyPoly &, CLwyPoly &);  //두 다항식을 더해주는 함수
	void Mult(CLwyPoly&, CLwyPoly& ); // 두 다항식을 곱해주는 함수
	void Trim(); // 현재 다항식을 정리해주는 함수(최고차항의 계수가 0이면 최고차항 수정)
};
void CLwyPoly::Read()
{
	printf("다항식의 최대 차수를 입력하기 >> ");
	scanf("%d", &m_degree); // 최대차수 입력을 받습니다.
	printf("각 항의 계수를 입력하시오 (%d개)", m_degree + 1); // 상수항까지 + 1
	for ( int i = 0 ; i <= m_degree ; i++ )// 다항식의 각 항의 계수를 하나하나 읽기
		scanf("%lf", &coef[i]); // m_coef + i
}
void CLwyPoly::Print( const char *msg )
{ // 매개변수가 문자열 
	printf("%s", msg); // 메시지를 출력하구
	for ( int i = 0 ; i < m_degree ; i++ ) 
		printf("(%4.1fx^%d) + ", coef[i], m_degree - i); // 각 항들을 + 로 이어서 출력
	printf("(%4.1lf)\n", coef[m_degree]); // 마지막 항은 따로 + 붙일 필요 없어서 그냥 출력
}

void CLwyPoly::Print2( const char *msg )
{
	printf("%s", msg); // 메시지 출력

	if ( m_degree > 0 ) {// 최대 차항이 0보다 클 경우(일반적인 경우)
		printf("%4.1lfx^%d", coef[0], m_degree); // 첫번째 항은 그대로 출력하기
		for ( int i = 1 ; i < m_degree ; i++ ) {
			if ( coef[i] < 0 )  // 계수가 음수일 경우
				printf(" - %4.1fx^%d", -coef[i], m_degree - i); // 수에 '-' 붙이고 앞에 빼기해줌
			else if ( coef[i] == 0) // 계수가 0인경우는 아예 아무것도 하지 않도록 만들었다.
			{
			}
			else
				printf(" + %4.1fx^%d", coef[i], m_degree - i);
		}
		if ( coef[m_degree] < 0 ) 
			printf(" - %4.1f", -coef[m_degree]);
		else if ( coef[m_degree] == 0) 
		{
		}
		else
			printf(" + %4.1f", coef[m_degree]);
		printf("\n");
	}
	else if ( m_degree == 0 ) // 상수항만 있는 경우
		printf("%4.1f\n", coef[m_degree]); // x 없이 그냥 상수만 출력
	else // 차수가 음수일 경우
		printf("0\n"); // 그냥 0을 출력하도록 함
}

void CLwyPoly::Add(CLwyPoly &a, CLwyPoly &b)// reference 사용
{ 
	if (a.m_degree > b.m_degree) {
		*this = a;
		for ( int i = 0 ; i <= b.m_degree ; i++ )
			coef[i+(m_degree-b.m_degree)] += b.coef[i];
	}
	else {
		*this = b;
		for ( int i = 0 ; i <= a.m_degree ; i++ )
			coef[i+(m_degree-a.m_degree)] += a.coef[i];
	}
}

void CLwyPoly::Mult(CLwyPoly &a, CLwyPoly &b)
{
	int i ,j; // 반복문을 돌릴 변수
	m_degree = a.m_degree + b.m_degree; // 두 다항식을 곱했을 떄 결과값의 최고차항은 두 다항식의 최고차항의 합
	for ( i = 0 ; i <= m_degree ; i++ )
		coef[i] = 0; // 각 인수 일단 초기화

	for ( i = 0 ; i <= a.m_degree ; i++ ) { // 두개의 반복문을 사용
		for ( j = 0 ; j <= b.m_degree ; j++ ) {
			coef[i+j] += a.coef[i] * b.coef[j]; // 두 값의 곱을 계속 각 배열 인자에 더해나감
		}
	}
}

void CLwyPoly::Trim()
{
	int i = 0;
	while ( coef[i] == 0 ) {
		if ( m_degree == 0 ) // 예외처리, 지수가 0일 경우 
			break;
		for ( i = 0 ; i < m_degree ; i++ ) //
			coef[i] = coef[i+1]; // 계수를 앞 배열로 하나씩 밀어줌
		m_degree -= 1;  // 차수를 하나씩 줄여줌
	}
}