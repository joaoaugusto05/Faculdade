/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Cria Lista de estacoes
Lista_estacao* cria_lista_estacao(){
    Lista_estacao* li = (Lista_estacao*) malloc(sizeof(Lista_estacao));
    if(li != NULL)
        *li = NULL;
    return li;
}

//Imprime Lista de estacoes
void imprime_lista(Lista_estacao* li){
    if(li == NULL)
        return;
    Elem_est* no = *li;
    while(no != NULL){
        printf("Nome: %s", no->nome);
        printf("Repeticoes: %d\n", no->repeticoes);
        no = no->prox;
    }
}

//Insere no final da lista de estacoes
int insere_lista_final_estacao(Lista_estacao* li, REGISTER r, HEADER *h){
    
    if(li == NULL)
        return 0;
    Elem_est *no;
    no = (Elem_est*) malloc(sizeof(Elem_est));
    if(no == NULL)
        return 0;
    no->nome = (char*) malloc(sizeof(char)*strlen(r.nomeEstacao) + 1);
    strcpy(no->nome, r.nomeEstacao);
    no->repeticoes = 0;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->ant = NULL;
        h->nroEstacoes++;

    }else{
        
        Elem_est *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(strcmp(aux->nome, no->nome) == 0){
                aux->repeticoes++;
                return 1;
            }          
            aux = aux->prox;
        }   
            aux->prox = no;
            no->ant = aux;
            h->nroEstacoes += 1;        

    }


    return 1;
}

//Retira pares de estacoes
void retira_estPares(Lista_pares* li, HEADER *h, REGISTER r){

   
        Elem_pares *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(r.codEstacao == aux->codEstacaoNo && r.codProxEstacao == aux->codProxEstacaoNo){

                aux->repeticoes--;
                if(aux->repeticoes < 0){

                    if(aux->ant == NULL){
                        aux = aux->prox;
                    }
                    else{
                        aux->ant->prox = aux->prox;
                    }

                    if(aux->codProxEstacaoNo != -1 && aux->codEstacaoNo != -1){                       
                        h->nroParesEstacao--;
                }   
                    return;
                }
            }
                
                
      
            aux = aux->prox;
        }   
                        
    return;
}

//Retira numero de estacoes
void retira_numEst(Lista_estacao* li, HEADER *h, REGISTER r){
    if(li == NULL)
        return;
        Elem_est* no = *li;
        
        while(no != NULL){
            if(strcmp(r.nomeEstacao, no->nome) == 0){
                no->repeticoes--;

                if(no->repeticoes < 0){
                    h->nroEstacoes--;
                    

                    if(no->ant == NULL)//remover o primeiro?
                        *li = no->prox;
                    else
                        no->ant->prox = no->prox;
                        
                    if(no->prox != NULL)//não é o último?
                         no->prox->ant = no->ant;
                }
            }
        no = no->prox;
    }

}

//Libera lista de estacoes
void libera_lista_est(Lista_estacao* li){
    if(li != NULL){
        Elem_est* no;
        while((*li) != NULL){

            no = *li;
            *li = (*li)->prox;
            free(no->nome);
            free(no);
        }
        free(li);
    }
}

//Libera lista de pares de estacao
void libera_lista_pares(Lista_pares* li){
    if(li != NULL){
        Elem_pares* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

//Libera ambas listas
void libera_lista(Lista_pares* par, Lista_estacao *est){
    libera_lista_est(est);
    libera_lista_pares(par);
}

//Cria listas de pares de estacao
Lista_pares* cria_lista_pares(){
    Lista_pares* li = (Lista_pares*) malloc(sizeof(Lista_pares));
    if(li != NULL)
        *li = NULL;
    return li;
}

//Insere par de estacao no fim da lista
int insere_lista_final_pares(Lista_pares* li, REGISTER r, HEADER *h){
    
    
    if(li == NULL)
        return 0;

    Elem_pares *no;
    no = (Elem_pares*) malloc(sizeof(Elem_pares));
    if(no == NULL)
        return 0;
        
    no->repeticoes = 0;
    no->codEstacaoNo = r.codEstacao;
    no->codProxEstacaoNo = r.codProxEstacao;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        no->ant = NULL;
        *li = no;
        

    }else{        
        Elem_pares *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(r.codEstacao == aux->codEstacaoNo && r.codProxEstacao == aux->codProxEstacaoNo){
                aux->repeticoes++;
                return 1;
            }          
            aux = aux->prox;
        }   
            aux->prox = no;
            no->ant = aux;
                   
        
    }
    if(r.codEstacao != -1 && r.codProxEstacao != -1)
                h->nroParesEstacao++; 

    return 1;
}