/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Imprime todos os registros de acordo com um filtro
void func_three(){
    //Le nome do arquivo
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);

    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
    
    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    //Le numero de campos de filtro
    int num_campos;     
    scanf("%d", &num_campos);

    char **nome_campo = (char **)malloc(sizeof(char*)* num_campos);
    char **valor_campo = (char **)malloc(sizeof(char*)* num_campos);
    //Criei um ponteiro de ponteiros. Sei que *char tera tamanho N por ser o numero total de registros. Os demais valores selao malocados depois
    
    char *tmp = malloc(sizeof(char) * 100);
    //Criei um char temp de tamanho fixo pra fazer um malloc mais correto no valor

    int achou = 0;
    for(int i = 0; i < num_campos; i++){
        scanf("%ms", &nome_campo[i]);

        if(strcmp(nome_campo[i], "nomeEstacao") == 0 || strcmp(nome_campo[i], "nomeLinha") == 0){
            scan_quote_string(tmp);
            valor_campo[i] = calloc(strlen(tmp),sizeof(char) + 1);
            strcpy(valor_campo[i], tmp);
        }
        else{
            scanf("%ms", &valor_campo[i]);
        }

        //Aqui eu escaneio de uma vez todos os valores e ja os armazeno. Resolvi fazer assim pra nao ocorrer de printar logo após voce digitar o comando
        //Eu tenho que conferir se o campo vai ser uma string ou nao, pois se for, eu uso o scanquote e senão eu posso scanear normalmente e malocar


    }
    free(tmp);
    HEADER h;
    REGISTER r;

    
   
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
    
    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        binToRegister(Arquivo_bin, &r);
        //Lemos registro por registro até o fim do arquivo
    


    int correto = compara_reg(r,num_campos,nome_campo,valor_campo); //Essa função retorna quantos campos do registro tem o valor semelhante aos campos/valores passados para ela
    if(correto == num_campos){ // Se todos os campos forem iguais..
        if(r.removido != '1'){
        imprime_reg(r);
        achou = 1;
        }
        
    }

    

    free(r.nomeEstacao);
    free(r.nomeLinha);

    }
   if(achou == 0){
       printf("Registro inexistente.\n");
   }
   //Liberação da memoria
   for(int z = 0; z < num_campos; z++){
            free(nome_campo[z]);
            free(valor_campo[z]);
    }

        free(nome_campo);
        free(valor_campo);

   free(nome_arquivo_bin);
   fclose(Arquivo_bin);
    


}   