/*
2020-5-14 15点29分
使用select函数
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE	30

int main()
{
	fd_set reads, temps;
	int result, str_len;
	char buf[BUF_SIZE];
	struct timeval timeout;

	//初始化fd_set变量
	FD_ZERO(&reads);
	FD_SET(0, &reads);

	while (1)
	{
		temps = reads;
		
		//设置5秒超时
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		result = select(1, &temps, 0, 0, &timeout);
		if (-1 == result)
		{
			puts("select() error!");
		}
		else if (0 == result)
		{
			puts("time out");
		}
		else
		{
			if (FD_ISSET(0, &temps))
			{
				str_len = read(0, buf, BUF_SIZE);
				buf[str_len] = 0;
				printf("message from console: %s", buf);
			}
		}
	}
	
	return 0;
}
