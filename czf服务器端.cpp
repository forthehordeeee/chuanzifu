#include <stdio.h>  
#include <stdlib.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <arpa/inet.h>  
#include <string.h>  
#include <errno.h>  
  
#define PROT_NUMBER     3333  
#define LINK_NUMBER     20  
#define BUF_SIZE        1024  
int main(int argc, char *argv[]){  
      
    int server_fd, new_sockfd, sin_size;  
    struct sockaddr_in server_addr,client_addr;  
    char buf[BUF_SIZE] = {0};  
  
    bzero(&server_addr, sizeof(struct sockaddr_in));  
    bzero(&client_addr, sizeof(struct sockaddr_in));  
    //创建socket套结字  
    server_fd = socket(AF_INET,SOCK_STREAM,0);/*AF_INET：IPv4；SOCKET_STREAM: TCP*/  
    if(server_fd == -1){  
        fprintf(stderr, "Socket Error %s\n\a", strerror(errno));  
        exit(EXIT_FAILURE);  
    }  
    //填充socket套结字  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_port = htons(PROT_NUMBER);  
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
  
    //绑定套结字  
    if((bind(server_fd, (struct sockaddr *)(&server_addr),sizeof(struct sockaddr_in))) == -1){  
        fprintf(stderr, "Bind Error %s\n\a", strerror(errno));  
        exit(EXIT_FAILURE);  
    }  
      
    //设置最大连接数  
    if((listen(server_fd, LINK_NUMBER)) == -1){  
        fprintf(stderr, "Listen Error %s\n\a", strerror(errno));  
        exit(EXIT_FAILURE);  
    }  
  
      
        sin_size = sizeof(struct sockaddr_in);  
        //服务器阻塞，等待客户端链接  
        if((new_sockfd = accept(server_fd,(struct sockaddr *)(&client_addr),&sin_size)) == -1){  
            fprintf(stderr, "Accept Error %s\n\a", strerror(errno));  
            exit(EXIT_FAILURE);  
        }  
        fprintf(stdout,"Server get connection from %s\n",inet_ntoa(client_addr.sin_addr));  
    while(1){  
        //接收客户端发送的内容  
        if((recv(new_sockfd,buf,BUF_SIZE,0)) == -1){  
            fprintf(stderr, "Recv Error %s\n\a", strerror(errno));  
            exit(EXIT_FAILURE);  
        }  
        else if(*buf == '\0'){  
            break;  
        }  
          
        printf("Server received %s\n",buf);  
        bzero(&buf,BUF_SIZE);  
    }  
  
    close(server_fd);  
  
    return 0;  
}  