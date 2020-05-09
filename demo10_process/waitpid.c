/*
2020-5-9
杀死僵尸进程
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int status;
	pid_t pid = fork();	//复制主进程
	
	if (0 == pid)
	{
		sleep(15);
		return 24;
	}
	else
	{
		while (!waitpid(-1, &status, WNOHANG))
		{
			sleep(3);
			puts("sleep 3sec.");
		}

		if (WIFEXITED(status))
		{
			printf("子进程发送: %d \n",WEXITSTATUS(status));
		}

	}
	
	return 0;
	
}

