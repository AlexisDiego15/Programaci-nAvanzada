#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<math.h>

  int A[3][3]={{2,0,1},{3,0,0},{5,1,1}};
  int B[3][3]={{1,0,1},{1,2,1},{1,1,0}};
  int resultado[3][3];
  
void *suma(void *argumento){
        printf("---SUMA--- \n");
        printf("Pid de hilo %ld \n", pthread_self());
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
            resultado[i][j]=A[i][j]+B[i][j];
              printf("%i\t", resultado[i][j]);
            }
            printf("\n");
        }
        pthread_exit(NULL);
}  

void *resta(void *argumento){
        printf("---RESTA---\n");
        printf("Pid de hilo %ld \n", pthread_self());
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
            resultado[i][j]=A[i][j]-B[i][j];
              printf("%i\t", resultado[i][j]);
            }
            printf("\n");
        }	
        pthread_exit(NULL);
}  
void *multiplicacion(void *argumento){ 
        printf("---MULTIPLICACION---\n");
        printf("Pid de hilo %ld \n", pthread_self());
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
            	resultado[i][j]=A[i][j]*B[i][j];
              printf("%i\t", resultado[i][j]);
            }
            printf("\n");
        }
        pthread_exit(NULL);
} 


int main(){    
       pthread_t hiloS, hiloR, hiloM;
       pthread_create(&hiloS,NULL,(void *) suma, NULL);
       pthread_create(&hiloR,NULL,(void *) resta, NULL);
       pthread_create(&hiloM,NULL,(void *) multiplicacion, NULL);
       


       pthread_join(hiloS,NULL);
       pthread_join(hiloR,NULL);
       pthread_join(hiloM,NULL);
       
    exit(EXIT_SUCCESS);
}
