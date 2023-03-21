#include <stdio.h>
#include <stdlib.h>
#include <define.h>
#include <string.h>
//Definição do tipo lista


Lista_estacao* cria_lista_estacao(){
    Elem_est* li = (Elem_est*) malloc(sizeof(Elem_est));
    li->nome = NULL;
    li->prox = NULL;
    li->codigo_est = -1;
    li->codigo_prox= -1;
    li->repeticoes_pares = -1;
    li->repeticoes_est = -1; //Se fosse zero ele apareceria uma vez
    return li;
}

int insere_lista_final_estacao(Lista_estacao* li, REGISTER r, HEADER* h){
    if(li == NULL)
        return 0;
    Elem_est *no;
    no = (Elem_est*) malloc(sizeof(Elem_est));
    if(no == NULL)
        return 0;
    no->nome = malloc(sizeof(char)*strlen(r.nomeEstacao));
    strcpy(no->nome, r.nomeEstacao);
    no->repeticoes_est = 0;

    no->codigo_est = r.codEstacao;
    no->codigo_prox = r.codProxEstacao;
    no->repeticoes_pares = 0;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        *li = no;
    }else{
        Elem_est *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(strcmp(aux->nome, no->nome) == 0){
                aux->repeticoes_est++;
                return 1;
            }
            aux = aux->prox;
        }
        aux->prox = no;
        h->nroEstacoes++;
    }
    return 1;
}

struct Pares{
    struct Pares *prox;
    int codEstacao;
    int codProxEstacao;
    int repeticoes;
};
typedef struct Pares* Lista_pares;
typedef struct Pares Elem_par;

Lista_pares* cria_lista_pares(){
    Elem_par* li = (Elem_par*) malloc(sizeof(Elem_par));
    li->prox = NULL;
    li->codEstacao = -1;
    li->codProxEstacao = -1;
    li->repeticoes = -1; //Se fosse zero ele apareceria uma vez
    return li;
}

int insere_lista_final_pares(Lista_pares* li, REGISTER r, HEADER* h){
    if(li == NULL)
        return 0;
    Elem_par *no;
    no = (Elem_par*) malloc(sizeof(Elem_par));
    if(no == NULL)
        return 0;


    no->repeticoes = 0;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        *li = no;
    }else{
        Elem_par *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(aux->codEstacao == no ->codEstacao && aux->codProxEstacao == no->codProxEstacao){
                aux->repeticoes++;
                return 1;
            }
            aux = aux->prox;
        }
        aux->prox = no;
        h->nroParesEstacao++;
    }
    return 1;
}


/*
void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}




}







int remove_lista(Lista* li, int mat){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;
    Elem *ant, *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        ant = no;
        no = no->prox;
    }
    if(no == NULL)//não encontrado
        return 0;

    if(no == *li)//remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}


int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}
*/