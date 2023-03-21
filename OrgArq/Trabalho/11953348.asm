#Trabalho de OrgArq: Joao Augusto Fernandes Barbosa 11953348
#Emanuel Lace Aranha 11234224 

.data
	endereco: .asciiz "/home/joao/Desktop/Faculdade/OrgArq/Trabalho/imagem.pgm"
	
	enderecoEsc: .asciiz "/home/joao/Desktop/Faculdade/OrgArq/Trabalho/imgproc.pgm"
	
	imagem_final: .space 10038
	
	tabela:
		.space 2048

	valores:
		.space 8192
		
	quebraLin: 
	 	"\n"
	AbrePar: 
	 	"("
	DoisP: 
	 	":"
	FechaPar: 
	 	")"
	black: .byte 0
	white: .byte 255
	TrashHold: .asciiz "Qual o valor desejado do TrashHold? "

.text		
	
	li $v0, 13 #abrir arquivo
	la $a0, endereco #carregar endereco
	li $a1, 0 #modo leitura
	li $a2, 0 #modo leitura
	syscall 
	
	move $s0, $v0 #salvar descritor em s0
	
	
	move $a0, $s0 #mover o descritor para o a0
	
	
	li $v0, 14 #read from file
	la $a1, imagem_final
	li $a2, 10038		#Le o arquivo todo de uma vez! Coloca ele na RAM
	syscall
	
	#A imagem esta na memoria entao posso fechar o arq
	move $a0, $s0
	li $v0, 16
	syscall
	
	
	li $t1, 0
	li $t2, 10038
	la $s0, imagem_final
	
	addi $s0, $s0, 38 #Começar apenas dps do cabeçaho 


	montarTab:
		la $s1, valores
					
		lbu $t3, 0($s0)	#acessa o byte da imagem
		add $s1, $s1, $t3 #Vai para o vetor do valor lido
		
		lb $t4, 0($s1) #le qual valor estava no vetor
		addi $t4, $t4, 1 #adiciona um
		sb $t4, 0($s1) #stora o novo valor
		
		
		addi $t1, $t1, 1 #soma os contadores
		addi $s0, $s0, 1


		bne $t1, $t2, montarTab
		
		
		
		
		li $t1, 0
		li $t2, 257
		la $s1, valores
		
	printValores:
	
		li $v0, 4
		la $a0, AbrePar #Print parenteses
		syscall
		
		move $a0, $t1
		li $v0, 1 #printa qual a posicao
		syscall
		
		li $v0, 4
		la $a0, DoisP #Printa dois pontos
		syscall
		
		lb $t4, 0($s1)
		move $a0, $t4 #print do num de repeticoes
		li $v0, 1
		syscall
		
		
		addi $s1, $s1, 1
		addi $t1, $t1, 1 #soma um nos contadores
		
		
		li $v0, 4
		la $a0, FechaPar #printa fechar parenteses
		syscall
		
		li $v0, 4
		la $a0, quebraLin #printa nova linha
		syscall
		bne $t1, $t2, printValores #se nao tiver acabado volta pro inicio 
		
	
	
	
	
	li $v0, 4
	la $a0, TrashHold #printa fechar parenteses
	syscall
	
	li $v0, 5
	syscall
	move $t3, $v0 #threshold em t3
	
	
	li $v0, 13 #abrir arquivo
	la $a0, enderecoEsc #carregar endereco
	li $a1, 1 #modo escrita
	li $a2, 1 #modo escrita
	syscall 
	
	move $s0, $v0 #salva descritor
	li $v0, 15 
	move $a0, $s0
	
	la $a1, imagem_final #pega a imagem
	li $a2, 38 #escreve o cabecalho
	syscall

	
	la $s0, imagem_final
	li $t0, 0
	li $t1, 10001 #numero de pixels q serao lidos
	addi $s0, $s0, 38 #pular o cabeçalho, novamente
	
	novaImg:
		beq $t0, $t1, fim #se tiver chego ao ultimo pixel, acaba
		lbu $t2, 0($s0)	#acessa o byte da imagem
		blt $t2, $t3, menor
		
		li $v0, 15 #se entrar nesse loop, ele é maior ou igual
		la $a1, white #se for maior pega o branco
		li $a2, 1 #escreve o cabecalho
		syscall
		
		addi $s0, $s0, 1 #passamos ao proximo byte
		addi $t0, $t0, 1 #somamos um no contador
		j novaImg #voltamos ao loop
		
	
	menor:
		li $v0, 15 
		la $a1, black #Por ser menor, escrevemos o preto
		li $a2, 1 #escreve o byte
		syscall
		
		addi $s0, $s0, 1 #passamos ao proximo
		addi $t0, $t0, 1 #mais um no contador
		j novaImg #voltamos ao inicio

	
	
	
	fim:
		move $a0, $s0
		li $v0, 16
		syscall
		
		li $v0, 10
		syscall
		
	
		



	
