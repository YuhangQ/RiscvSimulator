	.file	"test1.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	1
	.globl	rev
	.type	rev, @function
rev:
	lui	a5,%hi(n)
	lw	a1,%lo(n)(a5)
	bgt	a0,a1,.L1
	lui	a2,%hi(s)
	addi	a2,a2,%lo(s)
.L3:
	slli	a5,a0,2
	add	a5,a2,a5
	lw	a3,0(a5)
	negw	a4,a0
	and	a4,a0,a4
	xori	a3,a3,1
	sw	a3,0(a5)
	addw	a0,a4,a0
	ble	a0,a1,.L3
.L1:
	ret
	.size	rev, .-rev
	.align	1
	.globl	sub
	.type	sub, @function
sub:
	mv	a5,a0
	li	a0,0
	beq	a5,zero,.L9
	lui	a2,%hi(s)
	addi	a2,a2,%lo(s)
.L8:
	slli	a4,a5,2
	add	a4,a2,a4
	lw	a4,0(a4)
	addiw	a3,a5,-1
	and	a5,a3,a5
	xor	a0,a0,a4
	bne	a5,zero,.L8
	ret
.L9:
	ret
	.size	sub, .-sub
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"%d%d"
	.align	3
.LC1:
	.string	"%d"
	.align	3
.LC2:
	.string	"%d\n"
	.section	.text.startup,"ax",@progbits
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-80
	sd	s0,64(sp)
	sd	s1,56(sp)
	lui	s0,%hi(m)
	sd	s4,32(sp)
	lui	s1,%hi(.LC0)
	lui	s4,%hi(n)
	addi	a2,s0,%lo(m)
	addi	a1,s4,%lo(n)
	addi	a0,s1,%lo(.LC0)
	sd	ra,72(sp)
	sd	s2,48(sp)
	sd	s3,40(sp)
	sd	s5,24(sp)
	sd	s6,16(sp)
	call	scanf
	lw	a5,%lo(m)(s0)
	addiw	a4,a5,-1
	sw	a4,%lo(m)(s0)
	beq	a5,zero,.L12
	lui	s6,%hi(s)
	li	s2,1
	lui	s3,%hi(.LC2)
	addi	s6,s6,%lo(s)
	lui	s5,%hi(.LC1)
.L21:
	addi	a2,sp,8
	addi	a1,sp,4
	addi	a0,s1,%lo(.LC0)
	call	scanf
	lw	a5,4(sp)
	beq	a5,s2,.L33
	lw	a5,8(sp)
	li	a1,0
	beq	a5,zero,.L19
.L20:
	slli	a4,a5,2
	add	a4,s6,a4
	lw	a4,0(a4)
	addiw	a3,a5,-1
	and	a5,a3,a5
	xor	a1,a1,a4
	bne	a5,zero,.L20
.L19:
	addi	a0,s3,%lo(.LC2)
	call	printf
.L17:
	lw	a5,%lo(m)(s0)
	addiw	a4,a5,-1
	sw	a4,%lo(m)(s0)
	bne	a5,zero,.L21
.L12:
	ld	ra,72(sp)
	ld	s0,64(sp)
	ld	s1,56(sp)
	ld	s2,48(sp)
	ld	s3,40(sp)
	ld	s4,32(sp)
	ld	s5,24(sp)
	ld	s6,16(sp)
	li	a0,0
	addi	sp,sp,80
	jr	ra
.L33:
	addi	a1,sp,12
	addi	a0,s5,%lo(.LC1)
	call	scanf
	lw	a5,8(sp)
	lw	a1,%lo(n)(s4)
	bgt	a5,a1,.L14
.L15:
	slli	a4,a5,2
	add	a4,s6,a4
	lw	a2,0(a4)
	negw	a3,a5
	and	a3,a5,a3
	xori	a2,a2,1
	sw	a2,0(a4)
	addw	a5,a3,a5
	ble	a5,a1,.L15
.L14:
	lw	a5,12(sp)
	addiw	a5,a5,1
	bgt	a5,a1,.L17
.L16:
	slli	a4,a5,2
	add	a4,s6,a4
	lw	a2,0(a4)
	negw	a3,a5
	and	a3,a5,a3
	xori	a2,a2,1
	sw	a2,0(a4)
	addw	a5,a3,a5
	ble	a5,a1,.L16
	j	.L17
	.size	main, .-main
	.globl	m
	.globl	n
	.globl	s
	.bss
	.align	3
	.type	s, @object
	.size	s, 4092
s:
	.zero	4092
	.section	.sbss,"aw",@nobits
	.align	2
	.type	m, @object
	.size	m, 4
m:
	.zero	4
	.type	n, @object
	.size	n, 4
n:
	.zero	4
	.ident	"GCC: (GNU) 10.2.0"
