#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     8080 
#define MAXLINE 1024 
  
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    int n, len, num, numConver, status;


    while(1){
        scanf("%d",&num);
        //__fpurge(stdin);
        fflush(stdout);
        numConver = htonl(num);
        sendto(sockfd, &numConver, sizeof(numConver), MSG_CONFIRM, (const struct sockaddr *) &servaddr, sizeof(servaddr));   

    }
          
      
    close(sockfd); 
    return 0; 
    
} 
