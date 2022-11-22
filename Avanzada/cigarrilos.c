#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<time.h>

void * func_cerillo(void* argumento);
void * func_tabaco(void* argumento);
void * func_papel(void* argumento);
void * func_agente(void* argumento);

sem_t sem_cerillo;
sem_t sem_tabaco;
sem_t sem_papel;
sem_t sem_agente;

void main(void)
{
// o es papel
// 1 es tabaco
// 2 es cerillo
	while(1)
	{
		pthread_t th1;
		pthread_t th2;
		pthread_t th3;
		pthread_t th4;	

		sem_init(&sem_agente,0,1);
		sem_init(&sem_papel,0,0);
		sem_init(&sem_tabaco,0,0);
		sem_init(&sem_cerillo,0,0);
	
		pthread_create(&th4,NULL,func_agente,NULL);
		pthread_create(&th1,NULL,func_tabaco,NULL);
		pthread_create(&th2,NULL,func_papel,NULL);
		pthread_create(&th3,NULL,func_cerillo,NULL);
	
		pthread_join(th4,NULL);
		pthread_join(th1,NULL);
		pthread_join(th2,NULL);
		pthread_join(th3,NULL);
		
		sem_destroy(&sem_tabaco);
		sem_destroy(&sem_papel);
		sem_destroy(&sem_cerillo);
		sem_destroy(&sem_agente);
	exit(0);
	
	}
}

void * func_agente(void* argumento)
{
	int ingrediente, ingrediente1;
while(1)
{	
	do
	{
		ingrediente=rand()%3;
		ingrediente2=rand()%3;
	}
	while(ingrediente==ingrediente1);

	if((ingrediente==0)&&(ingrediente2==1)||(ingrediente==1)&&(ingrediente2==0))
	{
		sem_post(&sem_cerillo);
		sem_wait(&sem_agente);
	}
	
	if((ingrediente==0)&&(ingrediente2==2)||(ingrediente==2)&&(ingrediente2==0))
	{
		sem_post(&sem_tabaco);
		sem_wait(&sem_agente);
	}
	
	if((ingrediente==1)&&(ingrediente2==2)||(ingrediente==2)&&(ingrediente2==1))
	{
		sem_post(&fum_papel);
		sem_wait(&se_agente);
	}
	}
}


void * func_tabaco(void* argumento)
{
	while(1)
	{
	//printf("Se ha entrado a la func del tabaco\n");
	sem_wait(&sem_tabaco);
	printf("---Proceso del tabaco---\n");
	printf("Fumando, espere....\n");
	sleep(3);
	sem_post(&sem_agente);		
	}
}
void * func_papel(void* argumento)
{
	while(1)
	{
	//printf("Se ha entrado a la func del papel\n");
	sem_wait(&sem_papel);
	printf("---Proceso del papel---\n");
	printf("Fumando, espere....\n");
	sleep(3);
	sem_post(&sem_agente);
	}
}

void * func_cerillo(void* argumento)
{
	while(1)
	{
	//printf("Se ha entrado a la func del cigarillo");
	sem_wait(&sem_cerillo);
	printf("---Proceso de los cigarrillos---\n");
	printf("Fumando, espere....\n");
	sleep(3);
	sem_post(&sem_agente);	
	}
}
