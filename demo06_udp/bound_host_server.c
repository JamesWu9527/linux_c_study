/*
2020-5-7 16：27
UDP的数据边界问题
server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 	30

void error_handling(char *message);

void main()
{
	int serv_sock;
	char message[BUF_SIZE];
	int str_len, i;
	socklen_t clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;

	//Step1 创建socket套接字
	serv_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (-1 == serv_sock)
	{
		error_handling("UDP socket 创建失败");
	}

	//对地址的结构体进行一个初始化
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi("8888"));

	//Step2 bind连接socket
	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
	{
		error_handling("bind 失败");
	}

	//收来自客户端的消息 收三次
	for (i=0; i<3; i++)
	{
		sleep(5);
		clnt_adr_sz = sizeof(clnt_adr);
		str_len = recvfrom(serv_sock, message, BUF_SIZE, 0,
			(struct sockaddr*)&clnt_adr, &clnt_adr_sz);
		printf("接收来自客户端的消息：%d %s\n", i+1, message);
	}

	close(serv_sock);
	
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

