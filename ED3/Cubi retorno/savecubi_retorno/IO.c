/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
CUBI */
#include <stdio.h>
#include "define.h"
#include "IO.h"
#include "string.h"
#include "funcoesFornecidas.h"
#include <stdlib.h>
#include "ListaDinEncad.h"

void libera_lista_est(Lista_estacao* li){
    if(li != NULL){
        Elem_est* no;
        while((*li) != NULL){

            no = *li;
            *li = (*li)->prox;
            free(no->nome);
            free(no);
        }
        free(li);
    }
}
void libera_lista_pares(Lista_pares* li){
    if(li != NULL){
        Elem_pares* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

void libera_lista(Lista_pares* par, Lista_estacao *est){
    libera_lista_est(est);
    libera_lista_pares(par);
}

Lista_pares* cria_lista_pares(){
    Lista_pares* li = (Lista_pares*) malloc(sizeof(Lista_pares));
    if(li != NULL)
        *li = NULL;
    return li;
}

int insere_lista_final_pares(Lista_pares* li, REGISTER r, HEADER *h){
    
    
    if(li == NULL)
        return 0;

    Elem_pares *no;
    no = (Elem_pares*) malloc(sizeof(Elem_pares));
    if(no == NULL)
        return 0;
        
    no->repeticoes = 0;
    no->codEstacaoNo = r.codEstacao;
    no->codProxEstacaoNo = r.codProxEstacao;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        no->ant = NULL;
        *li = no;
        

    }else{        
        Elem_pares *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(r.codEstacao == aux->codEstacaoNo && r.codProxEstacao == aux->codProxEstacaoNo){
                aux->repeticoes++;
                return 1;
            }          
            aux = aux->prox;
        }   
            aux->prox = no;
            no->ant = aux;
                   
        
    }
    if(r.codEstacao != -1 && r.codProxEstacao != -1)
                h->nroParesEstacao++; 

    return 1;
}

Lista_estacao* cria_lista_estacao(){
    Lista_estacao* li = (Lista_estacao*) malloc(sizeof(Lista_estacao));
    if(li != NULL)
        *li = NULL;
    return li;
}

void imprime_lista(Lista_estacao* li){
    if(li == NULL)
        return;
    Elem_est* no = *li;
    while(no != NULL){
        printf("Nome: %s\n", no->nome);
        printf("Repeticoes: %d\n", no->repeticoes);
        no = no->prox;
    }
}

int insere_lista_final_estacao(Lista_estacao* li, REGISTER r, HEADER *h){
    
    if(li == NULL)
        return 0;
    Elem_est *no;
    no = (Elem_est*) malloc(sizeof(Elem_est));
    if(no == NULL)
        return 0;
    no->nome = (char*)malloc(sizeof(char)*strlen(r.nomeEstacao) + 1);
    strcpy(no->nome, r.nomeEstacao);
    no->repeticoes = 0;
    no->prox = NULL;

    if((*li) == NULL){//lista vazia: insere início
        *li = no;
        no->ant = NULL;
        h->nroEstacoes++;

    }else{
        
        Elem_est *aux;
        aux = *li;
        while(aux->prox != NULL){
            if(strcmp(aux->nome, no->nome) == 0){
                aux->repeticoes++;
                return 1;
            }          
            aux = aux->prox;
        }   
            aux->prox = no;
            no->ant = aux;
            h->nroEstacoes += 1;        
        
    }


    return 1;
}

