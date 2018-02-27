#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>

//#include "../include/proto.h"
#include <proto.h>

int main(int argc,char **argv)
{
    int sd;
    struct sockaddr_in laddr,raddr;
	socklen_t raddr_len;
    struct denglu_st dl;

    sd = socket(AF_INET,SOCK_DGRAM,0);
    if(sd < 0)
    {
        perror("socket()");
        exit(1);
    }

	laddr.sin_family = AF_INET;
    laddr.sin_port = htons(DEFAULT_SERVER_PORT);
    inet_pton(AF_INET,DEFAULT_SERVER_IP,&laddr.sin_addr);
    if(bind(sd,(void *)&laddr,sizeof(laddr)) < 0)
    {
        perror("bind()");
        exit(1);
    }
	
	raddr_len = sizeof(raddr);

	if(recvfrom(sd,&dl,sizeof(dl),0,(void *)&raddr,&raddr_len) < 0)
    {
         perror("recvfrom()");
         exit(1);
    }

	// 去数据库中验证用户信息的真实性

	dl.status = DENGLU_STATUS_ERROR;
	if(sendto(sd,&dl,sizeof(dl),0,(void *)&raddr,sizeof(raddr)) < 0)
	{
		perror("sendto()");
		exit(1);
	}

	puts("ok!");


	while(1);


	close(sd);

	exit(0);

}
