//MARQUINA ZENDEJAS VICTOR
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <pthread.h>

#define filosofos 5
typedef enum {Tenedores, Jarra, Espera} state_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
state_t state[filosofos];   
sem_t sem[filosofos]; 
#define LD(pos_filo) ((pos_filo+1)%filosofos)
#define LI(pos_filo)  ((pos_filo+(filosofos-1))%filosofos)

void orden(int pos_filo);
void mutex_espera(int pos_filo);
void mutex_agua(int pos_filo);
void *funcion_filo(void *argumento);
void funcion_agua(int pos_filo);
void funcion_comida(int pos_filo);

int main()
{
int pos_filo, *argumento;
pthread_t id[filosofos];
int j;
	
	//Inicializacion semaforos
for(j=0; j<filosofos;j++)
	{
	        sem_init(&sem[j], 0, 0 );
    	}    
    
for(pos_filo=0;pos_filo<filosofos;pos_filo++) 
	{
	        argumento=(int *)malloc(sizeof(int));
		*argumento=pos_filo;
	        pthread_create(&id[pos_filo],NULL,funcion_filo,argumento);
	}
	
	//Espera de los procesos
for(pos_filo=0;pos_filo<filosofos;pos_filo++)
	{
	        pthread_join(id[pos_filo],NULL);
        }
	
	//Destruccion semaforos
for(j=0;j<filosofos;j++)
	{
	        sem_destroy(&sem[j]); 
        }
    return 0;
}

void orden(int pos_filo)
{
if(state[pos_filo]==Espera && state[LI(pos_filo)]!=Tenedores && state[LD(pos_filo)]!=Tenedores)
	{
        	state[pos_filo]=Tenedores;
        	sem_post(&sem[pos_filo]);
	}
}

void mutex_espera(int pos_filo)
{
	pthread_mutex_lock(&mutex);
	state[pos_filo]=Espera;
	orden(pos_filo);                  
	pthread_mutex_unlock(&mutex);
	sem_wait(&sem[pos_filo]);
}

void mutex_agua(int pos_filo)
{
	pthread_mutex_lock(&mutex);
	state[pos_filo]=Jarra;
	orden(LI(pos_filo));            
	orden(LD(pos_filo));          
	pthread_mutex_unlock(&mutex);
}

void *funcion_filo(void *argumento)
{
	int pos_filo=*(int *)argumento;
	free(argumento);
	while(1)
	{
	funcion_agua(pos_filo);
      	mutex_espera(pos_filo);
	funcion_comida(pos_filo);
	mutex_agua(pos_filo);
	}

return NULL;
}

void funcion_agua(int pos_filo) // tomando
{
	printf("	Ha entrado a la funcion de agua\n");
	printf("Id del filosofo: [%li]\n",pthread_self());
	printf("El filosofo num: [%i] agarro la jarra, esta tomando agua, espere...\n",pos_filo+1);
	sleep(5);
}

void funcion_comida(int pos_filo) // comiendo
{
	printf("	Ha entrado a la funcion de comer\n");
	printf("Id del filosofo: [%li]\n",pthread_self());
	printf("El filosofo num: [%i] agarro los tenedores, esta comiendo, espere...\n",pos_filo+1);
	printf("El filosofo num: [%i] termino de comer\n",pos_filo+1);
	sleep(5);
}