int compara_reg(REGISTER r, int num_campos, char **nome_campo, char **valor_campo){
    int correto = 0;
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

void atualiza_cabec(HEADER h, FILE *fp){
    fseek(fp, 0, SEEK_SET);
    fwrite(&h.status,sizeof(char),1, fp);
    fwrite(&h.topoLista,sizeof(long int),1, fp);
    fwrite(&h.nroEstacoes,sizeof(int),1, fp);
    fwrite(&h.nroParesEstacao,sizeof(int),1, fp);
}

void binToRegister(FILE *fp, REGISTER *r){

        //printf("BIN AQUI1\n");
        fread(&r->tamanhoRegistro,sizeof(int),1,fp);
        fread(&r->proxLista,sizeof(long int),1,fp);
        fread(&r->codEstacao,sizeof(int),1,fp);
        fread(&r->codLinha,sizeof(int),1,fp);
        fread(&r->codProxEstacao,sizeof(int),1,fp);
        fread(&r->distProxEstacao,sizeof(int),1,fp);
        fread(&r->codLinhaIntegra,sizeof(int),1,fp);
        fread(&r->codEstIntegra,sizeof(int),1,fp);
        //printf("BIN AQUI2\n");
        char *tmp = (char *)calloc(sizeof(char),r->tamanhoRegistro - 32);
        //char tmp[r->tamanhoRegistro - 32]; //Quis evitar de criar um vetor estatico entao joguei ele num dinamico para posteriormente separalo novamente pela funcao strparse
        //printf("BIN AQUI3\n");
        fgets(tmp,(r->tamanhoRegistro -32), fp);
        //printf("BIN AQUI4\n");
        //printf(">>>>>>>>>>>>>>>>>>>>tmp: %s \n",tmp);
        char pipe[1];
        //printf("BIN AQUI5\n");
        fread(pipe,sizeof(char),1,fp);
        //printf("BIN AQUI6\n");
        
        r->nomeEstacao = strParser(tmp,'|',1);
        //printf("BIN AQUI6\n");
 // Pegamos cada uma das partes separadas pelo pipe atraves da funcao e adicionamo-as no registro
        
        r->nomeLinha = strParser(tmp,'|',2);
        //printf("BIN AQUI7\n");
        free(tmp);

}

char *strParser(char *str, char limitador, int pos){

	if(str == NULL){
		return NULL;
	}

	char *tmp =  malloc(strlen(str) * sizeof(char));

	int i = 0;
	int j = 0;
	int k = 0;
	
	while(i != strlen(str) && j < pos){
		
       
        
		if(str[i] == limitador){
			j++;
			tmp[k++] = '\0';
			k = 0;
		}else{
			tmp[k] = str[i];
			k++;	
		}
		
		i++;
    
	}
	
	if(str[i] == '\0'){
		tmp[k++] = '\0';

    }
    if(strlen(tmp) == 0 || tmp[0]  == '\r' || tmp[0]  == '\n'){ 
        strcpy(tmp,"-1");
    }
    
	return tmp;
}

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

        target->tamanhoRegistro = 32 + strlen(target->nomeEstacao) + strlen(target->nomeLinha) + 2;
    
    
    
    
}


void insert_regInBin(REGISTER *r, FILE *fp){
    char pipe = '|'; // Tava dando problema quando eu dava fwrite "|" entao definimos o pipe
    //A funcao pega os dados do cabeçalho e escreve no arquivo recebido

    fwrite(&r->removido,sizeof(char),1,fp);


    fwrite(&r->tamanhoRegistro,sizeof(int),1,fp);

    fwrite(&r->proxLista,sizeof(long int),1,fp);
    fwrite(&r->codEstacao,sizeof(int),1,fp);
    fwrite(&r->codLinha,sizeof(int),1,fp);
    fwrite(&r->codProxEstacao,sizeof(int),1,fp);
    fwrite(&r->distProxEstacao,sizeof(int),1,fp);
    fwrite(&r->codLinhaIntegra,sizeof(int),1,fp);
    fwrite(&r->codEstIntegra,sizeof(int),1,fp);


    fwrite(r->nomeEstacao,sizeof(char),strlen(r->nomeEstacao),fp);
    fwrite(&pipe ,sizeof(char),1,fp);
    
    fwrite(r->nomeLinha,sizeof(char),strlen(r->nomeLinha),fp);
    

    fwrite(&pipe,sizeof(char),1,fp);
   
    
}

void dataInHeader(Lista_estacao* Estacao, Lista_pares* par, HEADER *h, REGISTER r){
    insere_lista_final_estacao(Estacao, r, h);
    insere_lista_final_pares(par, r, h);
    }

void func_one(){
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
    //ListaEstacoes Estacoes = cria_lista_estacoes();
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

            insert_DataInReg(values, &r);    
            dataInHeader(li, pares, &h, r);
            insert_regInBin(&r, Arquivo_bin);
        
        }
   
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    fclose(Arquivo_csv);
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin); //Funcao solicitada
    
}

