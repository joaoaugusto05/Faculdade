.data #Dados na memória principal
	msg: .asciiz "Ola mundo" #Mensagem salva juntamente com o \0

.text #Instruções
li $v0, 1 #imprimir int
li $v0, 2 #imprimir foat
li $v0, 3 #imprimir double
li $v0, 4 #imprimir String/Char
li $v0, 5 #ler int
li $v0, 6 #ler float
li $v0, 7 #ler double
syscall #realiza operacao de v0. Para imprimir strings, o valor deve estar em a0