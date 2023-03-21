/* JOAO AUGUSTO FERNANDES BARBOSA - 11953348
VINICIUS SANTOS CUBI PAULO - 11965693 */
#include <stdio.h>
#include <stdlib.h>
#include "funcoesFornecidas.h"
#include "define.h"
#include "./Funcoes/func.h"

//Para nao ficar bagunçado, o main apenas chama cada função referente à opcao digitada
int main(){
  //Analisa a operacao inserida e direciona para respectiva funcao
  int opc;
  scanf("%d", &opc);
 
  switch(opc){

    case 1:
      func_one();
      break;
    case 2:
      func_two();
      break;
    case 3:
      func_three();
      break;
    case 4:
      func_four();
      break;
    case 5:
      func_five();
      break;
    case 6:
      func_six();
      break;
    default:
      printf("ERRO");
      
      break;
  }
}
