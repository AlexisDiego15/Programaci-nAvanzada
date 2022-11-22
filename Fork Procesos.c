#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <string.h>

void crearArchivo(char *);
void escribirArchivo(char *, int, char*);
void leerArchivo(char* ,int );

int main(){
	
	
	int proc;
	int i;
	int arr[4];
	int sleepTime = 20000;
	char nombreArchivo[20] = "procesos.txt";
	FILE *archivo;
	
	printf("\n");
	
	for(i=0; i<4; i++){
		
	 proc = fork(); //pid_t proc;
	
	if(proc < 0)
		printf("ocurrio un error\n");
	if(proc == 0){
		printf("proceso hijo: %i, papa: %i\n", getpid(), getppid());
		arr[i] = getpid();
		break;
	}
	else{
		//wait(&proc);
	}
	
		
	}
	
	while(1){
		
		if(i == 0){
			printf("proceso 1 %i\n", getpid());
			
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
				printf("entro\n");
				
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 1 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");		}
				else{
					printf("El proceso 1 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 1\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
			
		}
		if(i==1){
			
			printf("proceso 2 %i\n", getpid());
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);

				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 2 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
				}
				else{
					printf("El proceso 2 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 2\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
		}
		if(i==2){
			printf("proceso 3 %i\n", getpid());
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
				printf("entro\n");
				
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 3 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
				}
				else{
					printf("El proceso 3 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 3\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
		}
			if(i==3){
			
			printf("proceso 4 %i\n", getpid());
			if(archivo = fopen(nombreArchivo,"r")){
				int vacio;
				fscanf(archivo, "%i", &vacio);
		
				
				if(feof(archivo) != 0 || vacio == -1){
					fclose(archivo);
					printf("El proceso 4 no encontro nada,entonces, escribira\n");
					escribirArchivo(nombreArchivo, getpid(), "Hola");
				}
				else{
					printf("El proceso 4 encontro algo escrito, lo leera\n");
					leerArchivo(nombreArchivo, getpid());
				}
					
				fclose(archivo);
				
			}else{
				printf("No existe Archivo desde proceso 4\n");
				crearArchivo("procesos.txt");
				escribirArchivo("procesos.txt", getpid(), "Hola");
			}
		}
		
		
	
	}
	
	wait(&proc);
	exit(0);
	
	
	
}

void crearArchivo(char *nombre){
	FILE *archivo = fopen(nombre,"w");
	fclose(archivo);
}

void escribirArchivo(char* nombre, int proceso, char *mensaje){
	FILE *archivo = fopen(nombre, "w+");
	if(proceso != -1)
		fprintf(archivo,"%i %s", proceso, mensaje);
	else
		fprintf(archivo,"%i", proceso);
	fclose(archivo);
}

void leerArchivo(char* nombre, int pidLector){
	FILE *archivo = fopen(nombre,"r");
	char palabra[15];
	char mensaje[150];
	int pidProceso;
	

	fscanf(archivo, "%d %s", &pidProceso, mensaje);
	fclose(archivo);
	escribirArchivo(nombre, -1, "Nada");
	printf("Lo recibio el proceso: %i, lo mando el proceso: %i y el mensaje era: %s\n",pidLector, pidProceso, mensaje);
	
	
}

