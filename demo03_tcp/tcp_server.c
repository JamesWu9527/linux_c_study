/*
简单的TCP实例
编写server端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>


int main()
{
	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	socklen_t clnt_addr_size;
	char message[] = "Hello World!";

	//Step1 调用Socket函数
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
	{
		printf("Create Socket error");
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi("8888"));

	//Step2 调用bind函数
	if (bind(serv_sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("bind function error");
		return -1;
	}

	//Step3 调用listen函数
	if (listen(serv_sock, 5) == -1)
	{
		printf("listen function error");
		return -1;
	}

	clnt_addr_size = sizeof(clnt_addr);

	//Step4 调用accept函数
	clnt_sock = accept(serv_sock, (struct sockaddr*) & clnt_addr, &clnt_addr_size);
	if (-1 == clnt_sock)
	{
		printf("acccpt function error");
		return -1;
	}

	write(clnt_sock, message, sizeof(message));

	close(clnt_sock);
	close(serv_sock);
	return 0;
}
