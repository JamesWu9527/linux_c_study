/*
about byte sequence conversion
use inet_addr function
*/

#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main()
{
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;
    
    if (!inet_aton(addr, &addr_inet.sin_addr))
    {
        printf("Conversion error");
    }
    else
    {
        printf("Network ordered integer addr: %#x \n",addr_inet.sin_addr.s_addr);
    }
    
    
    return 0;
}
