/*
2020-5-6 17：03
基于UDP的回声 客户端
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
	int clnt_sock;
	char message[BUF_SIZE];
	int str_len;
	socklen_t serv_adr_sz;
	struct sockaddr_in serv_adr, from_adr;

	//Step1 创建socket套接字
	clnt_sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (-1 == clnt_sock)
	{
		error_handling("UDP socket 创建失败");
	}

	//对地址的结构体进行一个初始化
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(atoi("8888"));

	while (1)
	{
		fputs("输入信息(q退出)：",stdout);
		fgets(message, sizeof(message), stdin);
		if (!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
			break;

		//Step2.1 sendto发送消息给服务器端
		sendto(clnt_sock, message, strlen(message), 0,
			(struct sockaddr*)&serv_adr, sizeof(serv_adr));
		
		serv_adr_sz = sizeof(from_adr);

		//Step2.2 recvfrom接收来自服务器端的消息
		str_len = recvfrom(clnt_sock, message, BUF_SIZE, 0,
			(struct sockaddr*)&from_adr, &serv_adr_sz);
		message[str_len] = 0;
		printf("消息来自于服务器端：%s", message);
		
	}

	close(clnt_sock);
	
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

