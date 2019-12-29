/*tcp server*/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128

int main(int argc,char *argv[])
{
	if(argc != 3) {

			printf("输入参数有误!!! 请输入服务器的IP和端口\n");
			exit(-1);
	}
	/*创建套接字*/
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1) {

			perror("socket");
			exit(-1);
	}
	/*设置自己的IP和端口号*/
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],(struct sockaddr*)&addr.sin_addr)<0) {
	
			printf("server ip error\n");
			exit(-1);
	}
	/*绑定套接字*/
	if(bind(sockfd,(struct sockaddr*)&addr,sizeof(addr)) == -1) {

			perror("bind");
			exit(-1);
	}
	/*监听套接字*/
	if (listen(sockfd,5)<0) {

			perror("listen");
			exit(-1);
	}
	struct sockaddr_in cliaddr;
	bzero(&cliaddr,sizeof(cliaddr));
	int len = sizeof(cliaddr);
	/*接受客户端连接 返回通讯套接字*/
	int sockcon = accept(sockfd,(struct sockaddr*)&cliaddr,&len);
	if(sockcon == -1) {

			perror("accept");
			exit(-1);
	}
	char addrInfo[SIZE];
	bzero(addrInfo,sizeof(addrInfo));
	printf("客户端:[%s]成功连接\n",inet_ntop(AF_INET,(struct sockaddr*)&cliaddr.sin_addr,
		addrInfo,sizeof(addrInfo)));
	/*收发消息*/
	char msgBuf[SIZE];
	bzero(msgBuf,sizeof(msgBuf));
	while(1) {
			bzero(msgBuf,sizeof(msgBuf));
			read(sockcon,msgBuf,sizeof(msgBuf));
			printf("接收到消息:%s\n",msgBuf);
			bzero(msgBuf,sizeof(msgBuf));
			printf("请输入你想输入的消息:");
			scanf("%s",msgBuf);
			write(sockcon,msgBuf,strlen(msgBuf));
			if(strncmp(msgBuf,"bye",3) == 0) {

					break;
			}
	}
	close(sockcon);
	return 0;
}
