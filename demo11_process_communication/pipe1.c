/*
2020-5-14 11点24分
关于管道的基础概念
*/

#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE	30

int main()
{
	int fds[2];
	char str[] = "Hi JamesWu9527";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	//创建管道
	pid = fork();	//通过fork创建一个线程 然后两者进行通讯
	if (0 == pid)	//子进程执行的区域
	{
		fputs("我要发送数据啦\n",stdout);
		write(fds[1], str, sizeof(str));
	}
	else	//主进程执行的区域
	{
		read(fds[0], buf, BUF_SIZE);	//这里会阻塞 等待消息过来
		puts("我接收到数据啦");
		puts(buf);
	}

	return 0;
}
