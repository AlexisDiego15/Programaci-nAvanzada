#include<stdio.h>
#include<unistd.h> //Lleva todo lo relacionado a los procesos
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t proc;
	printf("Soy el proceso %i\n", getpid());
	proc = fork();
	if(proc<0)
		printf("Ocurrio un error\n");
	if(proc==0)
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
	else
		printf("Proceso papa: %i abuelo %i\n", getpid(), getppid());
		wait(&proc);
exit(0);
}
