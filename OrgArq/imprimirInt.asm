.data
	idade: .word 56
.text
	li $v0, 1
	lw $a0, idade #tipo load adress mas para word
	syscall
	
	li $v0, 10
	syscall