//Código Servidor

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PUERTO 5000                      //numero de puerto asignado al servidor
#define COLA_CLIENTES 5                  //tamano cola espera para clientes
#define TAM_BUFFER 100


void main(int argc, char **argv)
{
   int tamano_direccion, sockfd, cliente_sockfd;
   struct sockaddr_in direccion_servidor; //estructura que almacena direccion
   char leer_mensaje[TAM_BUFFER];

   //Se configura la direccion IPv4 para configurar el socket
   memset (&direccion_servidor, 0, sizeof (direccion_servidor));
   direccion_servidor.sin_family = AF_INET;
   direccion_servidor.sin_port = htons(PUERTO);
   direccion_servidor.sin_addr.s_addr = INADDR_ANY;

   //Creacion de las estructuras necesarias para el manejo de un socket
   printf("Creando Socket ....\n");
   if ( (sockfd = socket (AF_INET, SOCK_DGRAM, 0)) < 0){
	perror("Ocurrio un problema en la creacion del socket");
	exit(1);
   }

   //Configuracion del socket mediante la direccion IPv4
   printf("Configurando socket ...\n");
   if (bind(sockfd, (struct sockaddr *) &direccion_servidor,
	sizeof(direccion_servidor)) < 0){
	perror ("Ocurrio un problema al configurar el socket");
	exit(1);
   }
	
   //Define el socket listo para aceptar peticiones
   printf ("Estableciendo la aceptacion de clientes...\n");
   if ( listen(sockfd, COLA_CLIENTES) < 0){
	perror("Ocurrio un problema al crear la cola de aceptar peticiones de los clientes");
	exit(1);
   }

   //Selecciona un cliente de la cola de conexiones establecidas
   //se crea un nuevo descriptor de socket para el manejo
   //de la nueva conexion. Apartir de este punto se debe
   //utilizar el nuevo descriptor de socket
   printf ("En espera de peticiones de conexión ...\n");
   if ( (cliente_sockfd = accept(sockfd, NULL, NULL)) < 0){
	perror("Ocurrio algun problema al atender a un cliente");
	exit(1);
   }

   //Transferencia de datos entre cliente y Servidor
   printf ("Se aceptó un cliente, atendiendolo");
   if (read (cliente_sockfd, &leer_mensaje, TAM_BUFFER) < 0){
	perror ("Ocurrio algun problema al recibir datos del cliente");
	exit(1);
   }
   printf ("El cliente nos envio el siguiente mensaje: \n %s \n", leer_mensaje);
   if (write (cliente_sockfd, "Bienvenido cliente", 19) < 0){
	perror("Ocurrio un problema en el envio de un mensaje al cliente");
	exit(1);
   }
   printf ("Concluimos la ejecución de la aplicacion Servidor\n");
   //Cierre de conexiones

   while (1);
   close (sockfd);
   close (cliente_sockfd);
}


