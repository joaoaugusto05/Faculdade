/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include "../define.h"
#include "func.h"
#include "string.h"
#include "../funcoesFornecidas.h"
#include <stdlib.h>

//Separa a string de acordo com um separador passado para a funcao e retorna uma string de acordo com a posicao tambem passada
char *strParser(char *str, char limitador, int pos){

    //Verifica se a string eh valida
	if(str == NULL){
		return NULL;
	}

	char *tmp =  malloc(strlen(str) * sizeof(char));

	int i = 0;
	int j = 0;
	int k = 0;
	
    //Cria uma string a partir da string principal delimitada pelo delimitador e a posicao
	while(i != strlen(str) && j < pos){

         //Reinicia a string caso o delimitador tenha sido atingido      
		if(str[i] == limitador){
			j++;
			tmp[k++] = '\0';
			k = 0;
		}else{
            //Anexa caractere a string
			tmp[k] = str[i];
			k++;	
		}
		
		i++;
    
	}
	
	if(str[i] == '\0'){
		tmp[k++] = '\0';

    }
    //Caso o Valor seja nulo eh retortnado -1
    if(strlen(tmp) == 0 || tmp[0]  == '\r' || tmp[0]  == '\n'){ 
        strcpy(tmp,"-1");
    }
    
	return tmp;
}

//Faz a leitura de um registro no arquivo .bin
void binToRegister(FILE *fp, REGISTER *r){

        //Le registros de tamanho fixo
        fread(&r->tamanhoRegistro,sizeof(int),1,fp);
        fread(&r->proxLista,sizeof(long int),1,fp);
        fread(&r->codEstacao,sizeof(int),1,fp);
        fread(&r->codLinha,sizeof(int),1,fp);
        fread(&r->codProxEstacao,sizeof(int),1,fp);
        fread(&r->distProxEstacao,sizeof(int),1,fp);
        fread(&r->codLinhaIntegra,sizeof(int),1,fp);
        fread(&r->codEstIntegra,sizeof(int),1,fp);
        char tmp[r->tamanhoRegistro - 32]; //Quis evitar de criar um vetor estatico entao joguei ele num dinamico para posteriormente separalo novamente pela funcao strparse
        
        //Le registro de tamanho varivel e utiliza a funcao strParser para a separacao das strings
        fgets(tmp,(r->tamanhoRegistro -32), fp);
        
        char pipe[1];
        fread(pipe,sizeof(char),1,fp);
        
        r->nomeEstacao = strParser(tmp,'|',1);
        // Pegamos cada uma das partes separadas pelo pipe atraves da funcao e adicionamo-as no registro
        
        r->nomeLinha = strParser(tmp,'|',2);
        

}

//Faz a comparacao das informacoes dos campos e valores passados com o registro
int compara_reg(REGISTER r, int num_campos, char **nome_campo, char **valor_campo){ 
    int correto = 0;

    //Compara caso a caso de acordo com os campos armazenados no vetor

    for(int i = 0; i < num_campos; i++){
        if(strcmp("tamanhoRegistro", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.tamanhoRegistro)
                correto++;
        }

        if(strcmp("proxLista", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.proxLista)
                correto++;
        }

        if(strcmp("codEstacao", nome_campo[i]) == 0){
            if(atoi(valor_campo[i])== r.codEstacao)
                correto++;
        }

        if(strcmp("codLinha", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.codLinha)
                correto++;
        }

        if(strcmp("codProxEstacao", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.codProxEstacao)
                correto++;
        }

        if(strcmp("distProxEstacao", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.distProxEstacao)
                correto++;
        }

        if(strcmp("codLinhaIntegra", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.codLinhaIntegra)
                correto++;
        }

        if(strcmp("codEstIntegra", nome_campo[i]) == 0){
            if(atoi(valor_campo[i]) == r.codEstIntegra)
                correto++;
        }

        if(strcmp("nomeEstacao", nome_campo[i]) == 0){
            

            if(strcmp(valor_campo[i], r.nomeEstacao) == 0){
                correto++;
            }
                
        }

        if(strcmp("nomeLinha", nome_campo[i]) == 0){
            if(strcmp(valor_campo[i], r.nomeLinha) == 0)
                correto++;
        }
    }
    return correto;
}

