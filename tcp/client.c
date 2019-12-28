/*tcp client.c*/
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 128

int main (int argc,char *argv[]) 
{
	if(argc != 3) {

			printf("输入的参数有误！！！请输入服务器的IP和端口号\n");
			exit(-1);			
	}
	/*创建套接字*/
	int sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1) {

			perror("socket");
			exit(-1);
	}
	/*设置对方的IP和端口号*/
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	if(inet_pton(AF_INET,argv[1],(struct sockaddr *)&addr.sin_addr)<0) {

		perror("server ip error");
		exit(-1);
	}
	/*连接服务器*/
	if(connect(sockfd,(struct sockaddr*)&addr,sizeof(addr))<0) {

			perror("connect error");
			exit(-1);
	}
	char addrInfo[SIZE];
	bzero(addrInfo,sizeof(addrInfo));
	printf("成功连接到服务器:%s\n",inet_ntop(AF_INET,(struct sockaddr*)&addr.sin_addr,
		addrInfo,sizeof(addrInfo)));

	char msgbuf[SIZE];
	bzero(msgbuf,sizeof(msgbuf));
	/*收发消息*/
	while(1) {
				printf("请输入你想输入的消息:");
				fgets(msgbuf,sizeof(msgbuf),stdin);
				write(sockfd,msgbuf,strlen(msgbuf));
				if(strncmp(msgbuf,"bye",3) == 0) {

						break;
				}
				bzero(msgbuf,strlen(msgbuf));
				read(sockfd,msgbuf,sizeof(msgbuf));
				printf("接受到消息:%s\n",msgbuf);
				bzero(msgbuf,sizeof(msgbuf));
	}
	close(sockfd);
	return 0;
	
}