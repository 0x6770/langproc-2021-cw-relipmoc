.globl	f
.ent	f

f:
.frame	$fp,64,$31
addiu $sp,$sp,-64
sw $fp,60($sp)
move $fp,$sp
li $2,2		# load 2
sw $2,0($fp)
li $2,4		# load 4
sw $2,4($fp)
lw $2,0($fp)	# load a
li $3,2		# load 2
mult $2,$3
mflo $2
sw $2,8($fp)	# store result of multiplication
li $3,4		# load 4
lw $2,8($fp)
add $2,$2,$3
sw $2,12($fp)	# store result of addition
lw $2,4($fp)	# load b
li $3,2		# load 2
mult $2,$3
mflo $2
sw $2,16($fp)	# store result of multiplication
li $3,2		# load 2
lw $2,16($fp)
sll $2,$2,$3
sw $2,20($fp)	# store result of left shift operation
lw $2,12($fp)
lw $3,20($fp)
xor $2,$2,$3
sltiu $2,$2,1
sw $2,0($fp)	# store result of logical equal or logical not equal
nop
bne $2,$0,L2
nop
lw $2,0($fp)	# load a
li $3,2		# load 2
mult $2,$3
mflo $2
sw $2,28($fp)	# store result of multiplication
lw $3,4($fp)	# load b
lw $2,28($fp)
xor $2,$2,$3
sltiu $2,$2,1
sw $2,0($fp)	# store result of logical equal or logical not equal
nop
bne $2,$0,L3
nop
L2:
li $2,1
b L4
nop
L3:
move $2,$0
L4:
sw $2,36($fp)	 #store the value of logical orlw $2,36($fp)
move $sp,$fp
lw $fp,60($sp)
addiu $sp,$sp,64
jr $31
nop

.end	f
