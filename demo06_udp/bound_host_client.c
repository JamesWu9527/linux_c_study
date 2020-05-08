/*
2020-5-7 16：27
UDP的数据边界问题
client
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message);

void main()
{
	int clnt_sock;
	struct sockaddr_in serv_adr;

	//发送消息
	char msg1[] = "Hi!";
	char msg2[] = "2 message";
	char msg3[] = "3 message";

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

	
	//Step2.1 sendto发送消息给服务器端
	sendto(clnt_sock, msg1, strlen(msg1), 0,
		(struct sockaddr*)&serv_adr, sizeof(serv_adr));

	sendto(clnt_sock, msg2, strlen(msg2), 0,
		(struct sockaddr*)&serv_adr, sizeof(serv_adr));

	sendto(clnt_sock, msg3, strlen(msg3), 0,
		(struct sockaddr*)&serv_adr, sizeof(serv_adr));
		
	close(clnt_sock);
	
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

