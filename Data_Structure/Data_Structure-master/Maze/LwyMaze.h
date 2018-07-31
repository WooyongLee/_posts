#pragma once
#include "LwyLinkedStack.h"
#include <fstream>
#include <windows.h>
class CLwyMaze
{
	int m_w; // �̷��� width
	int m_h; // �̷��� height
	int** m_maze; // �̷��� �� �׸��� ����
	CLwyLinkedStack m_stack; // �̷� Ž���� ���� ����
	CLwyElement m_start; 
	CLwyElement m_exit;	// ���������� �������� ��ǥ�� ������ �������
	char m_filename[200]; 
public :
	CLwyMaze(void) { Init(0,0); } 
	~CLwyMaze(void)	{ Reset(); 	} 
	int getM_w() { return m_w; }
	int getM_h() { return m_h; }
	void setM_w(int w) { m_w = w; }
	void setM_h(int h) { m_h = h; } // ������ ��� �����鿡 ���� setter, getter ����

	void Init(int , int );
	void Reset();
	void Load( char *);	
	void Print(); // ���������� ��

	void getStartpoint();
	void getExitpoint(); // �������� ������ ã�� ����
	void ErrorCheck(CPoint2D cp) { if ( ( cp.m_x < 0) || (cp.m_y < 0) )  return; }
	 // �迭�� ������ ����� �׳� return ��Ű���� �մϴ�
	void Push(CPoint2D ); // ���� ��ġ�� �˻��ؼ� ���ÿ� push
	void Pop(); // Stack���� Pop�ϴ� �Լ�

