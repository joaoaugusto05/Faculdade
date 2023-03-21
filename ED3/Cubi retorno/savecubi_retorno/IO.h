#ifndef _IO_H_
#define _IO_H_
#include "define.h"

void func_one();
void func_two();
void func_three();
void func_four();
void func_five();
void func_six();
void insert_DataInReg(char *mensagem, REGISTER* target);
char *strParser(char *str, char limitador, int pos);
void colocaLixo(FILE *Arquivo_bin, int n);
void flushStdin();
void atualizaReg(char **nome_campo, char **valor_campo, int num_campos, REGISTER *r);
#endif