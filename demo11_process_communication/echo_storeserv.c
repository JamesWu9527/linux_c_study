/*
2020-5-14 14点11分
实现并发的回声服务器端
使用管道 将回声客户端传输的字符串按序保存到文件中
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE	100

void error_handling(char *message);
void read_childproc(int sig);

int main()
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	int fds[2];

	pid_t pid;
	struct sigaction act;
	socklen_t adr_sz;
	int str_len, state;
	char buf[BUF_SIZE];

	//防止产生僵尸进程
	act.sa_handler = read_childproc;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	state = sigaction(SIGCHLD, &act, 0);

	//创建socket
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	//对serv_adr 进行初始化 为bind做准备
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi("8888"));	//端口号 设置为8888

	//bind绑定
	if (-1 == bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)))
	{
		error_handling("bind() error");
	}

	//listen 监听
	if (-1 == listen(serv_sock, 5))	//最大允许5个客户端进行连接
	{
		error_handling("listen() error");
	}

	//增加一个子进程 用来写文件
	pipe(fds);
	pid = fork();
	if (0 == pid)
	{
		FILE *fp = fopen("echomsg.txt", "wt");
		char msgbuf[BUF_SIZE];
		int i, len;

		for (i=0; i<10; i++)	//保存十条数据
		{
			len = read(fds[0], msgbuf, BUF_SIZE);	//接收父进程接的msg
			fwrite((void*)msgbuf, 1, len, fp);
		}
		fclose(fp);
		return 0;
	}
	
	while (1)
	{
		adr_sz = sizeof(clnt_adr);
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
		if (-1 == clnt_sock)
		{
			continue;
		}
		else
		{
			puts("new client connected...");
		}

		pid = fork();
		if (-1 == pid)
		{
			close(clnt_sock);
			continue;
		}

		if (0 == pid)	//子进程运行的区域
		{
			close(serv_sock);
			while ((str_len = read(clnt_sock, buf, BUF_SIZE)) != 0)		//接收到客户端传输过来的内容
			{
				write(clnt_sock, buf, str_len);		//将接收的内容发回给客户端 实现回声
				write(fds[1], buf, str_len);
			}

			close(clnt_sock);
			puts("client disconnected...");
			return 0;
		}
		else	//主进程运行的区域
		{
			close(clnt_sock);
		}
	}

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void read_childproc(int sig)
{
	pid_t pid;
	int status;
	pid = waitpid(-1, &status, WNOHANG);
	printf("removed proc id: %d \n", pid);
}




