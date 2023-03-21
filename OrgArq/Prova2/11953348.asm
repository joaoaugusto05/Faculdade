.data
	msgEntrada: .asciiz "Adivinhe um numero entre 0.0 e 999.999 (com 3 casas antes e depois da virgula)\n"
	msgInput: .asciiz "Digite um numero: "
	msgMaior: .asciiz "O numero oculto eh MAIOR!\n"
	msgMenor: .asciiz "O numero oculto eh MENOR!\n"
	msgSucesso: .asciiz "Você acertou! Numero de tentativas: "
	nroOculto: .float 790.50 #Pode-se alterar aqui o valor do nroOculto
	precisao: .float 0.001 #Precisao de tres casas definidas no trabalho
	
	
	comparator: .float 0.000 #Preciso de usar um 0 como float pra verificar o valor absoluto da diferenca
	inversor: .float -1.000 #Se a diferenca for negativa multiplico por -1 para calcular o absoluto
.text #Pova2DeOrgArq


	li $t0, 0 #contador de vezes tentadas
	li $v0, 4
	la $a0, msgEntrada #Printo a entrada
	syscall
	
	
	li $t4, 0 #retorno da funcao pedida. 0 para erro, 1 para correto
	
	
	l.s $f1, nroOculto #jogo o nroOculto dentro do f1
	l.s $f2, precisao #jogo a precisao dentro do f2
	l.s $f4, comparator
	l.s $f5, inversor
	
	
	li $t0, 0 #contador de vezes tentadas
	
	tentativas:
		
		li $v0, 4
		la $a0, msgInput
		
		syscall #printar o digite novo numero
		jal TestaNumero #pulo linkado para o testa numero pedido no pdf
		addi $t0, $t0, 1 #Incremento o numero de tentativas
		beqz $t4, tentativas #Enquanto o retorno t4 for zero, eu repito isso
		j Fim #se a flag for 1 significa que entrou em algum dos loops que a setou como verdadeira, entao a pessoa acertou
		
	


	TestaNumero:
		li, $v0, 6
		syscall #armazenar a nova tentativa em f0
		sub.s $f3, $f1, $f0 #verifico a precisao, ou seja, subtraio um do outro jogando o resultado em f3. NroOculto - digitado
		
		
		c.eq.s $f3, $f2 #se, de primeira vez, a precisao ja for igual
		bc1f PrecisaoDiferente #Se for diferente, vou para aqui
		j Verdadeiro #Caso ja tenha acertado, pulo para essa funcao para setar o retorno
		
	
	
	PrecisaoDiferente:
	
		c.le.s $f3, $f4 #Se a precisao for negativa, usa-se o absoluto
		bc1t Negativo
		
		c.le.s $f3, $f2 #Se a precisao Nao for Negativa e for menor que a definida, significa que entrou no padrao
		bc1t Verdadeiro
				
				#Se a precisao for positiva e entrou neste if, significa que a diferença é maior que a precisao, ou seja, o numero eh "bem" menor que o procurado
		
		
		
		li $v0, 4
		la $a0, msgMaior
		syscall
		
		jr $ra
	
	
	
	Negativo:
	
		mul.s $f3, $f3, $f5 #transformo a posicao em valor positivo
		c.le.s $f3, $f2 #vejo se o valor dela em absoluto é menor ou igual a 0.001
		bc1t Verdadeiro #se for verdadeiro, pulo e dou o retorno
		
		li $v0, 4 #senao, significa que o numero digitado é "bem" maior que o procurado
		la $a0, msgMenor
		syscall
		jr $ra
		
	Verdadeiro:
		li $t4, 1 #Essa funcao seta o retorno que chamei de t4 para 1 e volta para o TestaNumero
		jr $ra
	
	Fim:
	#printo que deu sucesso, printo o numero de tentativas armazenadas em t0 e encerro
		li $v0, 4
		la $a0, msgSucesso
		syscall
		
		move $a0, $t0
		li $v0, 1
		syscall
		
		li $v0, 10
		syscall
	
	
	
