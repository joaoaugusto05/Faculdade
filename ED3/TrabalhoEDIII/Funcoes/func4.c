/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

void func_four(){
    //Le nome do arquivo .bin
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    
    //Le numero de arquivos a ser removido
    int num_repeticoes;     
    scanf("%d", &num_repeticoes);
    
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
    Lista_estacao* li = cria_lista_estacao();
    Lista_pares *pares = cria_lista_pares();
    
        //Le cabecalho
        fseek(Arquivo_bin, 0, SEEK_SET);    
        fread(&h.status,sizeof(char),1,Arquivo_bin);
        fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
        fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
        fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
        
        //Atualiza as informacoes de quantidade de estacoes e de pares de estacao. Precisamos saber quais sao as estações repetidas para manter o controle de inserção e exclusao
        h.nroEstacoes = 0;
        h.nroParesEstacao = 0;
        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            binToRegister(Arquivo_bin, &r);
            
            if(r.removido == '0'){
                dataInHeader(li, pares, &h, r);
            }
            free(r.nomeEstacao);
            free(r.nomeLinha);
        }     
        

    for(int i = 0; i < num_repeticoes; i++){           
        fseek(Arquivo_bin, 17, SEEK_SET); //Para cada repetição, começaremos a ler apenas do primeiro registro. Nao precisa ler o cabeçalho toda hora
        int num_campos;     

        //Le numero de campos de pesquisa
        scanf("%d", &num_campos);



        char **nome_campo = (char **)calloc(num_campos , sizeof(char*));
        char **valor_campo = (char **)calloc(num_campos, sizeof(char*));
        char *tmp = malloc(sizeof(char) * 100);

        //Le campos de pesquisa e valores que serao usados como filtro
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
        long int byteoffset;
        //o byte offset será relacionado ao valor de cada registro.
    
        

        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            
            //Eu leio o arquivo até nao ser o fim dele. O byteoffset será a posição atual - 1, pois no while ja realizei a leitura de um char
            byteoffset = ftell(Arquivo_bin) - 1;

            //Le o registro do arquivo
            binToRegister(Arquivo_bin, &r);

            if(r.removido == '1'){
                //Se ele tiver removido não consideramos para essa função
                    free(r.nomeEstacao);
                    free(r.nomeLinha);                      
                    continue;
                }
                
            
            //Verifica se esta de acordo com os filtros
            int correto = compara_reg(r, num_campos, nome_campo, valor_campo);
            
            
            if(correto == num_campos){
                if(r.removido != '1')

                    //Reduz o numero de estacao e de pares de estacao dentro das listas
                    retira_numEst(li, &h, r);
                    retira_estPares(pares, &h, r);
                    
                    
                    //Marca o registro como logicamente removido
                    //Primeiro, voltamos ao inicio do registro. Eu preferi usar o SEEK_CUR - tamanho do registro pois acredito que ler alguns bytes para trás seria mais eficiente do que voltar e ler desde o inicio do arquivo procurando o byteoffset
                    //Mas na teoria, é o mesmo que usar fseek(Arquivo_bin, byteoffset, SEEK_SET);
                    fseek(Arquivo_bin, -r.tamanhoRegistro - 5, SEEK_CUR);
                    //Para marcar como removido, primeiro colocamos seu valor = '1'
                    fputc('1', Arquivo_bin);

                    //Ao avançar 4 bytes do SEEK_CUR, após colocarmos o removido, chegaremos no campo "ProxLista"
                    //Para a remoção, este valor deverá receber o long int presente no Topo Lista
                    fseek(Arquivo_bin, 4, SEEK_CUR);
                    fwrite(&h.topoLista, sizeof(long int), 1, Arquivo_bin);
                    //Aqui o TopoLista foi escrito no binario removido, como explicado

                    fseek(Arquivo_bin, byteoffset + r.tamanhoRegistro + 5, SEEK_SET); //Voltamos o ponteiro de leitura a posição "Inicial", ou seja, ao registro subsequente ao que acabou de ser removido
                    h.topoLista = byteoffset;
                    //O cabeçalho terá seu valor de topo da lista atualizado. Porém, a reescrita deste não ocorrerá todo momento por questoes de eficiencia

                    
                    
                    
            }
            
            //Libera memoria
            free(r.nomeEstacao);
            free(r.nomeLinha);
        }
        //Atualiza o cabecalho
        //RETIRADO
        //atualiza_cabec(h ,Arquivo_bin); // Atualizamos o cabeçalho com os valores de topolista, nroPares e estações atualizadas

        //Liberacao de memoria
        for(int z = 0; z < num_campos; z++){
            free(nome_campo[z]);
            free(valor_campo[z]);
    }

        free(nome_campo);
        free(valor_campo);
       
    }
    
    //Atualiza status do cabecalho
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);

    //Libera Lista
    libera_lista(pares, li);
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin);
    free(nome_arquivo_bin);
}
