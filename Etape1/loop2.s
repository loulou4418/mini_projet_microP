   1              		.file	"loop.c"
   2              		.text
   3              	.Ltext0:
   4              		.globl	main
   6              	main:
   7              	.LFB0:
   8              		.file 1 "loop.c"
   1:loop.c        **** void main (void){
   9              		.loc 1 1 17
  10              		.cfi_startproc
  11 0000 F30F1EFA 		endbr64
  12 0004 55       		pushq	%rbp
  13              		.cfi_def_cfa_offset 16
  14              		.cfi_offset 6, -16
  15 0005 4889E5   		movq	%rsp, %rbp
  16              		.cfi_def_cfa_register 6
  17              	.L2:
   2:loop.c        **** 	while (1);
  18              		.loc 1 2 8 discriminator 1
  19 0008 EBFE     		jmp	.L2
  20              		.cfi_endproc
  21              	.LFE0:
  23              	.Letext0:
 120              		.section	.note.gnu.property,"a"
 121              		.align 8
 122 0000 04000000 		.long	 1f - 0f
 123 0004 10000000 		.long	 4f - 1f
 124 0008 05000000 		.long	 5
 125              	0:
 126 000c 474E5500 		.string	 "GNU"
 127              	1:
 128              		.align 8
 129 0010 020000C0 		.long	 0xc0000002
 130 0014 04000000 		.long	 3f - 2f
 131              	2:
 132 0018 03000000 		.long	 0x3
 133              	3:
 134 001c 00000000 		.align 8
 135              	4:
