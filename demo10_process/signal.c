/*
2020-5-11 14点55分
一个关于signal的小例子
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig);		//信号触发的函数
void keycontrol(int sig);	

int main()
{
	int i = 0;
	signal(SIGALRM, timeout);
	signal(SIGINT, keycontrol);
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
