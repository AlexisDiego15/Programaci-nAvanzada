#include<stdio.h>
#include<unistd.h> //Lleva todo lo relacionado a los procesos
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

int main()
{
	pid_t proc;
	int i;
	for(i=0;i<3;i++)
	{
	printf("Soy el proceso %i\n", getpid());
	proc = fork();
	if(proc<0)
		printf("Ocurrio un error\n");
	if(proc==0)
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
	else
		{
		wait(&proc);
		break;
		}
	}
exit(0);
}
