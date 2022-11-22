#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define N  5     

#define LEFT(numero_filosofo)  ( ( numero_filosofo + N - 1) % N )
#define RIGHT(numero_filosofo) ( ( numero_filosofo + 1 )    % N )


typedef enum { Tomando_agua, Esperando, Comiendo} state_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
state_t         state_array[N];   
sem_t           coordinate[N];   



void think( int numero_filosofo )
{
    printf( "El filosofo %i esta tomando agua con pid de %li\n", numero_filosofo,pthread_self() );
    sleep(5);
}



void eat( int numero_filosofo)
{
    printf( "El filosofo %i esta comiendo con pid de %li\n", numero_filosofo,pthread_self() );
    sleep(5);
}


void test( int numero_filosofo )
{
    if( state_array[numero_filosofo]        == Esperando &&
        state_array[LEFT(numero_filosofo)]  != Comiendo &&
        state_array[RIGHT(numero_filosofo)] != Comiendo    ) {

        state_array[numero_filosofo] = Comiendo;
        sem_post( &coordinate[numero_filosofo] );
    }
}

void take_forks( int numero_filosofo )
{
    pthread_mutex_lock( &mutex );
    state_array[numero_filosofo] = Esperando;
    test( numero_filosofo );                  
    pthread_mutex_unlock( &mutex );
    sem_wait( &coordinate[numero_filosofo] );
}


void put_forks( int numero_filosofo )
{
    pthread_mutex_lock( &mutex );
    state_array[numero_filosofo] = Tomando_agua;
    test( LEFT(numero_filosofo) );            
    test( RIGHT(numero_filosofo) );          
    pthread_mutex_unlock( &mutex );
}



void *filosofo(void *arg)
{
    
    int numero_filosofo = *(int *)arg;
    free( arg );

    while( 1 ) {
        think( numero_filosofo );
        take_forks( numero_filosofo );
        eat( numero_filosofo );
        put_forks( numero_filosofo );
    }

    return NULL;
}


int main( void )
{
    int       numero_filosofo;
    int       i;
    int      *arg;
    pthread_t threadIDs[N];

   
    for( i = 0; i < N; ++i ) {
        sem_init( &coordinate[i], 0, 0 );
    }

    
    for( numero_filosofo = 0;numero_filosofo < N; ++numero_filosofo ) {
        arg = (int *)malloc( sizeof( int ) );
       *arg = numero_filosofo;
        pthread_create( &threadIDs[numero_filosofo], NULL, filosofo, arg );
    }

    
    for( numero_filosofo = 0; numero_filosofo < N; ++numero_filosofo ) {
        pthread_join( threadIDs[numero_filosofo], NULL );
    }

    
    for( i = 0; i < N; ++i ) {
        sem_destroy( &coordinate[i] );
    }
    return EXIT_SUCCESS;
}
