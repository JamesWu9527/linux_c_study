/*
关于文件的操作
读取文件内容
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE    100

int main()
{
    int fd;
    char buf[BUF_SIZE];
    
    //open file    
    fd = open("data.txt", O_RDONLY);
    if (-1 == fd)
    {
        printf("open file error");
        exit(-1);
    }
    printf("file descriptor:%d \n", fd);
    
    //read file
    if (-1 == read(fd, buf, sizeof(buf)))
    {
        printf("read file error");
        exit(-1);
    }
    printf("file data: %s", buf);
    
    close(fd);
    return 0;
    
}
