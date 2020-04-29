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
	int sock;
	struct sockaddr_in serv_addr;
	char message[30];
	int str_len;

	//Step1 调用Socket函数
	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("Create Socket error");
		return -1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(atoi("8888"));

	//Step2 调用connect函数
	if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("connect function error");
		return -1;
	}

	//Step3 读取内容
	str_len = read(sock, message, sizeof(message) - 1);
	if (-1 == str_len)
	{
		printf("read fucntion error");
		return -1;
	}
	
	printf("Message from server: %s \n", message);

	close(sock);

	return 0;
}
