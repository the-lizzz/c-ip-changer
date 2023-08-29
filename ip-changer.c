#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int main()
{
    unsigned char ip_address[15];
    unsigned char interface[100];
    int fd;
    struct ifreq ifr;
    struct sockaddr_in* addr;
    printf("cic/ip>");
    scanf("%s", ip_address);
    FILE *fptr;
    fptr = fopen("var.h", "w");
    fprintf(fptr, "%s",ip_address);
    fclose(fptr);
    printf("cic/interface>");
    scanf("%s",interface);
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    memcpy(ifr.ifr_name,interface, IFNAMSIZ - 1);
    addr = (struct sockaddr_in*)&ifr.ifr_addr;
    inet_pton(AF_INET, ip_address, &addr->sin_addr);
    ioctl(fd, SIOCSIFADDR, &ifr);
    close(fd);
    memset((unsigned char*)ip_address, 0x20, 15);
    ioctl(fd, SIOCGIFADDR, &ifr);
    strcpy(ip_address, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
    return 0;
}
