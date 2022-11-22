#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>

#define MAX_BUFFER 8
#define DATOS_A_PRODUCIR 20

void* Productor(void* var);

void* Consumidor(void* var);


sem_t elementos;
sem_t huecos;
//sem_t mutex;

int buffer[MAX_BUFFER];

void main(void){
	pthread_t th1,th2;

//inicializar los semaforos
	sem_init(&elementos,0,0);
	sem_init(&huecos,0,MAX_BUFFER);
	
	//sem_init(&NombreVariableSem,0(TipodDeProceso),0(Valor));
//crear los procesos ligeros
	pthread_create(&th1,NULL,Productor,NULL);
	pthread_create(&th2,NULL,Consumidor,NULL);

//espera su finalizacion

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	sem_destroy(&huecos);
	sem_destroy(&elementos);

	exit(0);


}

void* Productor(void* var){
	int pos=0;
	int i;
	for(i=0;i<DATOS_A_PRODUCIR;i++){
	//un hueco menos
		sem_wait(&huecos);//p
		buffer[pos]=i;
		printf("Dato producido: %i\n",buffer[pos]);
		pos=(pos+1)%MAX_BUFFER;		
		sem_post(&elementos);//V
		}
	pthread_exit(0);

}


void* Consumidor(void* var){
	int pos=0;
	int dato,i;
	for(i=0;i<DATOS_A_PRODUCIR;i++){
		//une elemento menos
		sem_wait(&elementos);
		dato=buffer[pos];
		printf("elemento consumido %i\n",dato);
		pos=(pos+1)% MAX_BUFFER;
		sem_post(&huecos);
	}
	
	pthread_exit(0);

	}

