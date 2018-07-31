#pragma once //�ٸ� ���� ���ϵ��� #include �Ҷ� �ʿ���
#include <stdio.h>

const int MAX_DEGREE = 100;
class CLwyPoly
{
	int m_degree; // �ְ������� ����
	double coef[MAX_DEGREE]; // ���׽��� ���
public:
	CLwyPoly(void) : m_degree(0) {  } // ��� �ʱ�ȭ ����Ʈ
	~CLwyPoly(void) { } // �Ҹ���
	void Read();// ���׽��� ������ �Է¹޴�  �Լ�
	void Print( const char * ); // ���׽��� ������ ȭ�鿡 ����� �ִ� �Լ�
	void Print2( const char * );
	void Add(CLwyPoly &, CLwyPoly &);  //�� ���׽��� �����ִ� �Լ�
	void Mult(CLwyPoly&, CLwyPoly& ); // �� ���׽��� �����ִ� �Լ�
	void Trim(); // ���� ���׽��� �������ִ� �Լ�(�ְ������� ����� 0�̸� �ְ����� ����)
};
void CLwyPoly::Read()
{
	printf("���׽��� �ִ� ������ �Է��ϱ� >> ");
	scanf("%d", &m_degree); // �ִ����� �Է��� �޽��ϴ�.
	printf("�� ���� ����� �Է��Ͻÿ� (%d��)", m_degree + 1); // ����ױ��� + 1
	for ( int i = 0 ; i <= m_degree ; i++ )// ���׽��� �� ���� ����� �ϳ��ϳ� �б�
		scanf("%lf", &coef[i]); // m_coef + i
}
void CLwyPoly::Print( const char *msg )
{ // �Ű������� ���ڿ� 
	printf("%s", msg); // �޽����� ����ϱ�
	for ( int i = 0 ; i < m_degree ; i++ ) 
		printf("(%4.1fx^%d) + ", coef[i], m_degree - i); // �� �׵��� + �� �̾ ���
	printf("(%4.1lf)\n", coef[m_degree]); // ������ ���� ���� + ���� �ʿ� ��� �׳� ���
}

void CLwyPoly::Print2( const char *msg )
{
	printf("%s", msg); // �޽��� ���

	if ( m_degree > 0 ) {// �ִ� ������ 0���� Ŭ ���(�Ϲ����� ���)
		printf("%4.1lfx^%d", coef[0], m_degree); // ù��° ���� �״�� ����ϱ�
		for ( int i = 1 ; i < m_degree ; i++ ) {
			if ( coef[i] < 0 )  // ����� ������ ���
				printf(" - %4.1fx^%d", -coef[i], m_degree - i); // ���� '-' ���̰� �տ� ��������
			else if ( coef[i] == 0) // ����� 0�ΰ��� �ƿ� �ƹ��͵� ���� �ʵ��� �������.
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
	else if ( m_degree == 0 ) // ����׸� �ִ� ���
		printf("%4.1f\n", coef[m_degree]); // x ���� �׳� ����� ���
	else // ������ ������ ���
		printf("0\n"); // �׳� 0�� ����ϵ��� ��
}

void CLwyPoly::Add(CLwyPoly &a, CLwyPoly &b)// reference ���
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
	int i ,j; // �ݺ����� ���� ����
	m_degree = a.m_degree + b.m_degree; // �� ���׽��� ������ �� ������� �ְ������� �� ���׽��� �ְ������� ��
	for ( i = 0 ; i <= m_degree ; i++ )
		coef[i] = 0; // �� �μ� �ϴ� �ʱ�ȭ

	for ( i = 0 ; i <= a.m_degree ; i++ ) { // �ΰ��� �ݺ����� ���
		for ( j = 0 ; j <= b.m_degree ; j++ ) {
			coef[i+j] += a.coef[i] * b.coef[j]; // �� ���� ���� ��� �� �迭 ���ڿ� ���س���
		}
	}
}

void CLwyPoly::Trim()
{
	int i = 0;
	while ( coef[i] == 0 ) {
		if ( m_degree == 0 ) // ����ó��, ������ 0�� ��� 
			break;
		for ( i = 0 ; i < m_degree ; i++ ) //
			coef[i] = coef[i+1]; // ����� �� �迭�� �ϳ��� �о���
		m_degree -= 1;  // ������ �ϳ��� �ٿ���
	}
}