//Atualiza o cabecario sobre escrevendo o cabecalho com informacoes atualizadas
void atualiza_cabec(HEADER h, FILE *fp){
    fseek(fp, 0, SEEK_SET);
    fwrite(&h.status,sizeof(char),1, fp);
    fwrite(&h.topoLista,sizeof(long int),1, fp);
    fwrite(&h.nroEstacoes,sizeof(int),1, fp);
    fwrite(&h.nroParesEstacao,sizeof(int),1, fp);
}

//Imprime um registro passado, caso a informacao contida seja -1 imprime que a informacao eh "NULO"
void imprime_reg(REGISTER target){
    
    printf("%d ", target.codEstacao);
    printf("%s ", target.nomeEstacao);
    target.codLinha == -1 ? printf("NULO "):printf("%d ", target.codLinha);
    
    target.nomeLinha == NULL ? printf("NULO "):printf("%s ", target.nomeLinha);
    target.codProxEstacao == -1 ? printf("NULO "):printf("%d ", target.codProxEstacao);
    target.distProxEstacao == -1 ? printf("NULO "):printf("%d ", target.distProxEstacao);
    target.codLinhaIntegra == -1 ? printf("NULO "):printf("%d ", target.codLinhaIntegra);
    target.codEstIntegra == -1 ? printf("NULO\n"):printf("%d\n", target.codEstIntegra);

}

//Insere a informacao no registro a partir da string captada no CSV, utilizando ',' como separador
void insert_DataInReg(char *mensagem, REGISTER* target){
    
    char *tmp;

    target->removido = '0';
    target->tamanhoRegistro = 0;
    target->proxLista = -1;
    //Set de valores padrão

    //Daqui para baixo usamos o strParser.
    //Essa função "Quebra" a string recebida de acordo com o delimitador. O ultimo parametro refere-se a qual "Posicao" da palavra queremos receber
    //Assim, conseguimos escanear o csv baseado na posicao da palavra
    //É meio que uma adaptacao do strok
    //A funcao retorna -1 sempre que o valor lido for nulo uma vez que isso facilita o processo de inserção em binario e nao atrapalha a leitura do tamanho (FIXO)

    tmp = strParser(mensagem, ',', 1);
    target->codEstacao = atoi(tmp);
    free(tmp);
    
    tmp = strParser(mensagem, ',', 3);
    target->codLinha = atoi(tmp);
    free(tmp);
    
    tmp = strParser(mensagem, ',', 5);
    target->codProxEstacao = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 6);
    target->distProxEstacao = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 7);
    target->codLinhaIntegra = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 8);
    target->codEstIntegra = atoi(tmp);
    free(tmp);

    tmp = strParser(mensagem, ',', 2);
    target->nomeEstacao = malloc(sizeof(char) * strlen(tmp));
    strcpy(target->nomeEstacao, (tmp));
    free(tmp);

    tmp = strParser(mensagem, ',', 4);
    target->nomeLinha = malloc(sizeof(char) * strlen(tmp));
 
    if(strcmp(tmp, "-1") == 0){
        free(target->nomeLinha);
        target->nomeLinha = NULL;
    }
    else{
        strcpy(target->nomeLinha, tmp);
    }
    
    free(tmp);

    //Calcula o tamanho do registro de acordo com o tamanho dos registros fisicos(32) e adicionando o tamanho dos registros variaveis e dos delimitadores
    target->tamanhoRegistro = 32 + strlen(target->nomeEstacao) + strlen(target->nomeLinha) + 2;
    
    
    
    
}

