/*
2020-5-9
创建僵尸进程
*/

#include <stdio.h>
#include <unistd.h>

int main()
{
	pid_t pid;	//进程ID
	pid = fork();	//复制主进程
	
	if (0 == pid)
	{
		puts("我是子进程");
	}
	else
	{
		printf("子进程的ID：%d \n", pid);
		sleep(30);
	}

	if (0 == pid)
	{
		puts("子进程结束");
	}
	else
	{
		puts("主进程结束");
	}
	
	return 0;
	
}
