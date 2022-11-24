#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>

sem_t sem_CA;
sem_t sem_CB;


void *PuenteArriba(void *argumento);
void *PuenteAbajo(void *argumento);
void *Carros(void *argumento);
void *Barcos(void *argumento);

int carros=100;
int barcos=100;
int filaA=0;
int filaB=0;
int banderaCarro=0;
int banderaBarco=0;


pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;

void *Carros(void *argumento){
	pthread_mutex_lock (&mutex);
	banderaCarro=rand()%2;
	banderaBarco=rand()%2;
	sleep(1);
	sem_wait(&sem_CA);
	if(banderaCarro==1){
		printf("Soy el carro %ld cruzando el puente, el puente esta abajo \n",pthread_self());
		filaA++;
		
		
		if(banderaBarco==0){
			printf("No hay Barco\n");
			sleep(1);
			sem_post(&sem_CA);
			pthread_mutex_unlock (&mutex);
		}
		else{
			printf("Se aproxima Barco\n");
			sleep(2);
			printf("Puente abajo\n");
			sem_post(&sem_CB);
			pthread_mutex_unlock (&mutex);
		}
	
	}else{
		
		printf("\nNo pasan carros\n");
		sleep(2);
		sem_post(&sem_CB);
		pthread_mutex_unlock (&mutex);

	}	
	
	
}
void *PuenteArriba (void *argumento){
pthread_t hilo_A[carros];
	
	while(carros<101){
	for(int i=0;i<carros;i++){
	if(pthread_create(&hilo_A[i],NULL,*Carros,NULL)){
		printf("problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	}

	for(int i=0;i<carros;i++){
	if(pthread_join(hilo_A[i], NULL)){
		printf("problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	}
	}
}


void *Barcos(void *argumento){
pthread_mutex_lock (&mutex1);

	sleep(1);
	sem_wait(&sem_CB);

		printf("Soy el barco %ld cruzando por el mar, el puente esta levantado \n",pthread_self());
		filaB++;
		sleep(3);
		printf("Puente arriba\n");
		sem_post(&sem_CA);
		pthread_mutex_unlock (&mutex1);
	
	
}

void *PuenteAbajo(void *argumento){
	sleep(2);
	pthread_t hilo_B[barcos];
	while(barcos<101){
		for(int i=0;i<barcos;i++){
		if(pthread_create(&hilo_B[i],NULL,*Barcos,NULL)){
			printf("problema en la creación del hilo\n");
			exit(EXIT_FAILURE);
		}
		}
		for(int i=0;i<barcos;i++){
			if(pthread_join(hilo_B[i], NULL)){
				printf("problema en la creación del hilo\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}



void main(void){
	pthread_t hilo_CA,hilo_CB;;

	sem_init(&sem_CA,0,1);
	sem_init(&sem_CB,0,0);


	if(pthread_create(&hilo_CA,NULL,*PuenteArriba,NULL)){
		printf("Error al crear hilo 0\n");
		exit(EXIT_FAILURE);
	}

	if(pthread_create(&hilo_CB,NULL,*PuenteAbajo,NULL)){
		printf("Error al crear hilo 0\n");
		exit(EXIT_FAILURE);
	}


	if(pthread_join(hilo_CA,NULL)){
		printf("Problema en el enlace del hilo \n");
		exit(EXIT_FAILURE);
	}

	if(pthread_join(hilo_CB,NULL)){
		printf("Problema en el enlace del hilo \n");
		exit(EXIT_FAILURE);
	}

	sem_destroy(&sem_CA);
	sem_destroy(&sem_CB);
	exit(0);
}



