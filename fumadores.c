#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<pthread.h>

sem_t sem_agente;
sem_t sem_tabaco;
sem_t sem_cerillo;
sem_t sem_papel;


void *fun_agente(void *argumento){
	int ing1, ing2;
	int tabaco=0;
	int papel=1;
	int cerillo=2;
	
	while(1){
		sem_wait(&sem_agente);//P agente

		do{
			ing1=rand()%3;
			ing2=rand()%3;
		}while(ing1==ing2);
		
		printf("Ingrediente 1: %d \n", ing1);
		printf("Ingrediente 2: %d \n", ing2);
		

		if((ing1==tabaco && ing2==cerillo)||(ing1==cerillo && ing2==tabaco)){ 
			sem_post(&sem_papel);//V papel 	
		}
		

		if((ing1==tabaco && ing2==papel)||(ing1==papel && ing2==tabaco)){ 
			sem_post(&sem_cerillo);//V cerillo
		}
		
		if((ing1==papel && ing2==cerillo)||(ing1==cerillo && ing2==papel)){ 
			sem_post(&sem_tabaco);//V tabaco

		}
	}
	
	pthread_exit(0);
}

void *fun_tabaco(void *argumento){
	while(1){
		sem_wait(&sem_tabaco);//P tabaco
		printf("Fumador con tabaco %ld\n" , pthread_self());
		sleep(2);
		sem_post(&sem_agente);//V agente
	}
	pthread_exit(0);
}

void *fun_cerillo(void *argumento){
	while(1){
		sem_wait(&sem_cerillo); //P cerillo
		printf("Fumador con cerillo %ld\n" , pthread_self());
		sleep(2);
		sem_post(&sem_agente);//V agente
	}
	pthread_exit(0);
}

void *fun_papel(void *argumento){
	while(1){
		sem_wait(&sem_papel);//P papel
		printf("Fumador con papel %ld\n" , pthread_self());
		sleep(2);
		sem_post(&sem_agente);//V agente		
	}
	pthread_exit(0);
}

int main(){
	pthread_t th1, th2, th3, th4;
	
	sem_init(&sem_agente, 0, 1);
	sem_init(&sem_tabaco, 0, 0);
	sem_init(&sem_cerillo, 0, 0);
	sem_init(&sem_papel, 0, 0);


	pthread_create(&th1, NULL, fun_agente, NULL);
	pthread_create(&th2, NULL, fun_tabaco, NULL);
	pthread_create(&th3, NULL, fun_cerillo, NULL);
	pthread_create(&th4, NULL, fun_papel, NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);
	pthread_join(th4, NULL);

	sem_destroy(&sem_tabaco);
	sem_destroy(&sem_cerillo);
	sem_destroy(&sem_papel);
	sem_destroy(&sem_agente);

	exit(0);
}


