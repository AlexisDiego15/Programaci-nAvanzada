
/*Se tienen tre fumadores que se encargan de fumar. cada uno de ellos tiene un ingrediente ilimitado por ejemplo, el primero tiene tabaco, el segundo tiene papel y el tercero tiene cerillos.

para saber quien es el que debe de fumar existe un agente que también genera cada vez dos tipos de ingredientes pudiendo ser papel y cerillo entonces fumaria el fumador que tiene el tabaco. Si se produce la combinacion de tabaco-cerillo entonces quien debe de fumar es el que tiene el papel y asi sucesiamente.

el primer en entrar debe de ser el agente con la finalidad de que genere dos ingredientes, mientras los fumadores que quisieron entrar antes de que se generaran los ingredientes por el agente se desbloquearán en espera de una señal por parte del agente.

cuando el agente produce los dos ingredientes y despierta al fumador, se debe quedar dormido hasta que termine de fumar y pueda generar él otros dos ingredientes.

el programa debe de desplegar en la terminal el pid del agente y los ingredientes que esta produciendo.

Mientras que los fumadores deben de imprimir su pid, que ingrediente tiene el para poder fumar.
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<time.h>


void * fumador_tabaco(void* var);
void * fumador_cerillo(void* var);
void * fumador_papel(void* var);
void * agente(void* var);
//sem_post(&elementos);//V
//sem_wait(&huecos);//p
sem_t se_agente;
sem_t fum_papel;
sem_t fum_tabaco;
sem_t fum_cerillo;
//sem_init(&NombreVariableSem,0(TipodDeProceso),0(Valor));

//Inciar los semaforos



void main(void){
// o es papel
// 1 es tabaco
// 2 es cerillo
while(1){
	pthread_t th1,th2,th3,th4;	


	sem_init(&se_agente,0,1);
	sem_init(&fum_papel,0,0);
	sem_init(&fum_tabaco,0,0);
	sem_init(&fum_cerillo,0,0);

	//crear los procesos ligeros
	pthread_create(&th4,NULL,agente,NULL);
	pthread_create(&th1,NULL,fumador_tabaco,NULL);
	pthread_create(&th2,NULL,fumador_papel,NULL);
	pthread_create(&th3,NULL,fumador_cerillo,NULL);


	pthread_join(th4,NULL);
	pthread_join(th1,NULL);
	pthread_join(th2,NULL);
	pthread_join(th3,NULL);

	sem_destroy(&fumador_tabaco);
	sem_destroy(&fumador_papel);
	sem_destroy(&fumador_cerillo);
	sem_destroy(&agente);
	

	exit(0);
	
	}
	   }


void * agente(void* var){
	
	int ing1;
	int ing2;
while(1){
	
	//sem_wait(&se_agente);
	do{
		ing1=rand()%3;
		//printf("el valor 1: %i\n",ing1);
		ing2=rand()%3;
		//printf("el valor 2: %i\n",ing2);
	}while(ing1==ing2);
		
 
		if((ing1==0)&&(ing2==1)||(ing1==1)&&(ing2==0)){
			//despierto al proceso que tiene el cerillo
			sem_post(&fum_cerillo);//V
		//pthread_create(&th2,NULL,fumador_cerillo,NULL);

			sem_wait(&se_agente);//P
		//break;
		}
		if((ing1==0)&&(ing2==2)||(ing1==2)&&(ing2==0)){
			//despierto al proceso que tiene el tabaco
			sem_post(&fum_tabaco);//V
		//pthread_create(&th1,NULL,fumador_tabaco,NULL);
			sem_wait(&se_agente);//p
		}
		
		if((ing1==1)&&(ing2==2)||(ing1==2)&&(ing2==1)){
			//despierto al proceso que tiene el papel
			sem_post(&fum_papel);
			//pthread_create(&th2,NULL,fumador_papel,NULL);
			sem_wait(&se_agente);

		
		}
	}
}


void * fumador_tabaco(void* var){
	while(1){
	sem_wait(&fum_tabaco);
	printf("tengo el tabaco\n");
	printf("Estoy fumando\n");
	sleep(2);
	sem_post(&se_agente);		
		}
	}
void * fumador_papel(void* var){
	while(1){
	sem_wait(&fum_papel);
	printf("tengo el papel\n");
	printf("Estoy fumando\n");
	sleep(2);
	sem_post(&se_agente);
		}
	}

void * fumador_cerillo(void* var){
	while(1){
	sem_wait(&fum_cerillo);
	printf("tengo los cerillos\n");
	printf("Estoy fumando\n");
	sleep(2);
	sem_post(&se_agente);	
		}
	}
	
	
	
	
	
	
	
	
	
