#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void escribir(int numerito)
{
	FILE *pid;
	pid = fopen("PID.txt","a");
	fprintf(pid, "%i\n",numerito);
	fclose(pid);
}

void leer()
{
	FILE *pid;
	pid = fopen("PID.txt","r");
	char cadena[20];
	
	if(pid == NULL)
	{
		printf("\nNo se pudo cargar correctamente el archivo...\n");
	}
	else
	{
		printf("\nLa informacion dentro del archivo es:");
		fscanf(pid,"%s",cadena);
		while(!feof(pid))
		{
			printf("\n%s",cadena);
			fscanf(pid,"%s",cadena);
		}
		printf("\n");
		fclose(pid);
	}
}

void leerC()
{
	FILE *pid;
	pid = fopen("Carta.txt","r");
	char cadena[90];
	
	printf("La informacion dentro del archivo es:\n");
	fscanf(pid,"%s",cadena);
	while(!feof(pid))
	{
		printf("%s ",cadena);
		fscanf(pid,"%s",cadena);
	}
	printf("\n");
	fclose(pid);
}

void limpiar()
{
	FILE *pi;
	pi = fopen("Carta.txt","w");
	printf("\nSe ha borrado la carta\n");
	fclose(pi);
}

int main()
{
	int proc[4], pid[4], fuji[4], i, j;
	FILE *pi;
	pi = fopen("PID.txt","w");
	fclose(pi);
	
	for(i = 0; i < 4; i++)
	{
		proc[i]= fork();
		if(proc[i] < 0)
		{
			printf("\nOcurrio un error\n");
		}
		else if(proc[i] == 0)
		{
			pid[i] = getpid();
			escribir(getpid());
			break;
		}
		else
		{
			wait(&proc[i]);
		}
	}
	
	if(proc[i] == 0)
	{
		for(int i = 0; i < 4; i++)
		{
			if((pid[i] > 0) && (pid[i] < 40000))
			{
				fuji[i] = pid[i];
			}
		}
	}
	
	if(proc[i] == 0)
	{
		pi = fopen("Carta.txt","a");
		fseek(pi, 0, SEEK_END);
		if(ftell(pi) == 0)
		{
			if(getpid() == fuji[0])
			{
				printf("Se ha impreso el mensaje en el archivo");
				fprintf(pi, "\nHa recibido un saludo de su hermano %i",getpid());
				fclose(pi);
				exit(0);
			}
			else if(getpid() == fuji[1])
			{
				printf("Se ha impreso el mensaje en el archivo");
				fprintf(pi, "\nHa recibido un saludo de su hermano %i",getpid());
				fclose(pi);
				exit(0);
			}
			else if(getpid() == fuji[2])
			{
				printf("Se ha impreso el mensaje en el archivo");
				fprintf(pi, "\nHa recibido un saludo de su hermano %i",getpid());
				fclose(pi);
				exit(0);
			}
			else if(getpid() == fuji[3])
			{
				printf("Se ha impreso el mensaje en el archivo");
				fprintf(pi, "\nHa recibido un saludo de su hermano %i",getpid());
				fclose(pi);
				exit(0);
			}
		}
		else
		{
			if(getpid() == pid[0])
			{
				fclose(pi);
				leerC();
				limpiar();
				exit(0);
			}
			else if(getpid() == fuji[1])
			{
				fclose(pi);
				leerC();
				limpiar();
				exit(0);
			}
			else if(getpid() == fuji[2])
			{
				fclose(pi);
				leerC();
				limpiar();
				exit(0);
			}
			else if(getpid() == fuji[3])
			{
				fclose(pi);
				leerC();
				limpiar();
				exit(0);
			}
		}
	}
	
	//printf("%i\n",fuji[i]);
	//printf("Cuantos 'hola' salen aqui?\n");
	
	exit(0);
}

