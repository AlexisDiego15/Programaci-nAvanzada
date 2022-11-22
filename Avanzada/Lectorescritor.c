#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>

sem_t  sem_n;
sem_t acceso;
int  n=0;   
int palabra=0;
int leer;

FILE* archivo=NULL;

void leerbasedatos();
void escribirbasedatos();
void* lector();
void* escritor();


void main(void){

	pthread_t hilo1[10], hilo2[10];
	int i;
	sem_init(&acceso, 0, 1);
	sem_init(&sem_n, 0, 1);
	
	for(i=0; i<10; i++){
		if(pthread_create(&hilo1[i], NULL, escritor, NULL)){
			printf("Error al crear el hilo");
			exit(EXIT_FAILURE);
		}
		printf("#[%d] - Lector  id = %ld\n",i+1,hilo1[i]);

		if(pthread_create(&hilo2[i], NULL, lector, NULL)){
			printf("Error al hilo");
			exit(EXIT_FAILURE);
		}
		printf("#[%d] - Escritor  id = %ld\n",i+1,hilo2[i]);
	}

	int j;
	for(j=0; j<10; j++){
		pthread_join(hilo1[j], NULL);
		pthread_join(hilo2[j], NULL);
	}

	sem_destroy(&acceso);
	sem_destroy(&sem_n);

	exit(0);
}

void* lector(){
	int i=0;
	while(1){
		sleep(3);
		sem_wait(&sem_n);
		n=n+1;
		if(n==1){
			sem_wait(&acceso);
		}
		sem_post(&mutex);
		leerbasedatos();//Funcion que lee la data base
		sem_wait(&sem_n);
		nLector=nLector-1;
		if(nLector==0){
			sem_post(&acceso;
		}
		sem_post(&mutex);
	}
}

void* escritor(){
	while(1){
		sleep(3);
		sem_wait(&acceso);
		palabra++;
		escribirbasedatos();//Funcion que escribe en la data base
		sem_post(&acceso);
	}

}

void leerbasedatos(){
	
	archivo = fopen("base.txt", "r");
	if(archivo == NULL){
		puts("Error al abrir el archivo");
	}else{
		fscanf(archivo, "%d", &leer);
		printf("Lector id: %ld\nMensaje: %d\n",pthread_self(),leer);
	}
	fclose(archivo);
}


void escribirbasedatos(){

	printf("Escritor id: %ld\nMensaje: %d\n",pthread_self(),palabra);
	archivo = fopen("base.txt", "w");
	if( archivo== NULL){
		puts("ERROR EN LA OPERACION DE APERTURA");

	}else{
		fprintf(archivo, "%d", palabra);
	}
	fclose(archivo);
}
