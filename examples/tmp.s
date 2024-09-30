.text
.globl main
main:
	pushq %rbp
	movq %rsp, %rbp
	pushq %rbx
	pushq %r12
	movl $1024, %edi
	callq initstack
	movq %rax, %rbx
	callq getchar
	movq %rbx, %rdi
	movl %eax, %esi
	movq %rdi, %rbx
	callq push
	movq %rbx, %rdi
	movq %rdi, %rbx
.Lbb2:
	movq %rbx, %rdi
	callq pop
	movl %eax, %r12d
	movl %r12d, %edi
	callq putchar
	addl $1, %r12d
	movl %r12d, %esi
	movq %rbx, %rdi
	callq push
	movl %r12d, %eax
	subl $91, %eax
	jnz .Lbb2
	movq %rbx, %rdi
	movl $10, %esi
	movq %rdi, %rbx
	callq push
	movq %rbx, %rdi
	callq pop
	movl %eax, %edi
	callq putchar
	movl $0, %eax
	popq %r12
	popq %rbx
	leave
	ret
.type main, @function
.size main, .-main
/* end function main */

.section .note.GNU-stack,"",@progbits
