#include <stdio.h>
#include <fcntl>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_t id_hilo1;
pthread_t id_hilo2;
pthread_t id_hilo3;
pthread_t id_hilo4;

void *funcion_suma(void *argumento);
void *funcion_resta(void *argumento);
void *funcion_multiplicacion(void *argumento);
void *funcion_division(void *argumento);

int num=13;

sem_t suma;
sem_t resta;
sem_t mult;
sem_t divi;

	
int main()
{
sem_init(&suma,0,1);
sem_init(&resta,0,0);
sem_init(&mult,0,0);
sem_init(&divi,0,0);
printf("--------------> %d <------------------\n",num);
	
if(pthread_create(&id_hilo1, NULL, funcion_suma,NULL)) 
	{
		printf("Problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	
if(pthread_create(&id_hilo2, NULL, funcion_resta,NULL)) 
	{
		printf("Problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	
if(pthread_create(&id_hilo3, NULL, funcion_multiplicacion,NULL)) 
	{
		printf("Problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}

if(pthread_create(&id_hilo4, NULL, funcion_division,NULL)) 
	{
		printf("Problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}

pthread_join(id_hilo1,NULL);
pthread_join(id_hilo2,NULL);
pthread_join(id_hilo3,NULL);
pthread_join(id_hilo4,NULL);

sem_destroy(&suma);
sem_destroy(&resta);
sem_destroy(&mult);
sem_destroy(&divi);
}

void *funcion_suma(void *argumento)
{
//	printf("El codigo de la funcion esta en ejecucion\n El numero base es: %d\n",(int*)num);
	int j;
	for(j=0;j<5;j++)
	{
	sem_wait(&suma); //P
	printf("	Entro a la funcion de suma\n");
	printf("Proceso hijo: %li \n",pthread_self());
	num=num+3;
	printf("Se esta realizando una suma de +3\n");
	printf("El resultado es = %d\n",num);
	sem_post(&resta); //V
	printf("Termine la suma numero %d\n\n",j+1);
	}
}

void *funcion_resta(void *argumento)
{
//	printf("El codigo de la funcion esta en ejecucion\n El numero base es: %d\n",(int*)num);
	int j;
	for(j=0;j<5;j++)
	{
	sem_wait(&resta); //P
	printf("	Entro a la funcion de resta\n");
	printf("Proceso hijo: %li \n",pthread_self());
	num=num-2;
	printf("Se esta realizando una resta de -2\n");
	printf("El resultado es = %d\n",num);
	sem_post(&mult); //V
	printf("Termine la resta numero %d\n\n",j+1);
	}
}

void *funcion_multiplicacion(void *argumento)
{
//	printf("El codigo de la funcion esta en ejecucion\n El numero base es: %d\n",(int*)num);
	int j;
	for(j=0;j<5;j++)
	{
	sem_wait(&mult); //P
	printf("	Entro a la funcion de mult\n");
	printf("Proceso hijo: %li \n",pthread_self());
	num=num*(4);
	printf("Se esta realizando una multiplicacion por 4\n");
	printf("El resultado es = %d\n",num);
	sem_post(&divi); //V
	printf("Termine la multiplicacion numero %d\n\n",j+1);
	}
}

void *funcion_division(void *argumento)
{
//	printf("El codigo de la funcion esta en ejecucion\n El numero base es: %d\n",(int*)num);	
	int j;
	for(j=0;j<5;j++)
	{
	sem_wait(&divi); //P
	printf("	Entro a la funcion de div\n");
	printf("Proceso hijo: %li \n",pthread_self());
	num=num/(2);
	printf("Se esta realizando una division entre 2\n");
	printf("El resultado es = %d\n",num);
	sem_post(&suma); //V
	printf("Termine la division numero %d\n\n",j+1);
	}
}
