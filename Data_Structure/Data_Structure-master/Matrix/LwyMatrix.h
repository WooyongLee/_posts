#pragma once
#include <stdio.h>

class CLwyMatrix
{
	int m_rows; // ���� ����
	int m_cols; // ���� ����
	double **m_elem; // ����� �� �׸� ���� ����
public:
	CLwyMatrix(void) : m_rows(0), m_cols(0), m_elem(NULL) { } // ��� �ʱ�ȭ ����Ʈ
	~CLwyMatrix(void) { DeleteMem(); }
	void AllocMem( int , int ); // �޸� ���� �Ҵ����ִ� ����Լ�
	void DeleteMem(); // �޸�����
	void Read(); // �Է¹޴°�
	void Add( CLwyMatrix &, CLwyMatrix & );
	void Print(const char *);
};
void CLwyMatrix::AllocMem(int r, int c)
{
	if ( r <= 0 || c <= 0 ) 
		return; // ����ó��, �迭�� ũ�Ⱑ '-'�� �Ǵ� ���
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
	printf("����� ���Ǽ��� ���Ǽ��� �Է��Ͻÿ� : ");
	int r, c; // row, colm�� �Է¹޾� ��Ÿ���� ����
	scanf("%d%d", &r, &c);
	AllocMem(r, c); // ���� �޸𸮸� �Ҵ���
	printf("����� �� ���ڸ� �Է��Ͻÿ� ( �� %d ��)", r * c );
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
		printf("\n"); // ���� ����
	}
}
void CLwyMatrix::Add(CLwyMatrix &a, CLwyMatrix &b )
{
	// a�� b�� ���� ���� ũ�Ⱑ ���� ������ ����� ����
	if ( (a.m_rows != b.m_rows) || (a.m_cols != b.m_cols) ) return; 
	
	else { // �� ����� ũ�Ⱑ ���� ��� ������ ����
		AllocMem(a.m_rows, a.m_cols); // �ϴ� �迭�� �Ҵ� �� ����.
		m_rows = a.m_rows; // �� ����� ���� �� �� ���� ����� ��� ���� ũ��� 
		m_cols = a.m_cols; // ������ ����� ��� ���� ũ��� ����.
		for ( int i = 0 ; i < m_rows ; i++ )  { // ���� ������ŭ ������ ���� 
			for ( int j = 0 ; j < m_cols ; j++ ) { // ���� ������ŭ ������ �����Ͽ� ��� ��� ���� ���꿡 ���Եǵ��� �մϴ�.
				m_elem[i][j] = a.m_elem[i][j] + b.m_elem[i][j]; // �� ����� 0,0��° ���ں��� ��� ���� �ִ� ũ������� ���ڸ� ���� ��ü�� �־��ݴϴ�.
			}
		}
	}
}