/*
2020-5-19 11点55分
使用send 和 recv函数
测试MSG_PEEK 服务器端
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>

#define BUF_SIZE	30

void error_handling(char *message);

int acpt_sock;
int recv_sock;

int main()
{
	struct sockaddr_in recv_adr, serv_adr;
	int str_len, state;
	socklen_t serv_adr_sz;
	char buf[BUF_SIZE];

	//创建socket
	acpt_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&recv_adr, 0, sizeof(recv_adr));
	recv_adr.sin_family = AF_INET;
	recv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	recv_adr.sin_port = htons(atoi("8888"));

	//bind 操作
	if (-1 == bind(acpt_sock, (struct sockaddr*)&recv_adr, sizeof(recv_adr)))
	{
		error_handling("bind() error");
	}

	//listen操作
	listen(acpt_sock, 5);

	//accept操作 接收来自客户端的发过来的消息
	serv_adr_sz = sizeof(serv_adr);
	recv_sock = accept(acpt_sock, (struct sockaddr*)&serv_adr, &serv_adr_sz);

	while (1)
	{
		str_len = recv(recv_sock, buf, sizeof(buf)-1, MSG_PEEK | MSG_DONTWAIT);
		if (str_len > 0 )
		{
			break;
		}
	}

	buf[str_len] = 0;
	printf("Buffering %d bytes: %s \n", str_len, buf);

	str_len = recv(recv_sock, buf, sizeof(buf)-1, 0);
	buf[str_len] = 0;
	printf("Read again: %s\n", buf);
		
	close(recv_sock);
	close(acpt_sock);

	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


