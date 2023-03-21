/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
CUBI */
//Criamos um HEADER e um REGISTER com os dados passados de acordo com o pdf do trabalho
#ifndef _define_
#define _define_

#define ERROR 1
#define SUCCESS 0

typedef struct{

  char status;
  long int topoLista;
  int nroEstacoes;
  int nroParesEstacao;

}HEADER;


typedef struct{

  char removido;
  int tamanhoRegistro;
  long int proxLista;

  int codEstacao;
  int codLinha;
  int codProxEstacao;
  int distProxEstacao;
  int codLinhaIntegra;
  int codEstIntegra;
  char *nomeEstacao;
  char *nomeLinha;

}REGISTER;



struct Estacao{
    int repeticoes;
    char *nome;
    struct Estacao *prox;
    struct Estacao *ant;
};
typedef struct Estacao Elem_est;
typedef struct Estacao* Lista_estacao;


struct Pares{
    int codEstacaoNo;
    int codProxEstacaoNo;
    int repeticoes;
    struct Pares *prox;
    struct Pares *ant;
};
typedef struct Pares Elem_pares;
typedef struct Pares* Lista_pares;
#endif