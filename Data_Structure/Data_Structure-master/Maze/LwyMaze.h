#pragma once
#include "LwyLinkedStack.h"
#include <fstream>
#include <windows.h>
class CLwyMaze
{
	int m_w; // 미로의 width
	int m_h; // 미로의 height
	int** m_maze; // 미로의 각 항목값을 저장
	CLwyLinkedStack m_stack; // 미로 탐색을 위한 스택
	CLwyElement m_start; 
	CLwyElement m_exit;	// 시작지점과 끝지점의 좌표를 저장한 멤버변수
	char m_filename[200]; 
public :
	CLwyMaze(void) { Init(0,0); } 
	~CLwyMaze(void)	{ Reset(); 	} 
	int getM_w() { return m_w; }
	int getM_h() { return m_h; }
	void setM_w(int w) { m_w = w; }
	void setM_h(int h) { m_h = h; } // 각각의 멤버 변수들에 대한 setter, getter 정의

	void Init(int , int );
	void Reset();
	void Load( char *);	
	void Print(); // 지난번까지 함

	void getStartpoint();
	void getExitpoint(); // 시작점과 끝점을 찾는 연산
	void ErrorCheck(CPoint2D cp) { if ( ( cp.m_x < 0) || (cp.m_y < 0) )  return; }
	 // 배열의 범위를 벗어나면 그냥 return 시키도록 합니다
	void Push(CPoint2D ); // 현재 위치를 검사해서 스택에 push
	void Pop(); // Stack에서 Pop하는 함수

