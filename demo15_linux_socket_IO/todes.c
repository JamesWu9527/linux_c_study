/*
2020-5-19 14点59分
通过使用函数fdopen将文件描述符转换为FILE结构体指针
使用函数fileno进行一个可逆的转换 将FILE指针转换为文件描述符
*/

#include <stdio.h>
#include <fcntl.h>

int main()
{
	FILE *fp;
	int fd = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC);
	if (-1 == fd)
	{
		fputs("文件打开失败",stderr);
		return -1;
	}

	printf("文件描述符：%d\n", fd);
	fp = fdopen(fd,"w");
	fputs("JamesWu9527 \n",fp);
	printf("转换后的文件描述符：%d\n", fileno(fp));
	fclose(fp);	//这里的文件指针通过fclose关闭后，fd文件描述符将变成一个没有意义的整型变量
	return 0;
}