/*
2020/5/9
通过地址获取host信息
使用函数 gethostbyaddr
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message);

int main()
{
	int i;
	struct hostent *host;
	struct sockaddr_in addr;
	
	char strDoName[20];
	puts("请输入地址：");
	gets(strDoName);

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = inet_addr(strDoName);
	host = gethostbyaddr((char*)&addr.sin_addr, 4, AF_INET);
	if (!host)
	{
		error_handling("gethost.... error");
	}

	printf("Official name: %s \n", host->h_name);
	for (i=0; host->h_aliases[i]; i++)
	{
		printf("Aliases %d %s \n", i+1, host->h_aliases[i]);
	}

	printf("Addrss type: %s \n", (host->h_addrtype == AF_INET? "IPV4":"IPV6"));

	for (i=0; i<host->h_addr_list[i]; i++)
	{
		printf("IP addr %d %s \n", i+1, inet_ntoa(*(struct in_addr*)host->h_addr_list[i]));
	}
	
	return 0;
}

void error_handling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

/*
运行结果：
jameswu@ubuntu:/mnt/hgfs/trunk/demo08_dns$ ./gethostbyname
请输入域名：
www.baidu.com
Official name: www.a.shifen.com 
Aliases 1 www.baidu.com 
Addrss type: IPV4 
IP addr 1 163.177.151.110 
IP addr 2 163.177.151.109 
*/