	void SearchExit(); // 미로찾기를 시작 함수
	bool CannotGo(); // 갈수없는 곳을 전체적으로 판별해주는 함수
	bool EndCheck(); // 끝점을 확인해 주는 함수
	void SearchFast(); // 최적 경로를 탐색해주는 함수
};
void CLwyMaze::Init(int w, int h) 
{
	if ( (w < 0) || ( h < 0 ) ) // 예외처리
		return;
	setM_h(h); // 객체에 높이와너비 각각 대입
	setM_w(w); 
	m_maze = new int* [m_h + 2]; // 동적으로 m_w +2 만큼 할당
	for (int i = 0 ; i < m_h + 2; i++ ) // 동적으로 m_w +2만큼 할당받은거에 m_h+2만큼 더 할당받음
		m_maze[i] = new int[m_w + 2]; // +2를 하는 이유는 미로의 밖에 위아래옆으로 한겹 더 벽을 싸기 위해서
}
void CLwyMaze::Reset()
{
	if ( m_maze != NULL ) {
		for ( int i = 0 ; i < m_h + 2 ; i++ ) // 받아온 갯수만큼 동적 해제
			delete [] m_maze[i];
		delete m_maze;
	}
}
void CLwyMaze::Load( char *fname )
{
	int width = 0, height = 0;
	strcpy(m_filename, fname );
	FILE *fp = fopen(m_filename, "r"); // 파일을 열어봅니다.
	if (fp == NULL ) {
		printf("File Open Error\n");
		return;
	}

	fscanf( fp , "%d %d\n", &width, &height);

	Init(width, height); // 미로의 행과 열의 크기를 동적할당으로 받음
	
	for ( int i = 0 ; i < width + 2; i++ ) {
		m_maze[0][i] = 0; // (벽)0으로 초기화
		m_maze[height+1][i] = 0;
	}
	for ( int i = 0 ; i < height + 2; i++ ) {
		m_maze[i][0] = 0;
		m_maze[i][width+1] = 0;
	}

	for ( int i = 1 ; i <= height ; i++ ) {
		for ( int j = 1 ; j <= width ; j++ ) { // 먼저 한 행부터 반복을 돌림
			fscanf( fp, "%d ", &m_maze[i][j]);
		}
		fscanf( fp, "\n");
	}
	fclose(fp);
}
void CLwyMaze::Print() 
{
	//printf("%d 행 %d 열의 미로입니다\n", m_w, m_h);
	for ( int i = 1 ; i <= m_h ; i++ ) {
		for ( int j = 1 ; j <= m_w ; j++ ) { // 먼저 한 행부터 반복을 돌림
			switch ( m_maze[i][j] ) {
				case 0 : printf("■");  break;//벽
				case 1 : printf("  ");  break; // 지나갈 수 있는 길
				case 5 : printf("○");  break; // 입구
				case 9 : printf("◎");  break; // 출구
				case 8 : printf("☆");  break; // 현재위치
				case 2 : printf("□");  break; // 지나간 길
				case 3 : printf("□");  break; // 지나갔었는데 또 지나갈 길 
			}								  // ->지나간길과 똑같이 표시함
		}
		printf("\n");
	}
}
void CLwyMaze::getStartpoint()
{
	for ( int i = 0 ; i < m_h + 2 ; i++ ) { // 미로의 입구 찾기 연산
		for ( int j = 0 ; j < m_w + 2 ; j++ ) { // 동적할당으로 부터 미로의 각 행과 열을 2개씩 더 받아왔으므로 2번더 반복
			if (m_maze[i][j] == 5) {
				m_start.setElement(i, j); // 시작점을 setter를 통해 배열의 값을 받아옴
				break;
			}
		}
	}
}
void CLwyMaze::getExitpoint()
{
	for ( int i = 0 ; i < m_h + 2 ; i++ ) { // 끝좌표 역시 행과 열 각각 +2만큼 할당했으니
		for ( int j = 0 ; j < m_w + 2 ; j++ ) { // 그만큼 반복해서 끝점(9)를 찾아서
			if ( m_maze[i][j] == 9) { // setter를 이용해서 m_exit에 값 넣기
				m_exit.setElement(i, j);
				break;
			}
		}
	}
}
void CLwyMaze::Push(CPoint2D cp)  // x와 y좌표
{
	m_stack.Push(cp); // 스택에 푸시하도록
	printf("Push >> (%d, %d)\n", m_stack.Peek().m_x, m_stack.Peek().m_y); // 보여줌
}
void CLwyMaze::Pop()
{
	printf("Pop >> (%d, %d)\n", m_stack.Peek().m_x, m_stack.Peek().m_y); // 보여줌
	m_stack.Pop();
}
bool CLwyMaze::CannotGo()
{
	if ( ( m_maze[m_start.getX() - 1][m_start.getY()] == 0 || m_maze[m_start.getX() - 1][m_start.getY()] == 2 || m_maze[m_start.getX() - 1][m_start.getY()] == 3) &&
		( m_maze[m_start.getX()][m_start.getY() - 1] == 0 || m_maze[m_start.getX()][m_start.getY() - 1] == 2 || m_maze[m_start.getX()][m_start.getY() - 1] == 3) &&
		 ( m_maze[m_start.getX() + 1][m_start.getY()] == 0 || m_maze[m_start.getX() + 1][m_start.getY()] == 2 || m_maze[m_start.getX() + 1][m_start.getY()] == 3 ) &&
		  ( m_maze[m_start.getX()][m_start.getY() + 1] == 0 || m_maze[m_start.getX()][m_start.getY() + 1] == 2 || m_maze[m_start.getX()][m_start.getY() + 1] == 3 ) )
		  return false; // 동, 서 , 남 , 북이 모두 막혀있거나 이미 갔던 곳일 경우
	else
		return true;
}
void CLwyMaze::SearchExit()
{
	bool cannotChecking = true; // 갈곳이 있는지 판별해주는 변수
	getStartpoint(); // 끝점과 시작점을 찾아줍니다.
	getExitpoint();
	while ( 1 ) {
		Print();
		system("cls"); 
		if ( cannotChecking == false ) { // 갈곳이 없다면,
			if ( m_maze[(m_start.getX() - 1)][m_start.getY()] == 2 ) { // 가뜩이나 갈곳 없는 상태에서 왔던 길이 나오는 경우
				ErrorCheck(m_start.getElement()); // 갈수있는 좌표를 체크, 배열 공간이 0보다 작은곳에 가면 안되니까
				Pop(); // 스택을 Pop함
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 3; // 지나온 길 표시, 다시 지나갈일 없는 곳을 3으로 저장
				m_start.getNorthpoint(); // 북쪽으로 좌표를 옮김
			}
			else if ( m_maze[m_start.getX()][(m_start.getY() - 1)] == 2) { // 서로 가는 연산
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 3;
				m_start.getWestpoint(); // 서쪽으로 좌표를 옮김
			}
			else if ( m_maze[(m_start.getX() + 1)][m_start.getY()] == 2) { // 남으로 가는 연산
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 3;
				m_start.getSouthpoint();
			}
			else if ( m_maze[m_start.getX()][(m_start.getY()) + 1] == 2) { // 동으로 가는 연산
				ErrorCheck(m_start.getElement());
				Pop();
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 3;
				m_start.getEastpoint();
			}
		}
		else {  // cannotChecking = true 인 경우, 즉 갈 곳이 있어서 좌표를 이동해야겠다고 할 때
			if ( m_maze[(m_start.getX() - 1)][m_start.getY()] == 1 || m_maze[(m_start.getX() - 1)][m_start.getY()] == 9) {
				//북으로 가는 연산, 벽을 마주치거나 출구를 마주친다면
				if ( (m_start.getElement().m_x == 1) || (m_start.getElement().m_y == 1) )
				ErrorCheck(m_start.getElement()); // 예외체크
				Push(m_start.getElement()); // m_start의 좌표를 계속 Push
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 2; // 지나온 길 표시
				m_start.getNorthpoint(); // 북쪽으로 좌표를 옮김
			}
			else if ( m_maze[m_start.getX()][(m_start.getY() - 1)] == 1 || m_maze[m_start.getX()][(m_start.getY() - 1)] == 9) { // 서로 가는 연산
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 2;
				m_start.getWestpoint();
			}
			else if ( m_maze[(m_start.getX() + 1)][m_start.getY()] == 1 || m_maze[(m_start.getX() + 1)][m_start.getY()] == 9) { // 남으로 가는 연산
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[(m_start.getElement().m_x)][m_start.getElement().m_y] = 2;
				m_start.getSouthpoint();
			}
			else if ( m_maze[m_start.getX()][(m_start.getY()) + 1] == 1 || m_maze[m_start.getX()][(m_start.getY()) + 1] == 9) { // 동으로 가는 연산
				ErrorCheck(m_start.getElement());
				Push(m_start.getElement());
				m_maze[m_start.getElement().m_x][(m_start.getElement().m_y)] = 2;
				m_start.getEastpoint();
			}
		}
		if ( EndCheck() == true )  // 반복문을 빠져나옴
			break;
		Sleep(50);
		cannotChecking = CannotGo(); // 갈수없는 곳을 체크해서 bool타입의 변수에 넣어줌
	}	
}
bool CLwyMaze::EndCheck()
{
	CPoint2D temp_start, temp_exit; // 좌표에 대한 구조체 변수 두개를 선언 , 시작점 끝점을 받을꺼에요
	temp_start = m_start.getElement(); // 시작점을 받고
	temp_exit = m_exit.getElement(); // 끝점을 받습니다.
	if ( (temp_start.m_x == temp_exit.m_x) && (temp_start.m_y == temp_exit.m_y) ) { // 시작점과 끝점이같다면 true를 반환합니다.
		printf("미로찾기가 끝났습니다!!\n");//끝을 만났을때 문구를 출력함
		return true;
	}
	else
		return false; // 끝이나지 않으면 EndCheck가 false가 되어 위의 SearchExit함수의 while문이 계속 돌아감
}
void CLwyMaze::SearchFast()
{
	CPoint2D temp; // 임시변수 선언
	for ( int k = 0 ; k < m_w*m_h ; k++ ) {
		temp = m_stack.Pop(); // 임시변수에 Stack해서 Pop한 좌표들을 대입
		for ( int i = 0 ; i < m_h + 2 ; i++ ) {
			for ( int j = 0 ; j < m_w + 2 ; j++ ) { // 미로의 모든 좌표들을 반복문으로 확인
				if ( (temp.m_x == i ) && (temp.m_y == j) ) 
					m_maze[i][j] = 8; // 좌표의 값이 Pop하여 return된 좌표와 같으면 8(최적경로를 표시해주는 수)을 대입
			}
		}
	}
}