void func_two(){
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
    //Realiza o mesmo procedimento de leitura e abrir o arquivo
    int ctn = 0;
    
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

    printf("h.status: %c \n",h.status);
    printf("h.topoLista %ld \n",h.topoLista);
    printf("h.nroEstacoes %d \n",h.nroEstacoes);
    printf("h.nroParesEstacao %d \n",h.nroParesEstacao);

    //Le o cabecalho inicialmente e o printa a parte
    if(h.nroEstacoes == 0){
        printf("Registro inexistente.\n");
        return;
    }
    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        binToRegister(Arquivo_bin, &r);
        imprime_reg(r); // Imprimimos e damos um free nos ponteiros que poderao ser reutilizados
        free(r.nomeEstacao);
        free(r.nomeLinha);
 
        ctn++;
    }


   free(nome_arquivo_bin);
   fclose(Arquivo_bin);
}

void func_three(){
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);

    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
    
    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    int num_campos;     
    scanf("%d", &num_campos);

    char **nome_campo = (char **)malloc(sizeof(char*)* num_campos);
    char **valor_campo = (char **)malloc(sizeof(char*)* num_campos);
    //Criei um ponteiro de ponteiros. Sei *char tera tamanho N por ser o numero total de registros. Os demais valores selao malocados depois
    
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
        
    


    int correto = compara_reg(r,num_campos,nome_campo,valor_campo);
    if(correto == num_campos){
        imprime_reg(r);
        achou = 1;
    }

    

    free(r.nomeEstacao);
    free(r.nomeLinha);

    }
   if(achou == 0){
       printf("Registro inexistente.\n");
   }
   for(int z = 0; z < num_campos; z++){
            free(nome_campo[z]);
            free(valor_campo[z]);
    }

        free(nome_campo);
        free(valor_campo);

   free(nome_arquivo_bin);
   fclose(Arquivo_bin);
    


}   

void retira_estPares(Lista_pares* li, HEADER *h, REGISTER r){

        printf("RETIRA EST AQUI1\n");
        Elem_pares *aux;
        aux = *li;
        printf("RETIRA EST AQUI2\n");

        while(aux->prox != NULL){
            printf("RETIRA EST AQUI3\n");
            if(r.codEstacao == aux->codEstacaoNo && r.codProxEstacao == aux->codProxEstacaoNo){
                printf("RETIRA EST AQUI4\n");
                
                if(aux->repeticoes < 0){
                    printf("RETIRA EST AQUI5\n");
                    if(aux->ant == NULL){
                       printf("RETIRA EST AQUI5\n");
                        aux = aux->prox;
                       printf("RETIRA EST AQUI6\n");
                    }
                    else{
                        printf("RETIRA EST AQUI7\n");
                        aux->ant->prox = aux->prox;
                        printf("RETIRA EST AQUI8\n");
                    }
                    printf("RETIRA EST AQUI9\n");
                    if(aux->codProxEstacaoNo != -1){     
                        printf("RETIRA EST AQUI10\n");                  
                        h->nroParesEstacao--;
                        printf("RETIRA EST AQUI11\n");
                }   
                printf("RETIRA EST AQUI12\n");
                    free(aux);
                    return;
                }
            }
                
                
            printf("RETIRA EST AQUI13\n");
            aux = aux->prox;
        } 
          
         printf("RETIRA EST AQUI14\n");               
    return;
}
void retira_numEst(Lista_estacao* li, HEADER *h, REGISTER r){
    Elem_est *aux;
        aux = *li;
        while(aux->prox != NULL){
            
            if(strcmp(aux->nome, r.nomeEstacao) == 0){

                aux->repeticoes--;
                
                if(aux->repeticoes < 0){
                    if(aux->ant == NULL){
                        aux = aux->prox;
                    }
                    else{
                        aux->ant->prox = aux->prox;
                    }
                    free(aux->nome);                     
                    free(aux);
                    h->nroEstacoes--;
                    return;
                }
            }
                
                
      
            aux = aux->prox;
        }   
                        
    return;

}
void retira_cabecalho(Lista_estacao *estacao, Lista_pares* par, HEADER *h, REGISTER r){
    printf("RETIRA CABEC AQUI1\n");
    retira_estPares(par, h, r);
    printf("RETIRA CABEC AQUI2\n");
    retira_numEst(estacao, h, r);
    printf("RETIRA CABEC AQUI3\n");
}

