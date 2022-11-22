#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PUERTO 5000
#define TAM_BUFFER 100
#define DIR_IP "127.0.0.1"

//numero de puerto asignado al servidor
//Dirección del servidor

void main(int argc, char **argv){
	int tamano_direccion, sockfd;
	struct sockaddr_in direccion_servidor;
	char leer_mensaje[TAM_BUFFER];

	//Se configura la direccion IPv4 del servidor a donde se va a
	//establecer la conexion
	memset (&direccion_servidor, 0, sizeof (direccion_servidor));
	direccion_servidor.sin_family = AF_INET;
	direccion_servidor.sin_port = htons(PUERTO);


	//establece la direccion IPv4 en forma binaria
	if ( inet_pton(AF_INET, DIR_IP, &direccion_servidor.sin_addr) <= 0){
		perror("Ocurrio un error al momento de asignar la direccion IP");
		exit(1);
	}

	//Creacion de las estructuras necesarias para el manejo de un socket
	printf("Creando Socket ....\n");
	if ( (sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
		perror("Ocurrio un problema en la creacion del socket");
		exit(1);
	}

	//Inicia el establecimiento de una conexion mediante una apertura
	//activa con el servidor
	printf ("Estableciendo conexion ...\n");
	if ( connect(sockfd, (struct sockaddr *)&direccion_servidor,
		sizeof(direccion_servidor) ) < 0) {
		perror ("Ocurrio un problema al establecer la conexion");
		exit(1);
	}

	//Inicia la transferencia de datos entre cliente y servidor
	printf ("Enviando mensaje al servidor ...\n");
	if (write (sockfd, "Soy el Cliente", 15) < 0){
		perror("Ocurrio un problema en el envio de un mensaje al cliente");
		exit(1);
	}

	printf ("Recibiendo contestacion del servidor ...\n");
	if (read (sockfd, &leer_mensaje, TAM_BUFFER) < 0){	
		perror ("Ocurrio algun problema al recibir datos del cliente");
		exit(1);
	}
	
	printf ("El servidor envio el siguiente mensaje: \n%s\n", leer_mensaje);
	printf ("Cerrando la aplicacion cliente\n");
	//Cierre de la conexion
	while(1);
	close(sockfd);
}


