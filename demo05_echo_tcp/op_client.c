/*
�򵥵�TCPʵ��
��дop client��
ʵ�ּ򵥵ļ��㹦��
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

int main()
{
	int sock;
	char opmsg[BUF_SIZE];
	int result, opnd_cnt, i;
	struct sockaddr_in serv_addr;

	//Step1 ����һ��socket
	sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_addr.sin_port = htons(atoi("8888"));

	//Step2 Connect
	if(-1 == connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)))
	{
		printf("connect function error!");
		exit(1);
	}
	else
	{
		puts("Connected.............");
	}

	fputs("Operand count: ",stdout);		//ȷ����������ָ���
	scanf("%d", &opnd_cnt);
	opmsg[0] = (char*)opnd_cnt;

	for (i=0; i<opnd_cnt; i++)
	{
		printf("Operand %d:", i+1);
		scanf("%d", (int*)&opmsg[i*OPSZ+1]);
	}
	
	fgetc(stdin);
	
	fputs("Operator: ", stdout);			//���������
	scanf("%c", &opmsg[opnd_cnt*OPSZ+1]);

	write(sock, opmsg, opnd_cnt*OPSZ+2);
	read(sock, &result, RLT_SIZE);

	printf("Operation result: %d\n", result);
	close(sock);
	return 0;
}
