#/***************************************************************************/
#/*                                                                         */
#/* HDBENCH clone - a graphical benchmark software                          */
#/* Copyright (C) 1999 Yuuki NINOMIYA, gm@smn.enjoy.ne.jp                   */
#/*                                                                         */
#/* This program is free software; you can redistribute it and/or modify    */
#/* it under the terms of the GNU General Public License as published by    */
#/* the Free Software Foundation; either version 2, or (at your option)     */
#/* any later version.                                                      */
#/*                                                                         */
#/* This program is distributed in the hope that it will be useful,         */
#/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
#/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
#/* GNU General Public License for more details.                            */
#/*                                                                         */
#/* You should have received a copy of the GNU General Public License       */
#/* along with this program; if not, write to the                           */
#/* Free Software Foundation, Inc., 59 Temple Place - Suite 330,            */
#/* Boston, MA 02111-1307, USA.                                             */
#/*                                                                         */
#/***************************************************************************/

.text
	.align 16

# gint32 bench_integer(void);
.globl bench_integer
	.type	 bench_integer,@function
bench_integer:
	pushl %ebx
	pushl %ecx
	pushl %edx

	xorl %ebx,%ebx
	movl $128,%eax
	movl $128,b

	xorl %edx,%edx
.label1:
	movl $300,%ecx
	pushl %ebx
.label2:
        movl a,%ebx
        imull b,%ebx

        movl a,%ebx
        imull b,%ebx

        movl a,%eax
        cltd
        idivl b

        movl a,%eax
        cltd
        idivl b

        movl a,%ebx
        addl b,%ebx

        movl a,%ebx
        addl b,%ebx

        movl a,%ebx
        subl b,%ebx

        movl a,%ebx
        subl b,%ebx

	decl %ecx
	jnz .label2

	
	popl %ebx
	incl %ebx
	cmpl $1,done_flag
	jnz .label1

	movl %ebx,%eax

	popl %edx
	popl %ecx
	popl %ebx
	ret


# gint32 bench_float(void);
.globl bench_float
	.type	 bench_float,@function
bench_float:
	pushl %ebx
	pushl %ecx
	pushl %edx

	xorl %ebx,%ebx
	movl $1132462080,a
	movl $1124073472,b
.label3:
	movl $300,%ecx
.label4:
        flds a
        fmuls b
        fstps a
        flds a
        fmuls b
        fstps a
        flds a
        fdivs b
        fstps a
        flds a
        fdivs b
        fstps a
        flds a
        fsubs b
        fstps a
        flds a
        fsubs b
        fstps a
        flds a
        fadds b
        fstps a
        flds a
        fadds b
        fstps a

	decl %ecx
	jnz .label4

	incl %ebx
	cmpl $1,done_flag
	jnz .label3

	movl %ebx,%eax

	popl %edx
	popl %ecx
	popl %ebx
	ret


# gint32 bench_memory(gchar *src,gchar *dest);
.globl bench_memory
	.type	 bench_memory,@function
bench_memory:
	pushl %ebp
	movl %esp,%ebp
	pushf
	pushl %esi
	pushl %edi
	pushl %ebx
	pushl %ecx
	pushl %edx


	cld		# reset direction flag
	xorl %eax,%eax

.label5:
	movl 8(%ebp),%esi	# esi <- src
	movl 12(%ebp),%edi	# edi <- dest
	movl $64,%ecx

.label6:
	pushl %ecx
	movl $8192,%ecx	# 2MB/4/64
	rep
	movsl		# double word(4bytes)
	incl %eax
	popl %ecx

	cmp $1,done_flag
	jz .label7
	loop .label6
	jmp .label5

.label7:
	popl %edx
	popl %ecx
	popl %ebx
	popl %edi
	popl %esi
	popf
	movl %ebp,%esp
	popl %ebp
	ret


	.comm	a,4,4
	.comm	b,4,4
