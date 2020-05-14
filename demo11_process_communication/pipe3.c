/*
2020-5-14 11点40分
使用两个管道进行数据间的双向通信
*/

#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE	30

int main()
{
	int fds1[2], fds2[2];
	char str1[] = "Hi JamesWu9527";
	char str2[] = "我收到你的消息了";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds1);	//创建管道
	pipe(fds2);
	
	pid = fork();	//通过fork创建一个线程 然后两者进行通讯
	if (0 == pid)	//子进程执行的区域
	{
		write(fds1[1], str1, sizeof(str1));
		read(fds2[0], buf, BUF_SIZE);
		printf("收到父进程传过来的消息：%s\n",buf);
	}
	else	//主进程执行的区域
	{
		read(fds1[0], buf, BUF_SIZE);
		puts("我接收到数据啦");		
		puts(buf);
		write(fds2[1], str2, sizeof(str2));
	}

	return 0;
}
