	.file	"test1.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	tree
	.bss
	.align	3
	.type	tree, @object
	.size	tree, 2000040
tree:
	.zero	2000040
	.globl	a
	.align	3
	.type	a, @object
	.size	a, 2000040
a:
	.zero	2000040
	.globl	n
	.section	.sbss,"aw",@nobits
	.align	2
	.type	n, @object
	.size	n, 4
n:
	.zero	4
	.text
	.align	1
	.globl	update
	.type	update, @function
update:
	addi	sp,sp,-32
	sd	s0,24(sp)
	addi	s0,sp,32
	mv	a5,a0
	mv	a4,a1
	sw	a5,-20(s0)
	mv	a5,a4
	sw	a5,-24(s0)
	j	.L2
.L3:
	lui	a5,%hi(tree)
	addi	a4,a5,%lo(tree)
	lw	a5,-20(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-24(s0)
	addw	a5,a4,a5
	sext.w	a4,a5
	lui	a5,%hi(tree)
	addi	a3,a5,%lo(tree)
	lw	a5,-20(s0)
	slli	a5,a5,2
	add	a5,a3,a5
	sw	a4,0(a5)
	lw	a5,-20(s0)
	negw	a5,a5
	sext.w	a4,a5
	lw	a5,-20(s0)
	and	a5,a4,a5
	sext.w	a5,a5
	lw	a4,-20(s0)
	addw	a5,a4,a5
	sw	a5,-20(s0)
.L2:
	lui	a5,%hi(n)
	lw	a4,%lo(n)(a5)
	lw	a5,-20(s0)
	sext.w	a5,a5
	ble	a5,a4,.L3
	nop
	nop
	ld	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	update, .-update
	.align	1
	.globl	build
	.type	build, @function
build:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-20(s0)
	j	.L5
.L6:
	lui	a5,%hi(a)
	addi	a4,a5,%lo(a)
	lw	a5,-20(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a4,0(a5)
	lw	a5,-20(s0)
	mv	a1,a4
	mv	a0,a5
	call	update
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L5:
	lui	a5,%hi(n)
	lw	a4,%lo(n)(a5)
	lw	a5,-20(s0)
	sext.w	a5,a5
	ble	a5,a4,.L6
	nop
	nop
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	build, .-build
	.align	1
	.globl	query
	.type	query, @function
query:
	addi	sp,sp,-48
	sd	s0,40(sp)
	addi	s0,sp,48
	mv	a5,a0
	sw	a5,-36(s0)
	sw	zero,-20(s0)
	j	.L8
.L9:
	lui	a5,%hi(tree)
	addi	a4,a5,%lo(tree)
	lw	a5,-36(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	lw	a5,0(a5)
	lw	a4,-20(s0)
	addw	a5,a4,a5
	sw	a5,-20(s0)
	lw	a5,-36(s0)
	addiw	a5,a5,-1
	sext.w	a4,a5
	lw	a5,-36(s0)
	and	a5,a4,a5
	sw	a5,-36(s0)
.L8:
	lw	a5,-36(s0)
	sext.w	a5,a5
	bne	a5,zero,.L9
	lw	a5,-20(s0)
	mv	a0,a5
	ld	s0,40(sp)
	addi	sp,sp,48
	jr	ra
	.size	query, .-query
	.align	1
	.globl	main
	.type	main, @function
main:
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	addi	s0,sp,32
	lui	a5,%hi(n)
	li	a4,10
	sw	a4,%lo(n)(a5)
	li	a5,1
	sw	a5,-20(s0)
	j	.L12
.L13:
	lui	a5,%hi(a)
	addi	a4,a5,%lo(a)
	lw	a5,-20(s0)
	slli	a5,a5,2
	add	a5,a4,a5
	li	a4,1
	sw	a4,0(a5)
	lw	a5,-20(s0)
	addiw	a5,a5,1
	sw	a5,-20(s0)
.L12:
	lui	a5,%hi(n)
	lw	a4,%lo(n)(a5)
	lw	a5,-20(s0)
	sext.w	a5,a5
	ble	a5,a4,.L13
	call	build
	li	a1,3
	li	a0,1
	call	update
	li	a1,4
	li	a0,2
	call	update
	li	a1,5
	li	a0,3
	call	update
	li	a1,-5
	li	a0,6
	call	update
	li	a0,10
	call	query
	mv	a5,a0
	sw	a5,-24(s0)
	li	a5,0
	mv	a0,a5
	ld	ra,24(sp)
	ld	s0,16(sp)
	addi	sp,sp,32
	jr	ra
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
