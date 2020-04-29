/*
about byte sequence conversion
use inet_ntoa function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main()
{
    struct sockaddr_in addr1,addr2;
    char *str_ptr;
    char str_arr[20];
    
    addr1.sin_addr.s_addr = htonl(0x10203040);
    addr2.sin_addr.s_addr = htonl(0x10101010);
    
    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);
    printf("notation1: %s\n", str_ptr);
    
    inet_ntoa(addr2.sin_addr);
    printf("notation2: %s\n", str_ptr);
    
    
    return 0;
}
