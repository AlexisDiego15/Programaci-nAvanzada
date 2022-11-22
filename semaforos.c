#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>


#define MAX_BUFFER 10 
#define DATOS_A_PRODUCIR 100
sem_t elementos;
sem_t huecos;
int buffer[MAX_BUFFER];

void *Productor(void *argumento){
	int pos=0;
	int dato;
	int i;

	for(i=0; i<DATOS_A_PRODUCIR; i++){
		dato=i; 
 		sem_wait(&huecos);
 		buffer[pos]=i;
 		pos=(pos+1) % MAX_BUFFER;
 
 		printf("Dato Productor: %i \n", dato);
 		sleep(2);
 
 		sem_post(&elementos);
 	}
 	pthread_exit(0);
}
 
 void *Consumidor(void *argumento){

	int pos=0;
	int dato;
	int i;

	for(i=0; i<DATOS_A_PRODUCIR; i++){
 
		sem_wait(&elementos);
		dato=buffer[pos];
		pos=(pos+1) % MAX_BUFFER;
 
 		printf("Dato Consumidor: %i \n", dato);
		sleep(2);
 
	 	sem_post(&huecos);
	 }
	 pthread_exit(0);
}
 

int main(){ 
	pthread_t th1, th2;

	sem_init(&elementos, 0, 0);
	sem_init(&huecos, 0, MAX_BUFFER);


	pthread_create(&th1, NULL,Productor, NULL);
	pthread_create(&th2, NULL,Consumidor, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	sem_destroy(&huecos);
	sem_destroy(&elementos);

	exit(0);
}



