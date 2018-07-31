#include "LwyBSTree.h"

void main()
{
	printf("\n******************* [ 2015�⵵ 2�б� �ڷᱸ�� �ǽ����� 12 ] *******************\n\n");
	printf("                1. ����Ž��Ʈ���� ������ Wish List ���� ���α׷�   \n\n");

	CLwyBSTree t;

	t.Add( new CLwyTNode( 4, "����", 80, "����ī���" ) );
	t.Add( new CLwyTNode( 5, "��Ʈ��", 950, "���⿡" ) );
	t.Add( new CLwyTNode( 2, "�Ȱ�", 15, "�����޿�" ) );
	t.Add( new CLwyTNode( 1, "�Ź�", 10) );
	t.Add( new CLwyTNode( 3, "����", 10, "12�� ����" ) );
	t.Add( new CLwyTNode( 6, "���", 10, "���⿩�� ����" ) );
	t.Add( new CLwyTNode( 7, "���̾", 3, "���ظ���" ) );
	t.PrintPreOrder();
	t.PrintInOrder();
	t.PrintPostOrder();

	printf("-------------------         [ t.SearchPriority(7) ]         -------------------\n\n");
	t.SearchPriority(7);
	
	printf("\n-------------------      [ t.SearchPriceRange(1, 30) ]      -------------------\n\n");
	t.SearchPriceRange(1, 30);

	printf("\n-------------------     [ t.GetHeight(), t.GetCount() ]     -------------------\n\n");
	printf("[CBSTree�� ��ü t�� ����     : %2d]\n", t.GetHeight());
	printf("[CBSTree�� ��ü t�� ��尳�� : %2d]\n", t.GetCount());
	
	getchar();
}
