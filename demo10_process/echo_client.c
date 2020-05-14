/*
简单的TCP实例
编写echo client端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main()
{
	int sock;
	struct sockaddr_in serv_addr;
	char message[BUF_SIZE];
	int str_len, recv_len, recv_cnt;

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
	else
	{
	    puts("Connected..........");
	}
    
    while (1)
    {
        //Step3 read and write message
        fputs("Input message(Q to quit): ",stdout);
        fgets(message, BUF_SIZE, stdin);    //Input string
        str_len = write(sock, message, strlen(message));      //send message to server
        if (!strcmp(message,"q\n") || !strcmp(message,"Q\n"))
        {
            break;
        }
        
        recv_len = 0;
        while (recv_len < str_len)
        {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1); //recv message from server
            if (-1 == recv_len)
            {
                printf("read function error");
                exit(1);
            }
            recv_len += recv_cnt;
        }
	    
	    message[recv_len] = 0; 
	    printf("Message from server: %s \n", message);
	    
    }
	

	close(sock);
	return 0;
}
