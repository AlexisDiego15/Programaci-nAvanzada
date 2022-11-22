/*OLIVEROS GONZALEZ CARLOS FERNANDO
ELABORAR UN PROGRAMA DONDE SIMULE UNA BASE DE DATOS UN AVION DE DESCRIBE UN LECTOR Y UN ESCRITOR DONDE DEBERAN JALAR LOS DATOS DE UN ARCHIVO TXT SIMULANDO QUE ES LA BASE DE DATOS.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

sem_t  mutex;//protegerá la variable nLector
sem_t bd;// controla el acceso a la base de datos
int  nLector=0;   //Número de procesos que leen o desean leer

int palabra=0;
int leer;
FILE* archivo=NULL;// puntero para abrir el archivo
void* lector();//funcion que leerà el txt
void* escritor();//funcion que escribe en el txt
void leer_base_de_datos();//leer base de datos
void escribir_en_base_de_datos();//escribir en base de datos

void main(void){

	pthread_t hilo1[10], hilo2[10];//creamos los hilos como arreglos
	int i;

	/* inicializar los semaforos */
	sem_init(&bd, 0, 1);
	sem_init(&mutex, 0, 1);
	
	//creamos los hilos
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

	/* esperamos el final de cada hilo*/
	int j;
	for(j=0; j<10; j++){
		pthread_join(hilo1[j], NULL);
		pthread_join(hilo2[j], NULL);
	}

	sem_destroy(&bd);
	sem_destroy(&mutex);

	exit(0);
}

void* lector(){
	int i=0;
	while(1){
		sleep(3);
		//ponemos en espera la variable mutex
		sem_wait(&mutex);
		nLector=nLector+1;
		if(nLector==1){
			sem_wait(&bd);
		}
		sem_post(&mutex);
		leer_base_de_datos();//llamamos a la funcion que va a leer a la base de datos
		sem_wait(&mutex);
		nLector=nLector-1;
		if(nLector==0){
			sem_post(&bd);
		}
		sem_post(&mutex);//ejecuta otras acciones
	}
}

void* escritor(){
	while(1){
		sleep(3);
		sem_wait(&bd);
		palabra++;
		escribir_en_base_de_datos();//lamamos a la funcion que va a escribir en la base de datos
		sem_post(&bd);
	}

}

void leer_base_de_datos(){
	
	//abrimos el archivo base.txt
	archivo = fopen("base.txt", "r");
	if(archivo == NULL){
		puts("Error al abrir el archivo");
	}else{
		//leemos lo que contiene el archivo e imprimimos en pantalla
		fscanf(archivo, "%d", &leer);
		printf("Lector id: %ld\nMensaje: %d\n",pthread_self(),leer);
	}
	//cerramos archivo
	fclose(archivo);
}


void escribir_en_base_de_datos(){

	printf("Escritor id: %ld\nMensaje: %d\n",pthread_self(),palabra);
	//abrimos archivo bas.txt
	archivo = fopen("base.txt", "w");
	if( archivo== NULL){
		puts("ERROR EN LA OPERACION DE APERTURA");

	}else{
		//escribimos en el archivo
		fprintf(archivo, "%d", palabra);
	}
	//cerramos el archivo
	fclose(archivo);
}
