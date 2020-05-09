/*
2020-5-9
杀死僵尸进程
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int status;
	pid_t pid = fork();	//复制主进程
	
	if (0 == pid)
	{
		return 3;
	}
	else
	{
		printf("子进程的ID：%d \n", pid);
		pid = fork();
		if (0 == pid)
		{
			exit(7);
		}
		else
		{
			printf("子进程的ID：%d \n", pid);
			wait(&status);
			if (WIFEXITED(status))	//用宏WIFEXITED 验证子进程是否正常终止 正常则 返回true
			{
				printf("子进程发送1: %d \n",WEXITSTATUS(status));	//用宏 WEXITSTATUS 输出子进程的返回值
			}

			wait(&status);
			if (WIFEXITED(status))
			{
				printf("子进程发送2: %d \n",WEXITSTATUS(status));
			}

			sleep(10);
		}
	}
	
	return 0;
	
}