void func_four(){

    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    
  
    int num_repeticoes;     
    scanf("%d", &num_repeticoes);
    
    FILE *Arquivo_bin = fopen(nome_arquivo_bin, "rb+");
    if(Arquivo_bin == NULL){
            printf("Falha no processamento do arquivo.");
            return;
        }
    HEADER h;
    REGISTER r;


    fseek(Arquivo_bin, 17, SEEK_SET);
    /*
    while(fread( &r.removido,sizeof(char),1,Arquivo_bin) != 0){
            binToRegister(Arquivo_bin, &r);
            if(r.removido == '1' || r.codEstacao == -1 || r.nomeEstacao == NULL)
                dataInHeader(li, pares, &h, r);
            free(r.nomeEstacao);
            free(r.nomeLinha);
    }
    */

    for(int i = 0; i < num_repeticoes; i++){   
             
        fseek(Arquivo_bin, 0, SEEK_SET);    
        fread(&h.status,sizeof(char),1,Arquivo_bin);
        fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
        fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
        fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
        
        int num_campos;     
        scanf("%d", &num_campos);



        char **nome_campo = (char **)calloc(num_campos , sizeof(char*));
        char **valor_campo = (char **)calloc(num_campos, sizeof(char*));
        char *tmp = malloc(sizeof(char) * 100);
    
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
        long int byteoffset = 17;
        while(fread( &r.removido,sizeof(char),1,Arquivo_bin) != 0){
            //printf("AQUI1\n");
            binToRegister(Arquivo_bin, &r);
            //printf("AQUI2\n");
            if(r.removido == '1' || r.codEstacao == -1 || r.nomeEstacao == NULL){
                   // printf("AQUI2-1\n");
                    free(r.nomeEstacao);
                    //printf("AQUI2-2\n");
                    free(r.nomeLinha);
                    //printf("AQUI2-3\n");
                    byteoffset += r.tamanhoRegistro + 5;
                    continue;
                }
            //printf("AQUI3\n");   
            int correto = compara_reg(r, num_campos, nome_campo, valor_campo);
            //printf("AQUI4\n");

            if(correto == num_campos){
                    //printf("AQUI5\n");
                    //retira_cabecalho(li, pares, &h, r);
                    //printf("AQUI6\n");
                    fseek(Arquivo_bin, -r.tamanhoRegistro - 5, SEEK_CUR);
                    //printf("AQUI7\n");
                    fputc('1', Arquivo_bin);
                    fseek(Arquivo_bin, 4, SEEK_CUR);
                   // printf("AQUI8\n");
                    fwrite(&h.topoLista, sizeof(long int), 1, Arquivo_bin);
                   // printf("AQUI9\n");
                
                
                
               // printf("AQUI10\n");
                fseek(Arquivo_bin, 1, SEEK_SET);
               // printf("AQUI11\n");
                fwrite(&byteoffset, sizeof(long int), 1, Arquivo_bin);
               // printf("AQUI12\n");
                
            }
            byteoffset += r.tamanhoRegistro + 5;

            free(r.nomeEstacao);
            free(r.nomeLinha);
        }

        //atualiza_cabec(h, Arquivo_bin);

        for(int z = 0; z < num_campos; z++){
            free(nome_campo[z]);
            free(valor_campo[z]);
    }

        free(nome_campo);
        free(valor_campo);
        
    }

    Lista_estacao* li = cria_lista_estacao();
    Lista_pares *pares = cria_lista_pares();

    fseek(Arquivo_bin,0,SEEK_SET);
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
    h.nroEstacoes = 0;
    h.nroParesEstacao = 0;

    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){

        binToRegister(Arquivo_bin,&r);

        if(r.removido == '0'){
            dataInHeader(li, pares, &h, r);
        }
    }
    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    

    libera_lista(pares, li);
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin);
    free(nome_arquivo_bin);
    
}


