#include "LwyLinkedStack.h"
#include "LwyMaze.h"

void main() {
	CLwyMaze maze;
	maze.Load("maze.txt");
	printf("%d �� %d ���� �̷��Դϴ�\n", maze.getM_w(), maze.getM_h());
	maze.Print();
	printf(" �Ա� �ۺ��� --> �ⱸ �� ���ã�� ���� [enter]\n");
	getchar();
	maze.SearchExit();
	maze.Print();
	printf("\nEnter�� �����ø� �ִܰŸ��� ��µ˴ϴ�\n\n");
	getchar();

	maze.SearchFast();
	maze.Print();
	getchar();
	getchar();
}