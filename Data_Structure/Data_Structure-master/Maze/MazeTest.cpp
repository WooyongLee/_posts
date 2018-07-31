#include "LwyLinkedStack.h"
#include "LwyMaze.h"

void main() {
	CLwyMaze maze;
	maze.Load("maze.txt");
	printf("%d 행 %d 열의 미로입니다\n", maze.getM_w(), maze.getM_h());
	maze.Print();
	printf(" 입구 ○부터 --> 출구 ◎ 경로찾기 시작 [enter]\n");
	getchar();
	maze.SearchExit();
	maze.Print();
	printf("\nEnter를 누르시면 최단거리가 출력됩니다\n\n");
	getchar();

	maze.SearchFast();
	maze.Print();
	getchar();
	getchar();
}