/*
2020-5-14 11点40分
关于管道双向通信的例子
*/

#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE	30

int main()
{
	int fds[2];
	char str1[] = "Hi JamesWu9527";
	char str2[] = "我收到你的消息了";
	char buf[BUF_SIZE];
	pid_t pid;

	pipe(fds);	//创建管道
	pid = fork();	//通过fork创建一个线程 然后两者进行通讯
	if (0 == pid)	//子进程执行的区域
	{
		fputs("我要发送数据啦\n",stdout);			//Step2
		write(fds[1], str1, sizeof(str1));	//Step3
		sleep(2);							//Step5
		read(fds[0], buf, BUF_SIZE);		//Step8
		printf("收到父进程传过来的消息：%s\n",buf);
	}
	else	//主进程执行的区域
	{
		read(fds[0], buf, BUF_SIZE);		//Step1
		puts("我接收到数据啦");					//Step4
		puts(buf);
		write(fds[1], str2, sizeof(str2));	//Step6
		sleep(3);							//Step7
	}

	return 0;
}
