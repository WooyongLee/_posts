#include "LwyLinkedList.h"

void main() {

	printf("\n******************* [ 2015�⵵ 2�б� �ڷᱸ�� �ǽ����� 10 ] *******************\n\n");
	printf("                          2. Wish List ���� ���α׷�   \n\n");

	printf("-------------------         Addtail 2ȸ, AddHead 2ȸ        -------------------\n\n");
	CLwyLinkedList list1;												// CLinkedList Ŭ������ list ��ü ����
	list1.AddTail(new CLwyNode("����", 8000000, 4, "����ī���"));		// ������ ��ġ�� ����Ʈ �߰�
	list1.AddTail(new CLwyNode("��Ʈ��", 9500000, 5, "���⿡"));		// ������ ��ġ�� ����Ʈ �߰�
	list1.AddHead(new CLwyNode("�Ȱ�", 150000, 2, "�����޿�"));			// �� ó�� ��ġ�� ����Ʈ �߰�
	list1.AddHead(new CLwyNode("�Ź�", 100000, 1));						// �� ó�� ��ġ�� ����Ʈ �߰�
	list1.Display( "list1 " );													// ����Ʈ ��ü ���

	printf("-------------------   �켱�������� 2�� ��� Ž�� & AddNext  -------------------\n\n");
	CLwyNode *n = list1.FindNodePriority( 2 );							// �켱�������� 2�� ��� Ž��
	list1.AddNext(n, new CLwyNode("����", 100000, 3, "12�� ����"));		// �켱�������� 2�� ��� �ڿ� ���ο� ��� ����
	list1.Display( "list1 " );			

	printf("-------------- RemoveHead() , �켱�������� 2�� ��� Ž�� & ���� ---------------\n\n");
	list1.DeleteHead();										// ����Ʈ �� �� ��� ����
	n = list1.FindNodePriority( 2 );						// �켱�������� 2�� ��� Ž��
	list1.Delete( n );										// �� ��� ����
	list1.Display( "list1 " );								// ����Ʈ���� ȭ�����

	getchar();
	getchar();


}
