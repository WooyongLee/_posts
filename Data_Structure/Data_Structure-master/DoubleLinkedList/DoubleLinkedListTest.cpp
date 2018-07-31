
#include "LwyDLinkedList.h"

void main() {

	printf("\n******************* [ 2015�⵵ 2�б� �ڷᱸ�� �ǽ����� 11 ] *******************\n\n");
	printf("                1. ���߸���Ʈ�� ������ Wish List ���� ���α׷�   \n\n");

	printf("-------------------         Addtail 2ȸ, AddHead 2ȸ        -------------------\n\n");
	CLwyDLinkedList list1;													// CLinkedList Ŭ������ list ��ü ����
	list1.AddTail(new CLwyDNode("����", 8000000, 4, "����ī���"));		// ������ ��ġ�� ����Ʈ �߰�
	list1.AddTail(new CLwyDNode("��Ʈ��", 9500000, 5, "���⿡"));		// ������ ��ġ�� ����Ʈ �߰�
	list1.AddHead(new CLwyDNode("�Ȱ�", 150000, 2, "�����޿�"));		// �� ó�� ��ġ�� ����Ʈ �߰�
	list1.AddHead(new CLwyDNode("�Ź�", 100000, 1));					// �� ó�� ��ġ�� ����Ʈ �߰�
	list1.Display( "list1 " );											// ����Ʈ ��ü ���

	printf("-------------------   �켱�������� 2�� ��� Ž�� & AddNext  -------------------\n\n");
	CLwyDNode *n = list1.FindNodePriority( 2 );							// �켱�������� 2�� ��� Ž��
	list1.AddNext(n, new CLwyDNode("����", 100000, 3, "12�� ����"));	// �켱�������� 2�� ��� �ڿ� ���ο� ��� ����
	list1.Display( "list1 " );			
	
	printf("------- RemoveHead() , �켱�������� 2�� ��� Ž�� & ����, RemoveTail() --------\n\n");
	list1.DeleteHead();													// ����Ʈ �� �� ��� ����
	n = list1.FindNodePriority( 2 );									// �켱�������� 2�� ��� Ž��
	list1.Delete( n );													// �� ��� ����
	list1.DeleteTail();													// ����Ʈ �� �� ��� ����
	list1.Display( "list1 " );											// ����Ʈ���� ȭ�����													

	printf("------------- List1 DisplayRev() : �Ųٷ� ���(������������x) �ݺ� ------------\n\n");
	list1.DisplayRev( "list1 " );										// ����Ʈ���� ���� ȭ�����

	printf("------------- List1 DisplayRevRe() : �Ųٷ� ���(������������x) ��� ------------\n\n");
	list1.DisplayRevRecur( "list1 " );										// ����Ʈ���� ���� ȭ�����

/*	CLwyDLinkedList list2;													// CLinkedList Ŭ������ list ��ü ����
	list2.AddTail(new CLwyDNode("����", 8000000, 4, "����ī���"));		// ������ ��ġ�� ����Ʈ �߰�
	list2.AddTail(new CLwyDNode("��Ʈ��", 9500000, 5, "���⿡"));		// ������ ��ġ�� ����Ʈ �߰�
	list2.AddHead(new CLwyDNode("�Ȱ�", 150000, 2, "�����޿�"));		// �� ó�� ��ġ�� ����Ʈ �߰�
	list2.AddHead(new CLwyDNode("�Ź�", 100000, 1));					// �� ó�� ��ġ�� ����Ʈ �߰�

	list1.Merge(list2);
	list1.Display("List1 merge");  */

	printf("-------------------   list1�� ��� �׸� ���� & list1 ���  -------------------\n\n");
	list1.Clear();													// ����Ʈ�� ��� �׸� ����
	list1.Display( "list1 " );													// ����Ʈ���� ȭ�����

	getchar();
	getchar();


}
