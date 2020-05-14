/*
2020-5-14 10点05分
回声客户端的I/O程序分割
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE	30




void error_handling(char *message);
void read_routine(int sock, char *buf);
void write_routine(int sock, char *buf);

int main()
{
	int sock;
	pid_t pid;
	char buf[BUF_SIZE];
	struct sockaddr_in serv_adr;

	//创建socket
	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(atoi("8888"));

	//进行connect操作
	if (-1 == connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)))
	{
		error_handling("connect() error!");
	}

	pid = fork();
	if (0 == pid)	//子进程运行的区域
	{
		puts("进入子进程运行的区域");
		//子进程来发送数据到服务器端
		write_routine(sock, buf);
	}
	else
	{
		puts("进入父进程运行的区域");
		//父进程来接收来自服务器端的数据
		read_routine(sock, buf);
	}

	close(sock);

	return 0;

}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void read_routine(int sock, char *buf)
{
	while (1)
	{
		int str_len = read(sock, buf, BUF_SIZE);
		
		if (0 == str_len)
		{
			fputs("收到的消息为空",stdout);
			return;
		}
			
		buf[str_len] = 0;
		printf("Message From server: %s", buf);
	}
}

void write_routine(int sock, char *buf)
{
	while (1)
	{
		fgets(buf, BUF_SIZE, stdin);	//输入信息
		
		if (!strcmp(buf,"q\n") || !strcmp(buf,"Q\n"))
		{
			shutdown(sock, SHUT_WR);	//这条语句会向服务器 传递EOF
			return;
		}
		
		write(sock, buf, strlen(buf));
		
	}
}



