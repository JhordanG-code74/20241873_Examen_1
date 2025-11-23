	.arch armv7-a
	.text
	.global main
	.syntax unified
	.fpu vfpv3
	.eabi_attribute 28, 1

main:
	push {lr}
	sub sp, sp, #64

	bl time
	bl srand

	mov r4, #0
	ldr r5, =array

fill_loop:
	bl rand
	mov r1, #100
	bl __aeabi_idivmod
	add r0, r1, #1
	str r0, [r5, r4, lsl #2]

	add r4, r4, #1
	cmp r4, #15
	bne fill_loop

	ldr r0, =msg_header
	bl printf

	mov r4, #0
print_loop:
	ldr r1, [r5, r4, lsl #2]
	ldr r0, =msg_num
	bl printf

	add r4, r4, #1
	cmp r4, #15
	bne print_loop

	mov r4, #0
class_loop:
	ldr r6, [r5, r4, lsl #2]
	mov r7, #1
	mov r8, #0

div_loop:
	cmp r7, r6
	bge classify
	mov r0, r6
	mov r1, r7
	bl __aeabi_idivmod
	cmp r1, #0
	bne skip_add
	add r8, r8, r7

skip_add:
	add r7, r7, #1
	b div_loop

classify:
	cmp r8, r6
	beq perfect

	cmp r8, r6
	bgt abundant

deficient:
	ldr r0, =msg_def
	b print_class

perfect:
	ldr r0, =msg_per
	b print_class

abundant:
	ldr r0, =msg_abd

print_class:
	mov r1, r6
	bl printf

	add r4, r4, #1
	cmp r4, #15
	bne class_loop

	mov r0, #0
	add sp, sp, #64
	pop {pc}

.data
array:
	.space 60

msg_header:
	.asciz "El arreglo es:\n"

msg_num:
	.asciz "%d "

msg_def:
	.asciz "%d - Deficiente\n"

msg_per:
	.asciz "%d - Perfecto\n"

msg_abd:
	.asciz "%d - Abundante\n"
