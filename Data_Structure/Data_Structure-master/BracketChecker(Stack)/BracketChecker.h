#pragma once
#include "LwyStack.h"
#include <string.h>
class CBracketChecker
{
	CLwyStack m_st; // ������ ������ Ŭ����
	int m_nLine;
	int m_nChar;
	char m_filename[200]; // ���� �̸��� �����شٰ� ��

public:
	CBracketChecker(void){ }
	~CBracketChecker(void) { }
	bool Check(char* );
	bool Check2(char* ); 
	void PrintResult();
};

bool CBracketChecker::Check(char *filename)
{
	strcpy(m_filename, filename ); // ���ڿ� ���翬��
	FILE *fp = fopen (m_filename, "r"); // ������ ����ϴ�.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return 0;
	}
	m_nLine = 1;
	m_nChar = 0;
	m_st.Reset();
	printf("[%s] ���� �˻���\n" , m_filename);
	char ch;
	while ( (ch = getc(fp)) != EOF ) { // ������ ������
		m_nChar++; // ���Ͽ� ������ ���� �ϳ� ������Ŵ
		if ( ch == '\n' ) m_nLine++; // ������ ��� Line���� �ϳ� ������Ŵ
		if ( ch == '[' || ch == '(' || ch == '{' ) m_st.Push(ch); // ���°�ȣ�ϰ��
		else if ( ch == ']' || ch == ')' || ch == '}' ) {
			char prev = m_st.Pop();
			if ( ( (ch == ']')& (prev != '[') ) || ( (ch == '}') && (prev != '{') ) || ( (ch == ')') && (prev != '(' ) ) )  {
				break;
			}
		}
	}
	fclose(fp); // ���� �ݱ�
	PrintResult(); // ������ ��ȣ üũ����� ȭ�鿡 ���
	return m_st.IsEmpty();
}
bool CBracketChecker::Check2(char *filename)
{
	char ch;
	strcpy(m_filename, filename ); // ���ڿ� ���翬��
	FILE *fp = fopen (m_filename, "r"); // ������ ����ϴ�.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return 0;
	}
	m_nLine = 1;
	m_nChar = 0;
	m_st.Reset();
	printf("[%s] ���� �˻���\n" , m_filename);
	while ( (ch = getc(fp)) != EOF ) { // ������ ������
		
		if ( ch == '\n' ) m_nLine++; // ������ ��� Line���� �ϳ� ������Ŵ
		m_nChar++; // ���Ͽ� ������ ���� �ϳ� ������Ŵ

		if ( ch == 39 ) { // '��  �ƽ�Ű�ڵ尪 39
			while ( 1 ) {// �ϰ�� �ٷ� �ݺ����� ������
				ch = getc(fp); // �ű⿡ ���� file�� �ִ� ���ڸ� ��� get�ؼ� ch�� �������
				m_nChar++;
				if ( ch == 39 ) // �ѹ��� '�� ������ ��ƾ�� ���
					break;
			}
		}
		if ( ch == 34 ) { // "�� �ƽ�Ű�ڵ� �� 34 �̿�
			while ( 1 ) {
				ch = getc(fp);
				m_nChar++;
				if ( ch == 34 ) // �ѹ��� "�� ������ ��ƾ�� ���
					break;
			}
		}
		if ( ch == 47 ) { // ���� / �� �ƽ�Ű�ڵ尪 47
			ch = getc(fp);
			m_nChar++;
			if ( ch == 47 ) { // �ΰ��� /�� �޾ƾ���
				while ( 1 ) {
					ch = getc(fp);
					m_nChar++;
					if ( ch == '\n' ){ // ���� ����ָ� �ּ��� ������ ����� ������ �ٷ� �ݺ��� Ż��
						m_nLine++;
						break;
					}
				}
			}
			else if ( ch == 42 ) { // *�� �ƽ�Ű�ڵ�� 42
				while ( 1 ) {
					ch = getc(fp);
					m_nChar++; // ���ڸ� �Ѱ��� ���������ִ°� �ʼ�
					if ( ch == '\n' ) m_nLine++;
					if ( ch == 42 ) { // *�� �������
						ch = getc(fp);
						m_nChar++;
						if ( ch == 47 ) // */�� ���ð�� �ٷ� �ݺ��� Ż��
							break;
					}
				}
			} 
		}

		if ( ch == '[' || ch == '(' || ch == '{' )
			m_st.Push(ch); // ���°�ȣ�ϰ��
		else if ( ch == ']' || ch == ')' || ch == '}' ) {
			char prev = m_st.Pop();
			if ( ( ch == ']' && prev != '[' ) || ( ch == '}' && prev != '{' ) || ( ch == ')' && prev != '(' )  ) break;
		}

	}
	fclose(fp); // ���� �ݱ�
	PrintResult(); // ������ ��ȣ üũ����� ȭ�鿡 ���
	return m_st.IsEmpty();
}
void CBracketChecker::PrintResult()
{
	if (m_st.IsEmpty()==false) // ������ ������� �ʰ� ���ڰ� �������� ���
		printf("Error (Line %d) : ��ȣ�ݱ� ���� �߰�\n\n", m_nLine++);	

	else {
		printf("������ ���ΰ��� : %d\n", m_nLine);
		printf("������ ���ڰ��� : %d\n\n", m_nChar);
	}
}