	void SearchExit(); // �̷�ã�⸦ ���� �Լ�
	bool CannotGo(); // �������� ���� ��ü������ �Ǻ����ִ� �Լ�
	bool EndCheck(); // ������ Ȯ���� �ִ� �Լ�
	void SearchFast(); // ���� ��θ� Ž�����ִ� �Լ�
};
void CLwyMaze::Init(int w, int h) 
{
	if ( (w < 0) || ( h < 0 ) ) // ����ó��
		return;
	setM_h(h); // ��ü�� ���̿ͳʺ� ���� ����
	setM_w(w); 
	m_maze = new int* [m_h + 2]; // �������� m_w +2 ��ŭ �Ҵ�
	for (int i = 0 ; i < m_h + 2; i++ ) // �������� m_w +2��ŭ �Ҵ�����ſ� m_h+2��ŭ �� �Ҵ����
		m_maze[i] = new int[m_w + 2]; // +2�� �ϴ� ������ �̷��� �ۿ� ���Ʒ������� �Ѱ� �� ���� �α� ���ؼ�
}
void CLwyMaze::Reset()
{
	if ( m_maze != NULL ) {
		for ( int i = 0 ; i < m_h + 2 ; i++ ) // �޾ƿ� ������ŭ ���� ����
			delete [] m_maze[i];
		delete m_maze;
	}
}
void CLwyMaze::Load( char *fname )
{
	int width = 0, height = 0;
	strcpy(m_filename, fname );
	FILE *fp = fopen(m_filename, "r"); // ������ ����ϴ�.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return;
	}

	fscanf( fp , "%d %d\n", &width, &height);

	Init(width, height); // �̷��� ��� ���� ũ�⸦ �����Ҵ����� ����
	
	for ( int i = 0 ; i < width + 2; i++ ) {
		m_maze[0][i] = 0; // (��)0���� �ʱ�ȭ
		m_maze[height+1][i] = 0;
	}
	for ( int i = 0 ; i < height + 2; i++ ) {
		m_maze[i][0] = 0;
		m_maze[i][width+1] = 0;
	}

	for ( int i = 1 ; i <= height ; i++ ) {
		for ( int j = 1 ; j <= width ; j++ ) { // ���� �� ����� �ݺ��� ����
			fscanf( fp, "%d ", &m_maze[i][j]);
		}
		fscanf( fp, "\n");
	}
	fclose(fp);
}
void CLwyMaze::Print() 
{
	//printf("%d �� %d ���� �̷��Դϴ�\n", m_w, m_h);
	for ( int i = 1 ; i <= m_h ; i++ ) {
		for ( int j = 1 ; j <= m_w ; j++ ) { // ���� �� ����� �ݺ��� ����
			switch ( m_maze[i][j] ) {
				case 0 : printf("��");  break;//��
				case 1 : printf("  ");  break; // ������ �� �ִ� ��
				case 5 : printf("��");  break; // �Ա�
				case 9 : printf("��");  break; // �ⱸ
				case 8 : printf("��");  break; // ������ġ
				case 2 : printf("��");  break; // ������ ��
				case 3 : printf("��");  break; // ���������µ� �� ������ �� 
			}								  // ->��������� �Ȱ��� ǥ����
		}
		printf("\n");
	}
}
void CLwyMaze::getStartpoint()
{
	for ( int i = 0 ; i < m_h + 2 ; i++ ) { // �̷��� �Ա� ã�� ����
		for ( int j = 0 ; j < m_w + 2 ; j++ ) { // �����Ҵ����� ���� �̷��� �� ��� ���� 2���� �� �޾ƿ����Ƿ� 2���� �ݺ�
			if (m_maze[i][j] == 5) {
				m_start.setElement(i, j); // �������� setter�� ���� �迭�� ���� �޾ƿ�
				break;
			}
		}
	}
}
void CLwyMaze::getExitpoint()
{
	for ( int i = 0 ; i < m_h + 2 ; i++ ) { // ����ǥ ���� ��� �� ���� +2��ŭ �Ҵ�������
		for ( int j = 0 ; j < m_w + 2 ; j++ ) { // �׸�ŭ �ݺ��ؼ� ����(9)�� ã�Ƽ�
			if ( m_maze[i][j] == 9) { // setter�� �̿��ؼ� m_exit�� �� �ֱ�
				m_exit.setElement(i, j);
				break;
			}
		}
	}
}
void CLwyMaze::Push(CPoint2D cp)  // x�� y��ǥ
{
	m_stack.Push(cp); // ���ÿ� Ǫ���ϵ���
	printf("Push >> (%d, %d)\n", m_stack.Peek().m_x, m_stack.Peek().m_y); // ������
}
void CLwyMaze::Pop()
{
	printf("Pop >> (%d, %d)\n", m_stack.Peek().m_x, m_stack.Peek().m_y); // ������
	m_stack.Pop();
}
bool CLwyMaze::CannotGo()
{
	if ( ( m_maze[m_start.getX() - 1][m_start.getY()] == 0 || m_maze[m_start.getX() - 1][m_start.getY()] == 2 || m_maze[m_start.getX() - 1][m_start.getY()] == 3) &&
		( m_maze[m_start.getX()][m_start.getY() - 1] == 0 || m_maze[m_start.getX()][m_start.getY() - 1] == 2 || m_maze[m_start.getX()][m_start.getY() - 1] == 3) &&
		 ( m_maze[m_start.getX() + 1][m_start.getY()] == 0 || m_maze[m_start.getX() + 1][m_start.getY()] == 2 || m_maze[m_start.getX() + 1][m_start.getY()] == 3 ) &&
		  ( m_maze[m_start.getX()][m_start.getY() + 1] == 0 || m_maze[m_start.getX()][m_start.getY() + 1] == 2 || m_maze[m_start.getX()][m_start.getY() + 1] == 3 ) )
		  return false; // ��, �� , �� , ���� ��� �����ְų� �̹� ���� ���� ���
	else
		return true;
}
void CLwyMaze::SearchExit()
{
	bool cannotChecking = true; // ������ �ִ��� �Ǻ����ִ� ����
	getStartpoint(); // ������ �������� ã���ݴϴ�.
	getExitpoint();
	while ( 1 ) {
		Print();
		system("cls"); 
		if ( cannotChecking == false ) { // ������ ���ٸ�,
			if ( m_maze[(m_start.getX() - 1)][m_start.getY()] == 2 ) { // �����̳� ���� ���� ���¿��� �Դ� ���� ������ ���
				ErrorCheck(m_start.getElement()); // �����ִ� ��ǥ�� üũ, �迭 ������ 0���� �������� ���� �ȵǴϱ�
				Pop(); // ������ Pop��
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 3; // ������ �� ǥ��, �ٽ� �������� ���� ���� 3���� ����
				m_start.getNorthpoint(); // �������� ��ǥ�� �ű�
			}
			else if ( m_maze[m_start.getX()][(m_start.getY() - 1)] == 2) { // ���� ���� ����
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 3;
				m_start.getWestpoint(); // �������� ��ǥ�� �ű�
			}
			else if ( m_maze[(m_start.getX() + 1)][m_start.getY()] == 2) { // ������ ���� ����
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 3;
				m_start.getSouthpoint();
			}
			else if ( m_maze[m_start.getX()][(m_start.getY()) + 1] == 2) { // ������ ���� ����
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 3;
				m_start.getEastpoint();
			}
		}
		else {  // cannotChecking = true �� ���, �� �� ���� �־ ��ǥ�� �̵��ؾ߰ڴٰ� �� ��
			if ( m_maze[(m_start.getX() - 1)][m_start.getY()] == 1 || m_maze[(m_start.getX() - 1)][m_start.getY()] == 9) {
				//������ ���� ����, ���� ����ġ�ų� �ⱸ�� ����ģ�ٸ�
				if ( (m_start.getElement().m_x == 1) || (m_start.getElement().m_y == 1) )
				ErrorCheck(m_start.getElement()); // ����üũ
				Push(m_start.getElement()); // m_start�� ��ǥ�� ��� Push
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 2; // ������ �� ǥ��
				m_start.getNorthpoint(); // �������� ��ǥ�� �ű�
			}
			else if ( m_maze[m_start.getX()][(m_start.getY() - 1)] == 1 || m_maze[m_start.getX()][(m_start.getY() - 1)] == 9) { // ���� ���� ����
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 2;
				m_start.getWestpoint();
			}
			else if ( m_maze[(m_start.getX() + 1)][m_start.getY()] == 1 || m_maze[(m_start.getX() + 1)][m_start.getY()] == 9) { // ������ ���� ����
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 2;
				m_start.getSouthpoint();
			}
			else if ( m_maze[m_start.getX()][(m_start.getY()) + 1] == 1 || m_maze[m_start.getX()][(m_start.getY()) + 1] == 9) { // ������ ���� ����
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 2;
				m_start.getEastpoint();
			}
		}
		if ( EndCheck() == true )  // �ݺ����� ��������
			break;
		Sleep(50);
		cannotChecking = CannotGo(); // �������� ���� üũ�ؼ� boolŸ���� ������ �־���
	}	
}
bool CLwyMaze::EndCheck()
{
	CPoint2D temp_start, temp_exit; // ��ǥ�� ���� ����ü ���� �ΰ��� ���� , ������ ������ ����������
	temp_start = m_start.getElement(); // �������� �ް�
	temp_exit = m_exit.getElement(); // ������ �޽��ϴ�.
	if ( (temp_start.m_x == temp_exit.m_x) && (temp_start.m_y == temp_exit.m_y) ) { // �������� �����̰��ٸ� true�� ��ȯ�մϴ�.
		printf("�̷�ã�Ⱑ �������ϴ�!!\n");//���� �������� ������ �����
		return true;
	}
	else
		return false; // ���̳��� ������ EndCheck�� false�� �Ǿ� ���� SearchExit�Լ��� while���� ��� ���ư�
}
void CLwyMaze::SearchFast()
{
	CPoint2D temp; // �ӽú��� ����
	for ( int k = 0 ; k < m_w*m_h ; k++ ) {
		temp = m_stack.Pop(); // �ӽú����� Stack�ؼ� Pop�� ��ǥ���� ����
		for ( int i = 0 ; i < m_h + 2 ; i++ ) {
			for ( int j = 0 ; j < m_w + 2 ; j++ ) { // �̷��� ��� ��ǥ���� �ݺ������� Ȯ��
				if ( (temp.m_x == i ) && (temp.m_y == j) ) 
					m_maze[i][j] = 8; // ��ǥ�� ���� Pop�Ͽ� return�� ��ǥ�� ������ 8(������θ� ǥ�����ִ� ��)�� ����
			}
		}
	}
}