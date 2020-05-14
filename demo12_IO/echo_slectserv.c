/*
2020-5-14 16点14分
I/O复用服务器端
使用select来重写服务器端
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE	100

void error_handling(char *message);

int main()
{
	int serv_sock, clnt_sock;
	struct sockaddr_in serv_adr, clnt_adr;
	struct timeval timeout;		//时间结构体
	fd_set reads, cpy_reads;

	socklen_t adr_sz;
	int fd_max, str_len, fd_num, i;
	char buf[BUF_SIZE];

	//创建socket
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi("8888"));

	//bind
	if (-1 == bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)))
	{
		error_handling("bind() error");
	}

	//listen
	if (-1 == listen(serv_sock, 5))
	{
		error_handling("listen() error");
	}

	//这里对fd_set的值进行一个初始化
	FD_ZERO(&reads);
	FD_SET(serv_sock, &reads);		//监视serv_sock的套接字
	fd_max = serv_sock;

	while (1)
	{
		cpy_reads = reads;
		timeout.tv_sec = 5;
		timeout.tv_usec = 5000;

		//这里使用select
		if (-1 == (fd_num = select(fd_max+1, &cpy_reads, 0, 0, &timeout)))
			break;

		if (0 == fd_num)
			continue;

		for (i=0; i<fd_max+1; i++)
		{
			if (FD_ISSET(i, &cpy_reads))	//如果状态有变化则执行
			{
				if (i == serv_sock)
				{
					adr_sz = sizeof(clnt_adr);
					clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);
					FD_SET(clnt_sock, &reads);

					if (fd_max < clnt_sock)
					{
						fd_max = clnt_sock;
					}

					printf("connected client: %d \n", clnt_sock);
				}
				else
				{
					str_len = read(i, buf, BUF_SIZE);
					if (0 == str_len)
					{
						//从reads删除相关信息
						FD_CLR(i, &reads);
						close(i);
						printf("closed client: %d \n",i);
					}
					else
					{
						//有数据的时候 将执行回声
						write(i, buf, str_len);
					}
				}
			}
		}
	}

	close(serv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

