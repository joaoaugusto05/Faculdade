/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Atualiza um registro de acordo com os filtros passados
void func_six(){
	
	HEADER h;
    REGISTER r;
	
    //Le o nome do arquivo
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);

    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb+");

    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }
    
    //Marca arquivo como aberto
    fputc('0', Arquivo_bin);
    fseek(Arquivo_bin, 0, SEEK_SET);

    //Le o numero de pesquisas
    int num_pesquisas;
    scanf("%d", &num_pesquisas);
	
    for(int k = 0; k < num_pesquisas; k++){
        //Le numero de campos de pesquisa
        int num_campos;
        scanf("%d", &num_campos);


        char **nome_campo = (char **)calloc(num_campos , sizeof(char*));
        char **valor_campo = (char **)calloc(num_campos, sizeof(char*));
        char *tmp = malloc(sizeof(char) * 100);
        //Le campos de pesquisa e valores para filtro
        for(int j = 0; j < num_campos; j++){

            scanf("%ms ", &nome_campo[j]);
         

            if(strcmp(nome_campo[j], "nomeEstacao") == 0 || strcmp(nome_campo[j], "nomeLinha") == 0){
                scan_quote_string(tmp);
                valor_campo[j] = calloc(strlen(tmp) + 1,sizeof(char));
                strcpy(valor_campo[j], tmp);
            }
            else{
                
                scanf("%ms", &valor_campo[j]);
           

            }
        }
        free(tmp);
        
        //Le numero de campos que serao atualizados
        int num_atualiza;
        scanf("%d", &num_atualiza);

        char **nome_campo_atualiza = (char **)calloc(num_campos , sizeof(char*));
        char **valor_campo_atualiza = (char **)calloc(num_campos, sizeof(char*));
 
        //Le campos de pesquisa e valores para atualizar o registro
        for(int j = 0; j < num_atualiza; j++){

            scanf("%ms ", &nome_campo_atualiza[j]);
         

            if(strcmp(nome_campo_atualiza[j], "nomeEstacao") == 0 || strcmp(nome_campo_atualiza[j], "nomeLinha") == 0){
                valor_campo_atualiza[j] = malloc(sizeof(char)* 100);
                scan_quote_string(valor_campo_atualiza[j]);
            }
            else{
                
                scanf("%ms", &valor_campo_atualiza[j]);
        

            }
        }
        
        //Retorna para o inicio do Arquivo e le o cabecalho
        fseek(Arquivo_bin, 0,SEEK_SET);
        fread(&h.status,sizeof(char),1,Arquivo_bin);
        fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
        fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
        fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
        int byteoffset = 17;
        int cnt = 0;
       
        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            
			byteoffset = ftell(Arquivo_bin) - 1;

            //Le o registro do arquivo .bin
            binToRegister(Arquivo_bin, &r);

            cnt++;
            
            //verifica se o registro foi removido
            if(r.removido == '1'){
                free(r.nomeEstacao);
                free(r.nomeLinha);
                continue;
            }
            

        //Compara o registro com os criterios inseridos
        int correto = compara_reg(r, num_campos, nome_campo, valor_campo);
        
        
        if(correto == num_campos){
            //Atualiza tamanho do registro
            //Salvamos o tamanho antigo em um int pois precisaremos reutiliza-lo
            int tam_ant = r.tamanhoRegistro;
            //Atualiza os campos do registro com os dados inseridos
            atualizaReg(nome_campo_atualiza, valor_campo_atualiza, num_atualiza, &r); 
		
            //Verifica se o registro atualizado ainda cabe dentro de seu espaco em disco anterior
            if(tam_ant >= r.tamanhoRegistro){
                //Se o tamanho antigo for maior que o atual, voltamos ao inicio deste e os sobreescrevemos com os valores novos
                //Verifica a quantidade de lixo a ser adicionado
                int lixo = tam_ant - r.tamanhoRegistro;

                //Voltamos ao inicio
                fseek(Arquivo_bin, byteoffset,SEEK_SET);
                r.tamanhoRegistro = tam_ant;

                //Insere o registro atualizado no binario
                insert_regInBin(&r,Arquivo_bin);

                //Insere lixo caso necessario
                colocaLixo(Arquivo_bin, lixo);
                fseek(Arquivo_bin, byteoffset + r.tamanhoRegistro + 5, SEEK_SET); //Retornamos o ponteiro para a leitura do registro subsequente

            }else{
                //É meio que uma junção da 4 e da 5
                //Marca Registro como removido
                fseek(Arquivo_bin, -tam_ant - 5, SEEK_CUR);
                fputc('1', Arquivo_bin);

                //Atualiza proximo da lista no registro
                fseek(Arquivo_bin, 4, SEEK_CUR);
                fwrite(&h.topoLista, sizeof(long int), 1, Arquivo_bin);    

                //Atualiza cabecalho    
                h.topoLista = byteoffset;
                
                //Nesta situação, o binario será atualizado pois suas informações são necessarias na função de inserir com reaproveitamento
                atualiza_cabec(h, Arquivo_bin);

                //Insere em modo de reaproveitamento
                insereReaproveitamento(Arquivo_bin, &r, &h);              
                fseek(Arquivo_bin, byteoffset + tam_ant + 5, SEEK_SET);               
            }
            
        }
    

        }

        //Libera memoria    
        for(int z = 0; z < num_campos; z++){
            free(nome_campo[z]);
            free(valor_campo[z]);
         }

        for(int z = 0; z < num_atualiza; z++){
            free(nome_campo_atualiza[z]);
            free(valor_campo_atualiza[z]);
        }

        free(valor_campo);
        free(nome_campo);
        free(nome_campo_atualiza);
        free(valor_campo_atualiza);
    }
	
	//Atualiza o cabecalho
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

    //Atualiza o status do cabecalho
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    fclose(Arquivo_bin);

    binarioNaTela(nome_arquivo_bin);
    free(nome_arquivo_bin);
    libera_lista(Pares, Estacao);
   
    return;
}