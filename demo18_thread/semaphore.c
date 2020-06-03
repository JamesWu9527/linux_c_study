/*
2020-6-3 22��26��
��ʾ����̷߳����ٽ������´��������
ͨ���ź���������߳�ͬ��������
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREAD	100

void *thread_inc(void* arg);
void *thread_des(void *arg);

long long num = 0;
static sem_t sem_one;
static sem_t sem_two;

int main()
{
	pthread_t thread_id[NUM_THREAD];
	int i;

	//���ź������г�ʼ��
	sem_init(&sem_one, 0, 0);	//��ʼ��Ϊ0
	sem_init(&sem_two, 0, 1);	//��ʼ��Ϊ1

	printf("sizeof long long: %d\n", sizeof(long long));
	for (i=0; i<NUM_THREAD; i++)
	{
		if (i%2)
		{
			pthread_create(&(thread_id[i]), NULL, thread_inc, NULL);
		}
		else
		{
			pthread_create(&(thread_id[i]), NULL, thread_des, NULL);
		}
	}

	for (i=0; i<NUM_THREAD; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	printf("result: %ld \n", num);

	//�����ź���
	sem_destroy(&sem_one);
	sem_destroy(&sem_two);	
	return 0;
}

void *thread_inc(void* arg)
{
	int i;
	sem_wait(&sem_one);		//ע������ĵ���˳��
	for (i=0; i<50000000; i++)
	{
		num += 1;
	}
	sem_post(&sem_two);
	return NULL;
}

void *thread_des(void *arg)
{
	int i;
	sem_wait(&sem_two);	//ע������ĵ���˳�� ���������෴��
	for (i=0; i<50000000; i++)
	{
		num -=1;
	}
	sem_post(&sem_one);
	return NULL;
}
