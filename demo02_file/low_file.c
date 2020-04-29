/*
关于文件的操作
创建新文件并保存数据
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int fd;
    char buf[] = "Let's go!\n";
    
    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if (-1 == fd)
    {
        printf("open function error");
        exit(-1);
    }
    printf("file description: %d\n",fd);
    
    //write data to this file
    if (-1 == write(fd, buf, sizeof(buf)))
    {
        printf("write function error");
        exit(-1);
    }
    
    close(fd);
    
    return 0;
}