void func_five(){
    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);
    FILE *Arquivo_bin = fopen(nome_arquivo_bin, "rb+");

    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

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


        r.removido = '0';
        r.tamanhoRegistro = 32 + strlen(r.nomeEstacao) + strlen(r.nomeLinha) + 2;
        r.proxLista = -1;
        
        //Le o cabecalho recuperando infos
        fread(&h.status,sizeof(char),1,Arquivo_bin);
        fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
        fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
        fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);

        char removido = ' ';
        int tamanhoRegistro = 0;
        
        long int antLista =  0;
        long int atLista = h.topoLista;
        long int proxLista = -1;

        //Flag para verificar se foi gravado no meio do arquivo o registro
        int gravou = 0;

        //Procura o proximo da lista ate encontrar um endereco invalido
        while(atLista != -1){
            
            //Coloca o ponteiro no bityoffset indicado no cabecalho 
            fseek(Arquivo_bin,atLista,SEEK_SET);

            //Le o inicio do registro
            fread(&removido,sizeof(char),1,Arquivo_bin);
            fread(&tamanhoRegistro,sizeof(int),1,Arquivo_bin);
            fread(&proxLista,sizeof(long int),1,Arquivo_bin);
            
            //Compara o tamanho dos registros se o registro a ser inserido for menor que um que foi excluido sera permitida a insercao
            if(tamanhoRegistro >= r.tamanhoRegistro){

                //Armazena tamanho antigo do registro
                int tam_tmp = r.tamanhoRegistro;

                //Atualiza o tamanho do registro para o mesmo de onde ele sera inserido
                r.tamanhoRegistro = tamanhoRegistro;

                //Posiciona o ponteiro do arquivo pro inicio do registro
                fseek(Arquivo_bin,atLista,SEEK_SET);

                 //Sobrescreve o registro
                insert_regInBin(&r,Arquivo_bin);
                
                //Coloca lixo no restante do registro anterior
                colocaLixo(Arquivo_bin, (tamanhoRegistro - tam_tmp));
                gravou = 1;


                //Atualiza o "Proximo Lista" ou o "Topo Lista" de acordo com a situacao
                if(antLista == 0){
                    fseek(Arquivo_bin,antLista,SEEK_SET);
                    fread(&h.status,sizeof(char),1,Arquivo_bin);
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

        if(gravou == 0){
            fseek(Arquivo_bin,0,SEEK_END);
            insert_regInBin(&r,Arquivo_bin);
        }

        fseek(Arquivo_bin,0,SEEK_SET);
        free(r.nomeEstacao);
        free(r.nomeLinha);
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

    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){

        binToRegister(Arquivo_bin,&r);

        if(r.removido == '0'){
            dataInHeader(Estacao,Pares,&h,r);
        }
    }

    h.status = '1';
    atualiza_cabec(h,Arquivo_bin);
    
    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin);
}

void colocaLixo(FILE *Arquivo_bin, int n){

    char lixo =  '$';
    //Insere Lixo nos dados restantes do registro antigo
    for(int i = 0; i < n; i++){
        fwrite(&lixo,sizeof(char),1,Arquivo_bin);
    }
}

void flushStdin(){

    char c;
    c = fgetc(stdin);
    //Limpa buffer do teclado ate chegar ao proximo limitador
    while(c != EOF && c != ' ' && c != '\n' && c != '\0'){
        c = fgetc(stdin);
    }
}


