#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<semaphore.h>

int i;
int dato=1;
pthread_t id_hilo, id_hilo2, id_hilo3, id_hilo4;

void *funcion_hilo(void *argumento);
void *funcion_hilo2(void *argumento);
void *funcion_hilo3(void *argumento);
void *funcion_hilo4(void *argumento);
sem_t sem_s, sem_r, sem_m, sem_d;

int main() {
sem_init(&sem_s,0,1);
sem_init(&sem_r,0,0);
sem_init(&sem_m,0,0);
sem_init(&sem_d,0,0);

printf("EL DATO INICIAL ES: 1 \n\n");
//////////CREACION del hilo 1//////////
if ( pthread_create(&id_hilo, NULL, funcion_hilo, NULL)){
printf("Problema en la creación del hilo\n");
exit(EXIT_FAILURE); 
}
//pthread_join(id_hilo,NULL);

//////////CREACION HILO 2//////////
if ( pthread_create(&id_hilo2, NULL, funcion_hilo2, NULL) ){
printf("Problema en la creación del hilo\n");
exit(EXIT_FAILURE);
}
//pthread_join(id_hilo2,NULL);

//////////CREACION HILO 3//////////
if ( pthread_create(&id_hilo3, NULL, funcion_hilo3, NULL) ){
printf("Problema en la creación del hilo\n");
exit(EXIT_FAILURE);
}
//pthread_join(id_hilo3,NULL);
//////////CREACION HILO 4//////////
if ( pthread_create(&id_hilo4, NULL, funcion_hilo4, NULL) ){
printf("Problema en la creación del hilo\n");
exit(EXIT_FAILURE);
}
pthread_join(id_hilo,NULL);
pthread_join(id_hilo2,NULL);
pthread_join(id_hilo3,NULL);
pthread_join(id_hilo4,NULL);

sem_destroy(&sem_s);
sem_destroy(&sem_r);
sem_destroy(&sem_d);
sem_destroy(&sem_m);
}

void *funcion_hilo(void *argumento) {
for(int i=0; i<5;i++){
sem_wait(&sem_s);
printf("Su pid es %li \n", pthread_self());
printf("-----HILO SUMA-----\n");
dato=dato+3;
printf("Se le suma al dato +3\n");
printf("El nuevo valor de dato es %d\n", dato);
sem_post(&sem_r);
printf("\n\n");
}
}

void *funcion_hilo2(void *argumento) {
for(int i=0; i<5;i++){
sem_wait(&sem_r);
printf("-----HILO RESTA-----\n");
printf("Su pid es %li \n", pthread_self());
dato=dato-2;
printf("Se le resta al dato - 2\n");
printf("El nuevo valor de dato es %d\n", dato);
sem_post(&sem_m);
printf("\n\n");
}
}

void *funcion_hilo3(void *argumento) {
for(int i=0; i<5;i++){
sem_wait(&sem_m);
printf("-----HILO MULTIPLICACION-----\n");
printf("Su pid es %li \n", pthread_self());
dato=dato*4;
printf("Se multiplica el dato  x 4\n");
printf("El nuevo valor de dato es %d\n", dato);
sem_post(&sem_d);
printf("\n\n");
}
}

void *funcion_hilo4(void *argumento) {
for(int i=0; i<5;i++){
sem_wait(&sem_d);
printf("-----HILO DIVISION-----\n");
printf("Su pid es %li \n", pthread_self());
dato=dato/2;
printf("Se divide el dato / 2\n");
printf("El nuevo valor de dato es %d\n", dato);
sem_post(&sem_s);
printf("\n\n");
}
}
