/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Criar arquivo .bin a partir de um .csv
void func_one(){

    //Le nome dos arquivos
    char *nome_arquivo_csv;
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_csv);
    scanf("%ms", &nome_arquivo_bin);
    //Criamos os valores do nome do arquivo para abrir semelhante ao segundo aulão dado
    FILE *Arquivo_csv = fopen(nome_arquivo_csv, "rb");
    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"wb");

    if(Arquivo_bin == NULL || Arquivo_csv == NULL){
        printf("Falha no processamento do arquivo.");
    }

    HEADER h;
    Lista_estacao *li = cria_lista_estacao();
    Lista_pares *pares = cria_lista_pares();
    //Fazemos a criação de listas. Elas servirao pra manter os dados do cabeçalho atualizados

    h.status = '0';
    h.topoLista = -1;
    h.nroEstacoes = 0;
    h.nroParesEstacao = 0;

    atualiza_cabec(h, Arquivo_bin);
    //Escrevemos o cabeçalho com os valores iniciais que serão atualizados posteriormente

    char cabec_lixo[1024];
    fgets(cabec_lixo, 1024, Arquivo_csv);
    //Descartamos a primeira linha 

    REGISTER r;
    char values[1024];
    
    //Lemos linha por linha do registro até o fim do arquivo
    while(fgets(values, 1024, Arquivo_csv)){

            insert_DataInReg(values, &r);    //As informações do binario serão convertidos em um registro
            dataInHeader(li, pares, &h, r); // O registro sera contabilizado nas informações das listas criadas
            insert_regInBin(&r, Arquivo_bin);//Finalmente, o registro será convertido e escrito no arquivo binario
        
        }
   
    //Atualiza cabecalho. A função dataInHeader já recebe o cabeçalho por referencia, então o nosso cabeçalho é a versão "Atual", pois ela mesma ja foi modificada
    //Entao, setamos o status para um e chamamos a função de atualização. Ela só volta ao inicio do arquivo e sobreescreve os valores
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    fclose(Arquivo_csv);
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin); //Funcao solicitada
    libera_lista(pares, li);
    
    }