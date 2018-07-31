#include <stdio.h>
#include <stdlib.h>

int lwy_hanoi(int size, char from, char temp, char to); // �ϳ���ž �Լ�
int lwy_hanoiFrequency(int size, char from, char temp, char to); // ž�� �Ű����� ���� ������� �ʰ�, ���� ��ȯ�ϴ� �Լ�
// ������ ũ��, ó����ġ, �ӽú���, �Ű��� ��ġ�� �Ű������� ����
int main()
{
	int number = 0; // �ѱ� ������ ����
	int moveNumber = 0, temp = 0; // ���� �Ѱ����� Ƚ���� �ӽú���
	char c; // exe������ ���Ḧ ���� ����
	printf("�ѱ� ������ ������ �Է¹޽��ϴ� : ");
	scanf("%d", &number); // ǥ���Է�
	moveNumber = lwy_hanoi(number, 'A', 'B', 'C'); // �Լ�ȣ��
	printf("\n %d���� ������ �� �Ű��� Ƚ�� = %d\n", number, moveNumber);

	printf("\n3���� 15�������ǿ����� �Ű����� Ƚ���� ����մϴ� >> \n");
	for ( int i = 3 ; i < 16 ; i++ ) {
		moveNumber = lwy_hanoiFrequency(i, 'A', 'b', 'C');// �ѹ� �ݺ��ϰ� ���� Ƚ������ 0���� �ʱ�ȭ ���� �ʰ�
		// ��� ���� ���� �����ִ� ���¿��� ���� �Լ� ������ ����
		printf("%d ���� ������ ������ Ƚ�� : %d\n", i, moveNumber - temp); // ���� �������� ������ ���� ���̰� ���� Ƚ��, �̸� �����
		temp = moveNumber;// �ӽú����� �����Ͽ� ���� ���� Ƚ���� ���� ������ ����
	}
	printf("x�� �����ø� ���α׷��� ����˴ϴ�");
	do {
        c=getchar();
	} while (c != 'x');
	return 0;
}
int lwy_hanoi(int size, char from, char temp, char to) 
{
	static int frequency_number = 0; // �Ű��� Ƚ���� �޴� ����
	// �Լ��� ��� ������ ������ �ѹ��� �ʱ�ȭ ���ַ��� static������� 
	if ( size == 1 )  {
		printf("%c => %c (ũ�� %d�� ����)\n", from, to, size);
		frequency_number++; // �ű� ������ ����ϰ� �ٷ� Ƚ���� ������Ŵ
	}
	else {
		lwy_hanoi(size-1, from, to, temp); 
		printf("%c => %c (ũ�� %d�� ����)\n", from, to, size);
		frequency_number++;
		lwy_hanoi(size-1, temp, from, to);	
	}
	return frequency_number; // �Ű��� ���� ��ȯ
}

int lwy_hanoiFrequency(int size, char from, char temp, char to)
{
	static int frequency_number = 0; // �Ű��� Ƚ���� �޴� ����
	if ( size == 1 )  {
		frequency_number++; // Ƚ���� ������Ŵ
	}
	else {
		lwy_hanoiFrequency(size-1, from, to, temp); 
		frequency_number++;
		lwy_hanoiFrequency(size-1, temp, from, to);	
	}
	return frequency_number; // �Ű��� ���� ��ȯ
}