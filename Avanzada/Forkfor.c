#include<stdio.h>
#include<unistd.h> //Lleva todo lo relacionado a los procesos
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>

FILE *a;

void leer(int numero)
{
	int dato_leer; 
	a=fopen("archivo.txt","r");
	fscanf(a,"%d",&dato_leer);
	printf("El dato %d ha sido extraido\n", dato_leer);
	fclose(a);
}

void escritura(int numero)
{
	int n = numero;
	a=fopen("archivo.txt","w");
	fprintf (a, "%d %c", n, '\n');
    	fclose(a);
	
}


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
		{
		printf("Proceso hijo: %i, papa %i\n", getpid(), getppid());
		break;
		}
	else
		printf("Proceso papa: %i", getpid());
	}
	while(1)
	{
		if(proc==0)
		{
			if(a==NULL)
			{
				printf("Soy el proceso que escribe: %i\n \n",getpid());
				escritura(getpid());
			}
			else
			{
				printf("Soy el proceso que lee: %i\n",getpid());
				leer(getpid());
			}
		}
	}
	wait(&proc);
exit(0);
}
