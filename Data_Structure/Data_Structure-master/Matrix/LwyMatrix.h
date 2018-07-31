#pragma once
#include <stdio.h>

class CLwyMatrix
{
	int m_rows; // 행의 개수
	int m_cols; // 열의 개수
	double **m_elem; // 행렬의 각 항목 값을 저장
public:
	CLwyMatrix(void) : m_rows(0), m_cols(0), m_elem(NULL) { } // 멤버 초기화 리스트
	~CLwyMatrix(void) { DeleteMem(); }
	void AllocMem( int , int ); // 메모리 공간 할당해주는 멤버함수
	void DeleteMem(); // 메모리해제
	void Read(); // 입력받는거
	void Add( CLwyMatrix &, CLwyMatrix & );
	void Print(const char *);
};
void CLwyMatrix::AllocMem(int r, int c)
{
	if ( r <= 0 || c <= 0 ) 
		return; // 예외처리, 배열의 크기가 '-'가 되는 경우
	else
		{
			m_rows = r;
			m_cols = c;
			m_elem = new double* [ m_rows ];
			for ( int i = 0 ; i < m_rows ; i++ )
				m_elem[i] = new double [m_cols];
		}
}
void CLwyMatrix::DeleteMem()
{
	if ( m_elem != NULL ) {
		for ( int i = 0 ; i < m_rows ; i++ ) 
			delete [] m_elem[i];
		delete [] m_elem;
	}
}
void CLwyMatrix::Read()
{
	printf("행렬의 행의수와 열의수를 입력하시오 : ");
	int r, c; // row, colm를 입력받아 나타내는 변수
	scanf("%d%d", &r, &c);
	AllocMem(r, c); // 실제 메모리를 할당함
	printf("행렬의 각 인자를 입력하시오 ( 총 %d 개)", r * c );
	for ( int  i = 0 ; i < r ; i++ ) {
		for ( int j = 0 ; j < c ; j++ ) 
			scanf("%lf", &(m_elem[i][j])); // &(m_coef[i])
	}
}
void CLwyMatrix::Print(const char *msg = "Matrix = ")
{
	printf("%s [%d x %d]\n", msg, m_rows, m_cols);
	for ( int i = 0 ; i < m_rows ; i++ ) {
		for ( int j = 0 ; j < m_cols ; j++ )
			printf("%4.1lf", m_elem[i][j]);
		printf("\n"); // 계행 탭탭
	}
}
void CLwyMatrix::Add(CLwyMatrix &a, CLwyMatrix &b )
{
	// a와 b의 열과 행의 크기가 같지 않으면 계산을 못함
	if ( (a.m_rows != b.m_rows) || (a.m_cols != b.m_cols) ) return; 
	
	else { // 두 행렬의 크기가 같을 경우 연산을 수행
		AllocMem(a.m_rows, a.m_cols); // 일단 배열을 할당 해 놓음.
		m_rows = a.m_rows; // 두 행렬의 합을 한 후 나온 행렬의 행과 열의 크기는 
		m_cols = a.m_cols; // 연산한 행렬의 행과 열의 크기와 같다.
		for ( int i = 0 ; i < m_rows ; i++ )  { // 행의 갯수만큼 연산을 수행 
			for ( int j = 0 ; j < m_cols ; j++ ) { // 열의 갯수만큼 연산을 수행하여 모든 행과 열이 연산에 포함되도록 합니다.
				m_elem[i][j] = a.m_elem[i][j] + b.m_elem[i][j]; // 두 행렬의 0,0번째 인자부터 행과 열의 최대 크기까지의 인자를 더해 객체에 넣어줍니다.
			}
		}
	}
}