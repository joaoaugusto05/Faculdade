#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

//Definições dos valores semanticos para as ações dos filosofos
#define N 5
#define pensar 0
#define fome 1
#define comer 2

//definição dos garfos à esquerda e direita
#define esquerda (nfilosofo + 4)%N
#define direita (nfilosofo + 1)%N

//Criação dos filofos, monitores e recursos necessários
sem_t mutex;
sem_t S[N];
int estado[N];
int nfilosofo[N] = {0,1,2,3,4};

//Verifica se os garfos à esquerda e direita podem ser utilizados
void testar(int nfilosofo){
    if(estado[nfilosofo] == fome && estado[esquerda] != comer && estado[direita] != comer){
        estado[nfilosofo] = comer;
        sleep(2);
        printf("O filosofo %d agarrou os garfos\n", nfilosofo);
        sem_post(&S[nfilosofo]);
    }
}

//Realiza o ato de deixar o garfo verificando a disponibilidade e travando o recurso
void deixar_garfo(int nfilosofo){
    sem_wait(&mutex);
    estado[nfilosofo] = pensar;
    printf("O filosofo %d deixou os garfos.\n", nfilosofo);
    printf("O filosofo %d esta pensando.\n", nfilosofo);
    testar(esquerda);
    testar(direita);
    sem_post(&mutex);

}

//Agarra o garfo verificando as condições e travando os valores para evitar conflitos, requisitando o recurso
void agarra_garfo(int nfilosofo){
    sem_wait(&mutex);
    estado[nfilosofo] = fome;
    printf("O filosofo %d está com fome.\n", nfilosofo);
    testar(nfilosofo);
    sem_post(&mutex);
    sem_wait(&S[nfilosofo]);
    sleep(1);
}

//Definição da estrutura que representa um filosofo, o qual pensa e come
void *filosofo(void *n){
    while(1){
        int *i = n;
        sleep(1);
        agarra_garfo(*i);
        sleep(1);
        deixar_garfo(*i);

    }
}


int main(){
    pthread_t Thread[N];
    sem_init(&mutex, 0, 1);
    for ( int i = 0; i < N; i++)
    {
        sem_init(&S[i], 0, 0);

    }
    for (int i = 0; i < N; i++)
    {
        pthread_create(&Thread[i], NULL, filosofo, &nfilosofo[i]);
        printf("O filosofo %d esta pensando.\n", i);
    }
    for (int i = 0; i < N; i++)
    {
        pthread_join(Thread[i], NULL);
    }
    
    
}