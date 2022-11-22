#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void*funcion_hilo(void*argumento);
char mensaje[] = "Este es un mensaje";

int main()
{
	pthread_t id_hilo;
	void* valor_retorno;
	
	if(pthread_create(&id_hilo, NULL, funcion_hilo, (void*)mensaje) ) 
	{
		printf("Problema en la creación del hilo\n");
		exit(EXIT_FAILURE);
	}
	printf("Esperando a que termine el hilo hijo...\n");
	if(pthread_join(id_hilo, &valor_retorno) ) 
	{
		printf("Problema al crear enlace con otro hilo\n");
		exit(EXIT_FAILURE);
	}
	printf("El hilo que espera papá, regreso!!!\t %s\n", (char*) valor_retorno);
	printf("Nuevo mensaje : %s\n", mensaje);
	exit(EXIT_SUCCESS);
}

void *funcion_hilo (void *argumento)
{
	printf("El código de la función esta en ejecución.\n El argumento es: %s\n", (char*)argumento);
	sleep(3);
	strcpy(mensaje,"mensaje cambiado por el hijo!");
	pthread_exit("hijo retorna gracias.\n");
}
