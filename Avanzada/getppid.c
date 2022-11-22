#include<stdio.h>
#include<unistd.h> //Lleva todo lo relacionado a los procesos
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	int proc;
	int proc2; int proc3;
	proc = fork();
	if(proc<0)
		printf("Ocurrio un error\n");
	if(proc==0)
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
	else
		//printf("Proceso papa: %i\n", getpid());
	wait(&proc);
	proc2 = fork();
	if(proc2<0)
		printf("Ocurrio un error\n");
	if(proc2==0)
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
	else
		//printf("Proceso papa: %i\n", getpid());
	wait(&proc2);
	if(proc<0)
		printf("Ocurrio un error\n");
	if(proc3==0)
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
	else
		//printf("Proceso papa: %i\n", getpid());
	wait(&proc3);
exit(0);
}
