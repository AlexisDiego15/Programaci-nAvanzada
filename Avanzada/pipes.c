#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

#define hijos 3

int main(){

//tuberia
int fd[2], fd2[2];
int status;

pid_t pid_hijo;
char buf[15];
char buf2[15];

char string[]="Hola papa";
char string2[]="Hola hijo";

int h,p;

pipe(fd);
pipe(fd2);

for(int i=0; i<hijos;i++){
pid_hijo = fork();
if(pid_hijo<0)
//printf("Ocurrio un error\n");
if(pid_hijo==0){
//printf("Proceso hijo %i,papa%i\n",getpid(),getppid());
break;
}else{continue;}
//printf("Proceso Papa: %i\n",getpid());
}
//printf("\n\n\n\n\n\n");
if(pid_hijo == 0){
// Hijo Envia Al Padre
p = 0;
for(int i=0 ; i<15 ; i++){
buf2[i] = '\0';
}
close(fd[0]);
write(fd[1],string,strlen(string));
printf("Hijo %i ha enviado un mensaje\n",getpid());
close(fd[1]);
//Hijo Recibe Del Padre
close(fd2[1]);
while(p = read(fd2[0],buf2,sizeof(buf2)) > 0){
printf("Hijo leyendo a padre: %s",buf2);
printf("\n\n");
close(fd2[0]);
exit(0);
}
}
if(pid_hijo > 0){
//Padre recibe de hijo
h = 0;
for(int i=0 ; i<15 ; i++){
buf[i] = '\0';
}
close(fd[1]);
while(h = read(fd[0],buf,sizeof(buf)) > 0){
printf("Padre leyendo a hijo: %s",buf);
printf("\n");
close(fd[0]);
//Padre envia al hijo
close(fd2[0]);
write(fd2[1],string2,strlen(string2));
printf("Padre ha enviado un mensaje\n");
close(fd2[1]);
}
}
else{
printf("\nERROR\n");
}
//
int x=0;
while(x<3){
pid_hijo = wait(&status);
x++;
}

return 0;

}
