/*
2020-5-19 14点27分
使用系统函数
read,write来复制文件
*/

#include <stdio.h>
#include <fcntl.h>

#define BUF_SIZE	3

int main()
{
	int fd1, fd2;
	int len;
	char buf[BUF_SIZE];

	fd1 = open("test.txt", O_RDONLY);	//只读
	fd2 = open("cpy.txt", O_WRONLY | O_CREAT | O_TRUNC);

	while ((len = read(fd1, buf, sizeof(buf))) > 0)
	{
		write(fd2, buf, len);
	}

	close(fd1);
	close(fd2);
	
	return 0;
}

