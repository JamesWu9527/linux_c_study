/*
2020-5-19 12点14分
测试writev函数
*/

#include <stdio.h>
#include <sys/uio.h>

int main()
{
	struct iovec vec[2];
	char buf1[] = "JamesWu9527";
	char buf2[] = "123456";

	int str_len;
	vec[0].iov_base = buf1;
	vec[0].iov_len = 3;
	vec[1].iov_base = buf2;
	vec[1].iov_len = 3;

	str_len = writev(1, vec, 2);
	puts("");
	printf("write bytes: %d \n", str_len);

	return 0;
}
