#include "LwyQueue.h"
int main(){
	CLwyQueue q;
	
	for(int i = 0; i < 10; i++) // 큐에 0부터 9까지 인자를 대입
		q.EnQueue(i);

	q.Display(); // 0,1,2,3,....,9

	q.DeQueue(); // DeQueue연산 실행
	q.DeQueue();
	q.DeQueue();

	q.Display(); // 3,4,5, ... ,9

	q.DeQueue();
	q.DeQueue();
	q.DeQueue();
	q.DeQueue();
	q.DeQueue();
	q.DeQueue();
	q.DeQueue();
	q.DeQueue();


	q.Display();

	getchar();
	getchar();
	return 0;
}