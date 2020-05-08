/*
2020/5/8 21点07分
文件传输的一个小例子
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define 	BUF_SIZE	30

void error_handling(char *message);

int main()
{
	int socked;
	FILE *fp;

	char buf[BUF_SIZE];
	int read_cnt;
	struct sockaddr_in serv_adr;

	fp = fopen("receive.dat","wb");
	socked = socket(PF_INET, SOCK_STREAM, 0);

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
	serv_adr.sin_port = htons(atoi("8888"));

	connect(socked, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	while (0 != (read_cnt = read(socked, buf, BUF_SIZE)))
	{
		fwrite((void*)buf, 1, read_cnt, fp);
	}

	puts("Received file data");

	//发给服务器端
	write(socked, "Thank you", 10);

	fclose(fp);
	close(socked);

	return 0;

}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}


