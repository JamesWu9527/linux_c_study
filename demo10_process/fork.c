/*
2020-5-9
fork函数的使用
*/

#include <stdio.h>
#include <unistd.h>

int gval = 10;

int main()
{
	pid_t pid;	//进程ID
	int lval = 20;
	gval++;
	lval++;

	pid = fork();	//复制主进程
	if (0 == pid)
	{
		gval += 2;
		lval += 2;
	}
	else
	{
		gval -= 2;
		lval -= 2;
	}

	if (0 == pid)
	{
		printf("Child proc:[%d, %d] \n", gval, lval);
	}
	else
	{
		printf("Parent proc:[%d, %d] \n", gval, lval);
	}
	
	return 0;
	
}
