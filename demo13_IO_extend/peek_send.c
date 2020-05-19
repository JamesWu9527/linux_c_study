/*
2020-5-19 11点54分
使用send 和 recv函数
测试MSG_PEEK 客户端
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void error_handling(char *message);

int main()
{
	int sock;
	struct sockaddr_in recv_adr;

	//创建socket
	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&recv_adr, 0, sizeof(recv_adr));
	recv_adr.sin_family = AF_INET;
	recv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	recv_adr.sin_port = htons(atoi("8888"));

	//connect 操作
	if (-1 == connect(sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr)))
	{
		error_handling("connect() error");
	}

	//发送数据给服务器端
	write(sock, "123", strlen("123"));
	
	close(sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

