#include "LwyLinkedQueue.h"
// ���� 8�� �ߴ� cpp������ �ŰܿԽ��ϴ�
#include <stdlib.h>
void main(){

	printf("\n***************** [ 2015�⵵ 2�б� �ڷᱸ�� �ǽ����� 9 ] *****************\n\n");
	printf("                       2. ���� ť �׽�Ʈ ���α׷�   \n\n");

	CLwyLinkedQueue que;

	printf(" CLinkedQueue ���� 8�� ���� => ");
	for( int i=1 ; i<9 ; i++){
		que.EnQueue(new CLwyNode(i));
	}
	que.DisPlay();
	
	printf(" CLinkedQueue ���� 3�� ���� => ");
	CLwyNode* n;
	//int n = 0;
	n = que.DeQueue(); delete n;
	n = que.DeQueue(); delete n;
	n = que.DeQueue(); delete n;

	que.DisPlay();

	printf(" CLinkedQueue ��ȯ Peek() ���� => %2c", que.Peek()->GetInt());

	getchar();
	getchar();
}