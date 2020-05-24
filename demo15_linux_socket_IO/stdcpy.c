/*
2020-5-19 14点32分
使用标准I/O
fgets和fputs来复制文件
基于缓冲的复制
*/

#include <stdio.h>

#define BUF_SIZE	3

int main()
{
	FILE *fp1;
	FILE *fp2;
	char buf[BUF_SIZE];

	fp1 = fopen("test.txt", "r");	//只读
	fp2 = fopen("cpy.txt", "w");

	while (fgets(buf, BUF_SIZE, fp1) != NULL)
	{
		fputs(buf, fp2);
	}

	fclose(fp1);
	fclose(fp2);
	
	return 0;
}