REGISTER copia_reg(REGISTER r){
    REGISTER Backup;
    Backup.codEstacao = r.codEstacao;
    Backup.codEstIntegra = r.codEstIntegra;
    Backup.codLinha = r.codLinha;
    Backup.codLinhaIntegra = r.codLinhaIntegra;
    Backup.codProxEstacao = r.codProxEstacao;
    Backup.distProxEstacao = r.distProxEstacao;
    Backup.proxLista = r.proxLista;
    Backup.removido = r.removido;
    Backup.tamanhoRegistro = r.tamanhoRegistro;
    Backup.nomeEstacao = malloc(sizeof(char) * strlen(r.nomeEstacao));
    strcpy(Backup.nomeEstacao, r.nomeEstacao);

    Backup.nomeLinha = malloc(sizeof(char) * strlen(r.nomeLinha));
    strcpy(Backup.nomeLinha, r.nomeLinha);
    return Backup;
}
void func_six(){

    char *nome_arquivo_bin;
    scanf("%ms", &nome_arquivo_bin);

    FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
    
    if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    int num_pesquisas;
    scanf("%d", &num_pesquisas);

    for(int k = 0; k < num_pesquisas; k++){
        int num_campos;
        int num_atualiza;     


        char **nome_campo = (char **)malloc(sizeof(char*)* num_campos);
        char **valor_campo = (char **)malloc(sizeof(char*)* num_campos);
        char **nome_campo_atualiza = (char **)malloc(sizeof(char*)* num_campos);
        char **valor_campo_atualiza = (char **)malloc(sizeof(char*)* num_campos);
        //Criei um ponteiro de ponteiros. Sei *char tera tamanho N por ser o numero total de registros. Os demais valores selao malocados depois
    
        char *tmp = malloc(sizeof(char) * 100);
        //Criei um char temp de tamanho fixo pra fazer um malloc mais correto no valor

        int achou = 0;
    

        scanf("%d", &num_campos);
        flushStdin();

        for(int i = 0; i < num_campos; i++){
            scanf("%ms", &nome_campo[i]);
            flushStdin();

            if(strcmp(nome_campo[i], "nomeEstacao") == 0 || strcmp(nome_campo[i], "nomeLinha") == 0){
                scan_quote_string(tmp);
                flushStdin();
                valor_campo[i] = calloc(strlen(tmp),sizeof(char) + 1);
                strcpy(valor_campo[i], tmp);
            }
            else{
                scanf("%ms", &valor_campo[i]);
                flushStdin();
            }

        //Aqui eu escaneio de uma vez todos os valores e ja os armazeno. Resolvi fazer assim pra nao ocorrer de printar logo após voce digitar o comando
        //Eu tenho que conferir se o campo vai ser uma string ou nao, pois se for, eu uso o scanquote e senão eu posso scanear normalmente e malocar

        }

        scanf("%d", &num_atualiza);
        flushStdin();
    
        for(int i = 0; i < num_atualiza; i++){
            scanf("%ms", &nome_campo_atualiza[i]);
            flushStdin();

            if(strcmp(nome_campo_atualiza[i], "nomeEstacao") == 0 || strcmp(nome_campo_atualiza[i], "nomeLinha") == 0){
                scan_quote_string(tmp);
                flushStdin();
                valor_campo_atualiza[i] = calloc(strlen(tmp),sizeof(char) + 1);
                strcpy(valor_campo_atualiza[i], tmp);
            }
            else{
                scanf("%ms", &valor_campo_atualiza[i]);
                flushStdin();
            }

            //Aqui eu escaneio de uma vez todos os valores e ja os armazeno. Resolvi fazer assim pra nao ocorrer de printar logo após voce digitar o comando
            //Eu tenho que conferir se o campo vai ser uma string ou nao, pois se for, eu uso o scanquote e senão eu posso scanear normalmente e malocar


        }

        HEADER h;
        REGISTER r;
        Lista_estacao* li = cria_lista_estacao();
        Lista_pares* pares = cria_lista_pares();
   
        fread(&h.status,sizeof(char),1,Arquivo_bin);
        fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
        fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
        fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);
        int byteoffset = 17;

        while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
            binToRegister(Arquivo_bin, &r);

            if(r.removido = '1'){
                free(r.nomeEstacao);
                free(r.nomeLinha);
                continue;
            }
    


        int correto = compara_reg(r,num_campos,nome_campo,valor_campo);
        if(correto == num_campos){
            int tam_ant = r.tamanhoRegistro;
            REGISTER BACKUP = copia_reg(r);
            //atualizaReg()
            if(tam_ant >= r.tamanhoRegistro){
                fseek(Arquivo_bin, -1*tam_ant - 5,SEEK_CUR);
                r.tamanhoRegistro = tam_ant;
                insert_regInBin(&r,Arquivo_bin);
                colocaLixo(Arquivo_bin, tam_ant - r.tamanhoRegistro);
            }else{
                fseek(Arquivo_bin, -1*tam_ant - 5,SEEK_CUR);
                fputc('1', Arquivo_bin);
                fseek(Arquivo_bin, 4, SEEK_CUR);
                fwrite(&h.topoLista, sizeof(long int), 1, Arquivo_bin);
                fseek(Arquivo_bin, 1, SEEK_SET);
                fwrite(&byteoffset, sizeof(long int), 1, Arquivo_bin);
                //5
                return;
            }
            imprime_reg(r);
            achou = 1;
        }

    
        byteoffset += 0;
        free(r.nomeEstacao);
        free(r.nomeLinha);

        }

        if(achou == 0){
            printf("Registro inexistente.\n");
        }

        free(valor_campo);
        free(nome_campo);
        free(nome_campo_atualiza);
        free(valor_campo_atualiza);
    }

    fclose(Arquivo_bin);
    binarioNaTela(nome_arquivo_bin);
    free(nome_arquivo_bin);
   
    return;
}


void atualizaReg(char **nome_campo, char **valor_campo,int num_campos, REGISTER *r){

    for(int i = 0; i < num_campos; i++){
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
            
            strcpy(r->nomeEstacao,valor_campo[i]); 
        }

        if(strcmp("nomeLinha", nome_campo[i]) == 0){
            strcpy(r->nomeLinha,valor_campo[i]); 
        }

    }

    r->tamanhoRegistro = 32 + strlen(r->nomeEstacao) + strlen(r->nomeLinha) + 2;
    return;
}