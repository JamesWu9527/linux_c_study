/*
简单的TCP实例
编写op server端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE    1024
#define RLT_SIZE    4
#define OPSZ        4

int calculate(int opnum, int opnds[], char oprator);

int main()
{
	int serv_sock, clnt_sock;
	char opinfo[BUF_SIZE];
	int result, opnd_cnt, i;
	int recv_cnt, recv_len;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_size;
	int str_len;

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
	if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
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
	for (i=0; i<5; i++)     //max connect clients number 5
	{
	    opnd_cnt = 0;
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
		read(clnt_sock, &opnd_cnt, 1);	//按照一个字节去读

		recv_len = 0;
		while ((opnd_cnt*OPSZ + 1) > recv_len)
		{
			recv_cnt = read(clnt_sock, &opinfo[recv_len], BUF_SIZE-1);
			recv_len += recv_cnt;
		}
		
		result = calculate(opnd_cnt, (int*)opinfo, opinfo[recv_len-1]);
		write(clnt_sock, (char*)&result, sizeof(result));
        
        close(clnt_sock);
            
	}
	
	close(serv_sock);
	return 0;
}

int calculate(int opnum, int opnds[], char oprator)
{
	int result = opnds[0], i;
	switch (oprator)
	{
		case '+':
			for (i=1; i<opnum; i++) result += opnds[i];
			break;
		case '-':
			for (i=1; i<opnum; i++) result -= opnds[i];
			break;
		case '*':
			for (i=1; i<opnum; i++) result *= opnds[i];
			break;
		default:
			result = -1;
			break;
	}
	return result;
}

