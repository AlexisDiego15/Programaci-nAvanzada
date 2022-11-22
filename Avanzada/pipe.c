#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int fd[2], nbytes; //Declaracion pipes
	pid_t hijo;
	char string[]="Este es un mensaje\n";
	char readbuffer[80];
	
	pipe(fd);
	//Comprobacion de la creacion pipe
	if((hijo=fork())==-1)
	{
		printf("Ocurrio un error en el fork\n");
		exit(1);
	}
	if(hijo==0)
	{
	//Cierre del descriptor de entrada en el hijo
		close(fd[0]);
	//Enviar el saludo vía descriptor de salida
		write(fd[1],string,strlen(string));
		exit(0);
	}
	else
	{
	//Cierre del descriptor de salida en el padre
		close(fd[1]);
	
	//Leer algo de la tuberia
	nbytes = read(fd[0],readbuffer, sizeof(readbuffer));
	printf("Cadena recibida: %s", readbuffer);		
	}
return(0);
}
