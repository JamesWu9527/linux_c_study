/*
�򵥵�TCPʵ��
��дclient��
�޸�read�ĵ��÷�ʽ�����ж�ε���read ÿ�ζ�ȡ���������� 
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
	int str_len = 0;
	int idx = 0, read_len = 0;

	//Step1 ����Socket����
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

	//Step2 ����connect����
	if (connect(sock, (struct sockaddr*) & serv_addr, sizeof(serv_addr)) == -1)
	{
		printf("connect function error");
		return -1;
	}

	//Step3 ��ȡ���� modify
	/*str_len = read(sock, message, sizeof(message) - 1);
	if (-1 == str_len)
	{
		printf("read fucntion error");
		return -1;
	}
	*/
	while (read_len = read(sock,&message[idx++],1))
	{
	    if (-1 == read_len)
	    {
	        printf("read fucntion error");
	        return -1;
	    }
	    
	    str_len += read_len;
	}
	
	printf("Message from server: %s \n", message);
	printf("Function read call count: %d \n",str_len);

	close(sock);

	return 0;
}