//Insere o registro no arquivo .bin
void insert_regInBin(REGISTER *r, FILE *fp){
    char pipe = '|'; // Tava dando problema quando eu dava fwrite "|" entao definimos o pipe
    //A funcao pega os dados do Registro e escreve no arquivo recebido

    //Insre os campos de tamanho fixo
    fwrite(&r->removido,sizeof(char),1,fp);
    fwrite(&r->tamanhoRegistro,sizeof(int),1,fp);
    fwrite(&r->proxLista,sizeof(long int),1,fp);
    fwrite(&r->codEstacao,sizeof(int),1,fp);
    fwrite(&r->codLinha,sizeof(int),1,fp);
    fwrite(&r->codProxEstacao,sizeof(int),1,fp);
    fwrite(&r->distProxEstacao,sizeof(int),1,fp);
    fwrite(&r->codLinhaIntegra,sizeof(int),1,fp);
    fwrite(&r->codEstIntegra,sizeof(int),1,fp);

    //Insere os campos de tamanho variavel mais os delimitadores
    fwrite(r->nomeEstacao,sizeof(char),strlen(r->nomeEstacao),fp);
    fwrite(&pipe ,sizeof(char),1,fp);
    fwrite(r->nomeLinha,sizeof(char),strlen(r->nomeLinha),fp);
    fwrite(&pipe,sizeof(char),1,fp);
      
}

//Insere na lista da estacao e na lista de pares de estacao
void dataInHeader(Lista_estacao* Estacao, Lista_pares* par, HEADER *h, REGISTER r){

    insere_lista_final_estacao(Estacao, r, h);
    insere_lista_final_pares(par, r, h);
}


//Insere o lixo predeterminado nas especificacoes no restante do registro reaproveitado
void colocaLixo(FILE *Arquivo_bin, int n){
    char lixo =  '$';
    //Insere Lixo nos dados restantes do registro antigo
    for(int i = 0; i < n; i++){
        fwrite(&lixo,sizeof(char),1,Arquivo_bin);
    }
}

//Funcao para limpar o buffer do teclado em casos de entrada "NULO"
void flushStdin(){

    char c;
    c = fgetc(stdin);
    //Limpa buffer do teclado ate chegar ao proximo limitador
    while(c != EOF && c != ' ' && c != '\n' && c != '\0'){
        c = fgetc(stdin);
    }
}



//Atualiza os registros de acordo com os valores passados nos vetores de string
void atualizaReg(char **nome_campo, char **valor_campo,int num_campos, REGISTER *r){

    for(int i = 0; i < num_campos; i++){

        //Realiza comparacoes dos campos e se for compativel atualiza o dado do registro
        if(strcmp("codEstacao", nome_campo[i]) == 0){
            r->codEstacao = atoi(valor_campo[i]);
        }

        if(strcmp("codLinha", nome_campo[i]) == 0){
            r->codLinha = atoi(valor_campo[i]);
        }

        if(strcmp("codProxEstacao", nome_campo[i]) == 0){
            r->codProxEstacao = atoi(valor_campo[i]);
        }

        if(strcmp("distProxEstacao", nome_campo[i]) == 0){
            r->distProxEstacao = atoi(valor_campo[i]);
        }

        if(strcmp("codLinhaIntegra", nome_campo[i]) == 0){
            r->codLinhaIntegra = atoi(valor_campo[i]);
        }

        if(strcmp("codEstIntegra", nome_campo[i]) == 0){
            r->codEstIntegra = atoi(valor_campo[i]);
        }

        if(strcmp("nomeEstacao", nome_campo[i]) == 0){
            r->nomeEstacao = malloc(sizeof(char) * strlen(valor_campo[i]) + 1);
            strcpy(r->nomeEstacao, valor_campo[i]); 
        }

        if(strcmp("nomeLinha", nome_campo[i]) == 0){
            r->nomeLinha = malloc(sizeof(char) * strlen(valor_campo[i]) + 1);
            strcpy(r->nomeLinha, valor_campo[i]);
        }

    }

    //Atualiza o tamanho do registro
    r->tamanhoRegistro = 32 + strlen(r->nomeEstacao) + strlen(r->nomeLinha) + 2;
    return;
}

