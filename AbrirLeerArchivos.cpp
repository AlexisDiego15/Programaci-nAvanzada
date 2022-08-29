#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int main(){
	int opc;
	char c;
	char descripcion[100];
	FILE *archivo;
	
	do{
		printf("\nIngrese la opcion\n1.-Escribir en archivo\n2.-Leer archivo\n3.-Salir\n");
		scanf("%d",&opc);
		system("cls");
		switch(opc){

			case 1:
	 				fflush(stdin);
		   			printf("\nEscribe lo que quieres escribir en el archivo \n");
		   			gets(descripcion);
		   			
		   			archivo = fopen("info.txt","a");
					fprintf(archivo,"%s\n",descripcion);
					fclose(archivo);
					
					printf("Se escribio con exito\n");
			break;

			case 2:
				
				
					
					archivo=fopen("info.txt", "r");
					if(archivo == NULL){
				      printf("Error al abrir archivo");   
				      exit(1);             
				    }else{
				    	printf("El texto dice:\n");
						while((c=getc(archivo))!=EOF){
							printf("%c",c);
						}
					}

			break;				
		}
	}while(opc!=3);
	return 0;
}
