#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <string.h>  
#include <errno.h>  
#include <netdb.h>  
  
#define SERVER_PORT         3333  
#define BUF_SIZE            1024  
  
int main(int argc, char *argv[]){  
    if(argc != 2){  
        printf("Usage: %s hostname\n",argv[0]);  
        exit(EXIT_FAILURE);  
    }  
  
    int client_fd;  
    struct sockaddr_in server_addr;  
    struct hostent *host;  
    char buf[BUF_SIZE] = {0};  
  
    bzero(&server_addr,sizeof(struct sockaddr_in));  
  
    //通过域名得到IP  
    if((host = gethostbyname(argv[1])) == NULL){  
        switch(h_errno)    
            {    
             case HOST_NOT_FOUND :    
                 printf("The specified host is unknown\n");    
                 break;    
    
             case NO_ADDRESS:    
                 printf("The requested name is valid but does not have an IP address.\n");    
                 break;    
    
             case NO_RECOVERY:    
                 printf(" A nonrecoverable name server error occurred.\n");    
                 break;    
    
             case TRY_AGAIN:    
                 printf("A temporary error occurred in the authoritative \  
                         domain name server. Please try again later.\n");    
                 break;    
            }  
        exit(EXIT_FAILURE);  
    }  
  
    //创建套结字  
    client_fd = socket(AF_INET, SOCK_STREAM , 0);  
    if(client_fd == -1){  
        fprintf(stderr,"Socket error:%s",strerror(errno));  
        exit(EXIT_FAILURE);  
    }  
  
    //填充服务端sockaddr结构  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(SERVER_PORT);  
    server_addr.sin_addr = *((struct in_addr*)host->h_addr);  
      
    //连接服务器  
    if((connect(client_fd, (struct sockaddr *)(&server_addr),sizeof(struct sockaddr_in))) == -1){  
        fprintf(stderr,"Connect error:%s",strerror(errno));  
        exit(EXIT_FAILURE);  
    }  
  
    while(1){  
        scanf("%s",buf);  
        if(strcmp(buf,"Quit") == 0){  
            break;  
        }  
    //发送数据  
        if((send(client_fd,buf,sizeof(buf),0)) == -1){  
            fprintf(stderr,"Connect error:%s",strerror(errno));  
            exit(EXIT_FAILURE);  
        }  
    }  
  
    close(client_fd);  
}  