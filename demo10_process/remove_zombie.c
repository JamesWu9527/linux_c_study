/*
2020-5-12 09点59分
移除僵尸进程
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void read_childproc(int sig);

int main()
{
	pid_t pid;
	struct sigaction act;
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGCHLD, &act, 0);	//在子进程结束的时候会被触发

	pid = fork();	//创建一个子进程
	if (0 == pid)		//子进程
	{
		puts("我是一个子进程");
		sleep(10);
		return 12;
	}
	else				//父进程
	{
		printf("父进程1 ID：%d\n", pid);
		pid = fork();	//创建另外一个子进程
		if (0 == pid)	//另一个子进程
		{
			puts("我是另外一个子进程");
			sleep(10);
			return 24;
		}
		else			//父进程
		{
			int i;
			printf("父进程2 ID：%d\n", pid);

			for (i=0; i<5; i++)
			{
				puts("wait...");
				sleep(5);
			}
				
		}
	}
		
	
	return 0;
}


void read_childproc(int sig)
{
	int status;
	pid_t id = waitpid(-1, &status, WNOHANG);	//这里子进程将会正常终止，不会成为僵尸进程
	if (WIFEXITED(status))
	{
		printf("移除进程ID为：%d 的进程\n", id);
		printf("Child send: %d \n", WEXITSTATUS(status));

	}
	
}