//Insere o registro com reaproveitando os espaços dos registros removidos
void insereReaproveitamento(FILE *Arquivo_bin,REGISTER *r, HEADER *h){
                
				fseek(Arquivo_bin, 0 ,SEEK_SET);
				r->removido = '0';

                //Recalcula o tamanho de registro
                r->tamanhoRegistro = 32 + strlen(r->nomeEstacao) + strlen(r->nomeLinha) + 2;
				r->proxLista = -1;
				
				//Le o cabecalho recuperando infos
				fread(&h->status,sizeof(char),1,Arquivo_bin);
				fread(&h->topoLista,sizeof(long int),1,Arquivo_bin);
				fread(&h->nroEstacoes,sizeof(int),1,Arquivo_bin);
				fread(&h->nroParesEstacao,sizeof(int),1,Arquivo_bin);
				
				char removido = ' ';
				int tamanhoRegistro = 0;
				
				long int antLista =  0;
				long int atLista = h->topoLista;
				long int proxLista = -1;
				
				//Flag para verificar se foi gravado no meio do arquivo o registro
				int gravou = 0;
				//---------
				//Procura o proximo da lista ate encontrar um endereco invalido
				while(atLista != -1){
					
					//Coloca o ponteiro no bityoffset indicado no cabecalho 
					fseek(Arquivo_bin,atLista,SEEK_SET);

					//Le o inicio do registro
					fread(&removido,sizeof(char),1,Arquivo_bin);
					fread(&tamanhoRegistro,sizeof(int),1,Arquivo_bin);
					fread(&proxLista,sizeof(long int),1,Arquivo_bin);
					
					//Compara o tamanho dos registros se o registro a ser inserido for menor que um que foi excluido sera permitida a insercao
					if(tamanhoRegistro >= r->tamanhoRegistro){

						//Armazena tamanho antigo do registro
						int tam_tmp = r->tamanhoRegistro;

						//Atualiza o tamanho do registro para o mesmo de onde ele sera inserido
						r->tamanhoRegistro = tamanhoRegistro;

						//Posiciona o ponteiro do arquivo pro inicio do registro
						fseek(Arquivo_bin,atLista,SEEK_SET);

						 //Sobrescreve o registro
						insert_regInBin(r,Arquivo_bin);
						
						//Coloca lixo no restante do registro anterior
						colocaLixo(Arquivo_bin, (tamanhoRegistro - tam_tmp));
						gravou = 1;


						//Atualiza o "Proximo Lista" ou o "Topo Lista" de acordo com a situacao
						if(antLista == 0){
							fseek(Arquivo_bin,antLista,SEEK_SET);
							fread(&h->status,sizeof(char),1,Arquivo_bin);
							fwrite(&proxLista,sizeof(long int),1,Arquivo_bin);

						}else{
							fseek(Arquivo_bin,antLista,SEEK_SET);
							fread(&removido,sizeof(char),1,Arquivo_bin);
							fread(&tamanhoRegistro,sizeof(int),1,Arquivo_bin);
							fwrite(&proxLista,sizeof(long int),1,Arquivo_bin);
						}

						break;
					}else{
						antLista = atLista;
						atLista = proxLista;
					}
					
				}
				//----------
				if(gravou == 0){
					fseek(Arquivo_bin,0,SEEK_END);
					insert_regInBin(r,Arquivo_bin);
				}

                //Libera as informacoes alocadas
				fseek(Arquivo_bin,0,SEEK_SET);
				free(r->nomeEstacao);
				free(r->nomeLinha);
				//---------
                return;
}
