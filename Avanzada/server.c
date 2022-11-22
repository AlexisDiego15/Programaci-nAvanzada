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

int calculo=0;
int num[4], aux = 0;
char *hello = "Hello from server"; 
int sockfd, len; 
char buffer[MAXLINE];
  
struct sockaddr_in servaddr, cliaddr; 
   
int main() {    
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 

    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 
      
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    int  n, numRecib, numRecibConv; 
  
    len = sizeof(cliaddr);  
  
    while(calculo < 500){
        aux++;
        recvfrom(sockfd, &numRecib, sizeof(numRecib), MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
        numRecibConv = ntohl(numRecib);
        num[aux] = numRecibConv;

        printf("num(%d): %d\n", aux, num[aux]); 

        if(aux == 4){
            	calculo = ((num[1] + num[4]) * num[2]) - num[3];
		printf("%d\n",calculo);
        if (calculo < 500){
            	printf("Datos no son correctos \n Vuelva a introducir los numeros\n");
            	
        }else{
            	printf("Datos correctos\n");
        }
		fflush(stdout);
       	aux = 0;
	}
    }
    
    close(sockfd);      
    return 0; 
} 
