#include <stdio.h>
#include <stdlib.h>

int lwy_FiboIter(int n); // �ݺ����� ���
int lwy_FiboRecur(int n); // ��ȯ���� ���

int count_FiboRecur[] = {0, }; // lwy_FiboRecur�Լ��� ����Ƚ���� �����ϴ� ����, 
// ��� 0 ���� �ʱ�ȭ����
int main() { 
	int result_FiboIter = 0, result_FiboRecur = 0, i; // �� �Լ��� ���ϵǴ� ������� �˾ƺ��� ����
	int number = 0; // ���� �Ǻ���ġ ��
	char c; // exe������ ���Ḧ ���� ����
	printf("���� �Ǻ���ġ ���� �Է��Ͻÿ� >> ");
	scanf("%d", &number);
	printf("number��  FiboIter   FiboRecur \n");
	for ( i = 0 ; i <= number ; i++ ) {
		result_FiboIter = lwy_FiboIter(i);
		result_FiboRecur = lwy_FiboRecur(i);
		printf("n= %d          %d          %d\n", i, result_FiboIter , result_FiboRecur);
	}

	for ( i = 0 ; i < number ; i++ ) {
		count_FiboRecur[i] = 0; // �տ��� �̹� ������ �߱� ������ ����� Ƚ���� �ϴ� ��� �ʱ�ȭ 
	}
	printf("ȣ��Ƚ���� ����մϴ� >>> \n");
	
	result_FiboRecur = lwy_FiboRecur(number); // �Լ� ȣ����
	count_FiboRecur[number] = 1; // number�� ���� ū ���϶��� �Ű������� �޴� ��ȯ �Լ��� �� �ѹ� �ݺ���
	for ( i = 0 ; i <= number; i++ ) {
		printf("lwy_FiboRecur(%d)ȣ��Ƚ�� : %d\n", i, count_FiboRecur[i]); // ȣ��Ƚ�� ����ϱ�
	}
	
	printf("\n");

	printf("x�� �����ø� ���α׷��� ����˴ϴ� >> ");
	do {
        c=getchar();
	} while (c != 'x');
	return 0;
}
int lwy_FiboIter(int n)
{ 
	int temp, current = 1 , last = 0; // �ӽú����� �����, ���� ���� ����
	if ( n < 2 ) // n�� 0�̳� 1�� ��� 
		return n; // �״�� ��ȯ�ϸ� ��
	else { // n��° ���� n-1��° ���� n-2��° ���� ���� ���� ���̴�.
		for ( int i = 2 ; i <= n ; i++ ) {
			temp = current; // �ӽú����� n-1���� ���� �ְ�
			current += last; // n-2���� ���� n-1��° ���� ���Ͽ� n��° ���� �����.
			last = temp; // n-2��° ���� n-1��° ���� �Ű��ش�.
		}
	}
	return current; // ������ ���� ��ȯ�Ѵ�.
}	

int lwy_FiboRecur(int n)
{
	count_FiboRecur[n] += 1; // �Լ��� ������ �� ���� n�迭 ���� ��� 1�� ���ذ�
	//�Լ��� ��� ��������� ȣ��Ǹ鼭 n�� ���� ��� �ϳ�, �Ѿ� �����鼭 �ᱹ 0��° �迭���� ������ ��
	if ( n < 2 ) 
		return n; // n�� 0�̳� 1�ϰ�� n�ǰ��� 0�� 1�̹Ƿ� �ٷ� ��ȯ�Ѵ�.
	else
		return (lwy_FiboRecur(n-1) + lwy_FiboRecur(n-2)); // ���� ���� ������ ���� �ѹ� �� ȣ���ؼ� ���Ѵ�.
}