/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Insere registro no arquivo .bin
void func_five(){

    //Le nome do arquivo .bin
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    FILE *Arquivo_bin = fopen(nome_arquivo_bin, "rb+");

    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }
    //Marca arquivo como aberto
    fputc('0', Arquivo_bin);
    fseek(Arquivo_bin, 0, SEEK_SET);

    HEADER h;
    REGISTER r;

    //Le o cabecalho e atualiza para o estado de leitura
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);

    h.status = '0';
    atualiza_cabec(h,Arquivo_bin);

    fseek(Arquivo_bin,0,SEEK_SET);

    //Le quantos arquivos serao inseridos
    int num_repeticoes;     
    scanf("%d", &num_repeticoes);
    

    for(int i = 0; i < num_repeticoes; i++){
        
        r.nomeEstacao = calloc(100,sizeof(char));
        r.nomeLinha = calloc(100,sizeof(char));

        if(r.nomeEstacao == NULL || r.nomeLinha == NULL){
            printf("Falha no processamento do arquivo.");
        }
        
        //Inicia as variaveis em -1 assim caso o valor seja "NULO" elas permanecerao com -1
        r.codEstacao = -1;
        r.codLinha = -1;
        r.codProxEstacao = -1;
        r.distProxEstacao = -1;
        r.codLinhaIntegra = -1;
        r.codEstIntegra = -1;

        //Computa as informacoes do registro
        //Criamos uma função para limpar o buffer pois havia casos em que o codigo funcionava no pc e nao no runcodes devido às entradas
        scanf("%d",&r.codEstacao);
        flushStdin();
        scan_quote_string(r.nomeEstacao);
        flushStdin();
        scanf("%d",&r.codLinha);
        flushStdin();
        scan_quote_string(r.nomeLinha);
        flushStdin();
        scanf("%d",&r.codProxEstacao);
        flushStdin();
        scanf("%d",&r.distProxEstacao);
        flushStdin();
        scanf("%d",&r.codLinhaIntegra);
        flushStdin();
        scanf("%d",&r.codEstIntegra);
        flushStdin();

        //Insere com reaproveitamento de espaço
        insereReaproveitamento(Arquivo_bin, &r, &h);
    }

    //Atualiza o cabecalho
    //Com a inserção feita, haverá valores novos para o header que serão analisados
    Lista_estacao *Estacao = cria_lista_estacao();
    Lista_pares *Pares = cria_lista_pares();
    
    fseek(Arquivo_bin,0,SEEK_SET);
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
    h.nroEstacoes = 0;
    h.nroParesEstacao = 0;

    //Atualiza o numero de estacoes e de pares de estacoes
    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){

        binToRegister(Arquivo_bin,&r);

        if(r.removido == '0'){
            dataInHeader(Estacao,Pares,&h,r);
        }
    }
    
    //Atualiza status do cabecalho
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin);
    libera_lista(Pares, Estacao);
}