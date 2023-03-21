/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Imprime todos os registros
void func_two(){

    //Le nome do aquivo
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
    //Realiza o mesmo procedimento de leitura e abrir o arquivo
    int ctn = 0;
    //Contador serve para conferir a condicional dada na proposta do exercicio de registro inexistente
    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    HEADER h;
    REGISTER r;
   
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
  
    //Le o cabecalho inicialmente
    if(h.nroEstacoes == 0){
        printf("Registro inexistente.\n");
        return;
    }
    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        binToRegister(Arquivo_bin, &r);
        if(r.removido != '1')
            imprime_reg(r); // Imprimimos e damos um free nos ponteiros que poderao ser reutilizados. Logicamente, o registro so sera impresso se nao estiver removido
        free(r.nomeEstacao);
        free(r.nomeLinha);
 
        ctn++;
    }


   free(nome_arquivo_bin);
   fclose(Arquivo_bin);
}