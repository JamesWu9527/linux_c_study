/*
2020-5-12 09点31分
一个关于 sigaction 的小例子
*/

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig);		//信号触发的函数
void keycontrol(int sig);	

int main()
{
	int i = 0;
	struct sigaction act;
	act.sa_handler = timeout;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGALRM, &act, 0);

	alarm(2);

	for (;i<3; i++)
	{
		puts("wait...");
		sleep(100);
	}
	
	return 0;
}

void timeout(int sig)
{
	if (SIGALRM == sig)
	{
		puts("Time out");
	}
	alarm(2);
}

void keycontrol(int sig)
{
	if (SIGINT == sig)
	{
		puts("CTRL + C pressed");
	}
}
