#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	int fd[2], nbytes;
	pid_t hijo;
	char string[]="Este es un mensaje\n";
	char readbuffer[80];
	
	pipe(fd);
	
	if((hijo=fork())==-1){
		printf("Ocurrio un error en la creacion del hijo\n");
		exit(1);
	}
	
	if(hijo==0){
		//cierre del descriptor de entrada en el hijo
		close(fd[0]);	
		
		//enviar el saludo via descriptor de salida
		write(fd[1], string, strlen(string));
		exit(0);
	}
	else{
		//cierre del descriptor en la salida del padre
		close(fd[1]);
		
		//leer algo de la tuberia
		nbytes = read(fd[0], readbuffer,sizeof(readbuffer));
		printf("Cadena recibida: %s", readbuffer);
	
	}
	return 0;
}

