#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int hijos=1;

int main(void){
	int fd[2], fd2[2], nbytes;
	pid_t pid_hijo;
	//char string[]="Este es un mensaje\n";
	char readbuffer[80];
	
	pipe(fd);
	pipe(fd2);
		
	char string[]="Mensaje para papa";
	char string2[]="Mensaje para hijo";



	
	for(int i=0; i<hijos;i++){
		pid_hijo = fork();
		if(pid_hijo<0)
			printf("Ocurrio un error\n");
		if(pid_hijo==0){
			//printf("Proceso hijo %i,papa%i\n",getpid(),getppid());
		break;
		}else{continue;}
	}
	
	if(pid_hijo==-1){
		printf("Ocurrio un error en la creacion del hijo\n");
		exit(1);
	}
	
	if(pid_hijo==0){

		close(fd[1]);
		close(fd2[0]);
		
		nbytes = read(fd[0], readbuffer,sizeof(readbuffer));
		printf("Cadena recibida: %s\n", readbuffer);
		
		write(fd2[1],string,strlen(string));
		printf("Hijo %i ha enviado un mensaje\n",getpid());
		

		
		
		exit(0);
		
	}
	else{
		//cierre del descriptor en la salida del padre
		close(fd[0]);
		close(fd2[1]);
				printf("Papa ha enviado un mensaje\n");
		write(fd[1],string2,strlen(string2));
		//leer algo de la tuberia
		nbytes = read(fd2[0], readbuffer,sizeof(readbuffer));
		printf("Cadena recibida: %s\n", readbuffer);

	
	
	}
	return 0;
}

