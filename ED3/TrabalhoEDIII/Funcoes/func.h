/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#ifndef _funcsgerais_ 
#define _funcsgerais_
#include <stdio.h>
#include "../define.h"

    //Declacao de funcoes
    void libera_lista_est(Lista_estacao* li);
    void libera_lista_pares(Lista_pares* li);
    void libera_lista(Lista_pares* par, Lista_estacao *est);
    Lista_pares* cria_lista_pares();
    int insere_lista_final_pares(Lista_pares* li, REGISTER r, HEADER *h);
    Lista_estacao* cria_lista_estacao();
    void imprime_lista(Lista_estacao* li);
    int insere_lista_final_estacao(Lista_estacao* li, REGISTER r, HEADER *h);

    int compara_reg(REGISTER r, int num_campos, char **nome_campo, char **valor_campo);
    void atualiza_cabec(HEADER h, FILE *fp);
    void binToRegister(FILE *fp, REGISTER *r);
    char *strParser(char *str, char limitador, int pos);
    void imprime_reg(REGISTER target);
    void insert_DataInReg(char *mensagem, REGISTER* target);
    void insert_regInBin(REGISTER *r, FILE *fp);
    void dataInHeader(Lista_estacao* Estacao, Lista_pares* par, HEADER *h, REGISTER r);

    //Funcoes principais do trabalho
    void func_one();
    void func_two();
    void func_three();
    void func_four();
    void func_five();
    void func_six();
    

    void retira_estPares(Lista_pares* li, HEADER *h, REGISTER r);
    void retira_numEst(Lista_estacao* li, HEADER *h, REGISTER r);
    void colocaLixo(FILE *Arquivo_bin, int n);
    void flushStdin();

    void atualizaReg(char **nome_campo, char **valor_campo,int num_campos, REGISTER *r);
    void insereReaproveitamento(FILE *Arquivo_bin,REGISTER *r, HEADER *h);

#endif
