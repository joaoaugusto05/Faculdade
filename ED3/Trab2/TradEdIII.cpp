#include <iostream>
using namespace std;

#include "define.h"
#include "func.h"
#include "define.h"
#include "Node.hpp"



map<int, long> mapearByteOffSet(FILE* Arquivo_bin){
  REGISTER r;
  map<int, long> mapa;
  fseek(Arquivo_bin, 17, SEEK_SET);
  while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        long byteoffset = ftell(Arquivo_bin);
        binToRegister(Arquivo_bin, &r);
        if(r.removido != '1'){
          mapa.insert(pair<int, long>(r.codEstacao, byteoffset));

        }
}
  return mapa;
}


HEADER ler_cabecalho(FILE *Arquivo_bin){
  HEADER h;
  if(Arquivo_bin == NULL){
        printf("Falha no processamento do arquivo.");
        return h;
    }

    
   
    fread(&h.status,sizeof(char),1,Arquivo_bin);
    fread(&h.topoLista,sizeof(long int),1,Arquivo_bin);
    fread(&h.nroEstacoes,sizeof(int),1,Arquivo_bin);
    fread(&h.nroParesEstacao,sizeof(int),1,Arquivo_bin);

    //Le o cabecalho inicialmente e o printa a parte
    
  return h;
}

string byteToString(FILE* Arquivo_bin, map<int, long> mapa, int codEst){
  long byteoffset = ftell(Arquivo_bin);
  map<int, long>::iterator it;
  it = mapa.find(codEst);
  long pos = it->second;
  fseek(Arquivo_bin, pos , SEEK_SET);
  REGISTER r;
  binToRegister(Arquivo_bin, &r);

  fseek(Arquivo_bin, byteoffset, SEEK_SET);
  return r.nomeEstacao;
}

void func_seven(){
  
  char *nome_arquivo_bin;
  scanf("%ms", &nome_arquivo_bin);

  FILE *Arquivo_bin = fopen(nome_arquivo_bin,"rb");
  HEADER h = ler_cabecalho(Arquivo_bin);
  Grafo Graph;
  REGISTER r;


  if(h.nroEstacoes == 0){
        printf("Registro inexistente.\n");
        return;
    }


    
    
    //Criar tabela com codigo da estacao e nome da estacao
    
    map<int, long> MapaOffSet = mapearByteOffSet(Arquivo_bin);
    
   //Volta pro inicio

    fseek(Arquivo_bin, 17, SEEK_SET);
    while(fread(&r.removido,sizeof(char),1,Arquivo_bin) != 0){
        binToRegister(Arquivo_bin, &r);
        if(r.removido != '1'){

            if(Graph.find(r.nomeEstacao) == Graph.end()){ //Nao inserido



              if(r.codProxEstacao != -1){
                map<string, Node> Lista;
                string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao);
                Node novo(r);
                Lista.insert(pair<string, Node> (Prox_estacao, novo));



                if(r.codEstIntegra != -1){

                  string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);
                  Node novo(r);
                  
                  if(Prox_estacao.compare(r.nomeEstacao)){
                    Node integracao(r.codEstIntegra);
                    Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                  }

                }


                Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista));
              }
              else{
                map<string, Node> Lista;

                if(r.codEstIntegra != -1){
                  string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);


                  if(Prox_estacao.compare(r.nomeEstacao)){
                    Node integracao(r.codEstIntegra);
                    Lista.insert(pair<string, Node> (Prox_estacao, integracao));
                    //cout<< "Valores: " << r.nomeEstacao << " e " << Prox_estacao << endl;
                  }

                }
                Graph.insert(pair<string, map<string,Node>>(r.nomeEstacao, Lista));
              }
            }

            else{ //Ja foi inserido
             //Inserir dentro da lista
                if(r.codProxEstacao != -1){
                
                string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codProxEstacao);
                Node novo(r);


                if(Graph[r.nomeEstacao].find(Prox_estacao) == Graph[r.nomeEstacao].end()){
                  //A estacao ja foi inserida mas sem essa aresta
                  Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, novo));
                  if(r.codEstIntegra != -1){
                    string Prox_estacao = byteToString(Arquivo_bin, MapaOffSet, r.codEstIntegra);           
                    if(Prox_estacao.compare(r.nomeEstacao)){
                      Node integracao(r.codEstIntegra);
                      Graph[r.nomeEstacao].insert(pair<string, Node> (Prox_estacao, integracao));
                    }

                  }
                }
                else{
                  //A estacao ja foi inserida e com essa aresta
                  //Acessar vetor de linhas e adicionar essa linha

                    auto i = Graph[r.nomeEstacao].find(Prox_estacao);
                    Graph[r.nomeEstacao].find(Prox_estacao)->second.linhas.insert(pair<string, int>(r.nomeLinha, r.codProxEstacao));
                  }

                  
                
                }

                

            }
            
        }  
    }
      for(map<string, map<string,Node> >::const_iterator it = Graph.begin(); it != Graph.end(); ++it){
     
      cout << it->first;

    for(map<string,Node>::const_iterator sec = it->second.begin(); sec != it->second.end(); ++sec){

      Node n = sec->second;
      cout << " " << sec->first << " " << n.distancia;

      
      for(map<string,int>::const_iterator ter = n.linhas.begin(); ter != n.linhas.end();++ter){
          cout << " " + ter->first;
      }
      
      
    }
    cout << endl;
}

  
  
  }

  


int main(){
 
  int opc;
  cin >> opc;
  switch(opc){

    case 7:
        func_seven();
    break; 

  }
}