/*
2020-5-19 14点47分
通过使用函数fdopen将文件描述符转换为FILE结构体指针
*/

#include <stdio.h>
#include <fcntl.h>

int main()
{
	FILE *fp;
	int fd = open("data.txt", O_WRONLY|O_CREAT|O_TRUNC);
	if (-1 == fd)
	{
		fputs("文件打开失败",stderr);
		return -1;
	}

	fp = fdopen(fd,"w");
	fputs("JamesWu9527 \n",fp);
	fclose(fp);	//这里的文件指针通过fclose关闭后，fd文件描述符将变成一个没有意义的整型变量
	return 0;
}