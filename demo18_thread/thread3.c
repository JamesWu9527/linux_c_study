/*
2020-6-3 21点35分
演示多个线程工作的原型
这里演示的例子 是存在问题的 两个线程共同访问变量sum是会出问题的
这里演示的例子不会出错，因为数据量很小
thread4.c将演示错误的例子
*/

#include <stdio.h>
#include <pthread.h>

void *thread_sum(void *arg);

int sum = 0;

int main()
{
	pthread_t id_t1, id_t2;
	int range1[] = {1,5};
	int range2[] = {6,10};

	pthread_create(&id_t1, NULL, thread_sum, (void*)range1);
	pthread_create(&id_t2, NULL, thread_sum, (void*)range2);

	pthread_join(id_t1, NULL);
	pthread_join(id_t2, NULL);

	printf("result: %d \n", sum);
	return 0;
}

void *thread_sum(void *arg)
{
	int start = ((int*)arg)[0];
	int end = ((int*)arg)[1];

	while (start <= end)
	{
		sum += start;
		start++;
	}

	return NULL;

}