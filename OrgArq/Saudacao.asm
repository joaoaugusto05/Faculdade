.data
	msg: .asciiz "Olá, qual é o seu nome? "
	saudacao: .asciiz "Bom dia, "
	nome: .space 25
.text
	li $v0, 4
	la $a0, msg
	syscall 
	
	li $v0, 8
	li $a1, 25
	la $a0, nome	
	syscall
	
	move $t2, $a0
	
	li $v0, 4
	la $a0, saudacao
	syscall 
	
	li $v0, 4
	move $a0, $t2
	syscall 