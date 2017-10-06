	.386p
	ifdef ??version
	if    ??version GT 500H
	.mmx
	endif
	endif
	model flat
	ifndef	??version
	?debug	macro
	endm
	endif
	?debug	S "D:\develop\SmartController\controller\source\link_driver\hal_windows\windows_driver\WindowsCommDriver.cpp"
	?debug	T "D:\develop\SmartController\controller\source\link_driver\hal_windows\windows_driver\WindowsCommDriver.cpp"
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
_DATA	segment dword public use32 'DATA'
_DATA	ends
_BSS	segment dword public use32 'BSS'
_BSS	ends
$$BSYMS	segment byte public use32 'DEBSYM'
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
$$BNAMES	ends
$$BROWSE	segment byte public use32 'DEBSYM'
$$BROWSE	ends
$$BROWFILE	segment byte public use32 'DEBSYM'
$$BROWFILE	ends
DGROUP	group	_BSS,_DATA
_DATA	segment dword public use32 'DATA'
@_$CHCC$@WinMain$qqspvt1pci	segment virtual
	align	2
@@_$CHCC$@WinMain$qqspvt1pci	label	dword
	dd	-4
	dd	4
	dd	@1
	dd	@@$xt$r18Sysutils@Exception
	dd	0
	dd	0
	dd	0
	dd	0
@_$CHCC$@WinMain$qqspvt1pci	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTDC$@WinMain$qqspvt1pci	segment virtual
	align	2
@@_$ECTDC$@WinMain$qqspvt1pci	label	dword
	dd	0
	dd	-40
	dw	0
	dw	3
	dd	@@_$CHCC$@WinMain$qqspvt1pci
	dw	0
	dw	4
@_$ECTDC$@WinMain$qqspvt1pci	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
WinMain	segment virtual
@WinMain	proc	near
?live16385@0:
	?debug L 14
	push      ebp
	mov       ebp,esp
	add       esp,-40
	push      ebx
	push      esi
	push      edi
@2:
	mov       eax,offset @@_$ECTDC$@WinMain$qqspvt1pci
	call      @__InitExceptBlockLDTC
	?debug L 16
	mov       word ptr [ebp-24],8
	?debug L 18
	mov       edx,dword ptr [@Forms@Application]
	mov       eax,dword ptr [edx]
	call      @@Forms@TApplication@Initialize$qqrv
	?debug L 19
	mov       edx,dword ptr [@Forms@Application]
	mov       eax,dword ptr [edx]
	mov       ecx,dword ptr [_Driver]
	mov       edx,dword ptr [@@TDriver@]
	call      @@Forms@TApplication@CreateForm$qqrp17System@TMetaClasspv
	?debug L 20
	mov       eax,dword ptr [@Forms@Application]
	mov       eax,dword ptr [eax]
	call      @@Forms@TApplication@Run$qqrv
	?debug L 21
	mov       word ptr [ebp-24],0
	jmp       short @3
	?debug L 24
@4:
@1:
	mov       edx,dword ptr [@Forms@Application]
	mov       eax,dword ptr [edx]
	mov       edx,dword ptr [ebp-4]
	call      @@Forms@TApplication@ShowException$qqrp18Sysutils@Exception
	?debug L 25
@5:
	mov       word ptr [ebp-24],16
	call      @@_CatchCleanup$qv
	?debug L 26
@3:
	xor       eax,eax
	mov       edx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],edx
	?debug L 27
@7:
@6:
	pop       edi
	pop       esi
	pop       ebx
	mov       esp,ebp
	pop       ebp
	ret       16
	?debug L 0
@WinMain	endp
WinMain	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	db	2
	db	0
	db	0
	db	0
	dw	54
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch1
	dd	?patch2
	dd	?patch3
	df	@WinMain
	dw	0
	dw	4096
	dw	0
	dw	1
	dw	0
	dw	0
	dw	0
	db	7
	db	87
	db	105
	db	110
	db	77
	db	97
	db	105
	db	110
	dw	18
	dw	512
	dw	8
	dw	0
	dw	1027
	dw	0
	dw	2
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	12
	dw	0
	dw	1027
	dw	0
	dw	3
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	16
	dw	0
	dw	1136
	dw	0
	dw	4
	dw	0
	dw	0
	dw	0
	dw	18
	dw	512
	dw	20
	dw	0
	dw	116
	dw	0
	dw	5
	dw	0
	dw	0
	dw	0
	dw	24
	dw	519
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch4
	df	@4
	dw	0
	dw	0
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	65535
	dw	65535
	dw	6
	dw	0
	dw	0
	dw	0
?patch4	equ	@5-@4
	dw	2
	dw	6
?patch1	equ	@7-@WinMain+9
?patch2	equ	0
?patch3	equ	@7-@WinMain
	dw	2
	dw	6
	dw	8
	dw	531
	dw	7
	dw	65484
	dw	65535
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@$xt$r18Sysutils@Exception	segment virtual
	align	2
@@$xt$r18Sysutils@Exception	label	dword
	dd	4
	dw	160
	dw	12
	dd	@@$xt$18Sysutils@Exception
	db	69
	db	120
	db	99
	db	101
	db	112
	db	116
	db	105
	db	111
	db	110
	db	32
	db	38
	db	0
@$xt$r18Sysutils@Exception	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$18Sysutils@Exception	segment virtual
	align	2
@@$xt$18Sysutils@Exception	label	byte
	dd	12
	dw	3
	dw	48
	dd	0
	dd	183
	dw	60
	dw	76
	dd	0
	dw	0
	dw	0
	dd	0
	dd	4
	dd	4
	dd	@@Sysutils@Exception@$bdtr$qqrv
	dw	3
	dw	80
	db	69
	db	120
	db	99
	db	101
	db	112
	db	116
	db	105
	db	111
	db	110
	db	0
	db	0
	db	0
	dd	@@$xt$14System@TObject
	dd	0
	dd	3
	dd	0
	dd	0
	dd	@@$xt$17System@AnsiString
	dd	4
	dd	@@$xt$17System@AnsiString
	dd	0
	dd	0
@$xt$18Sysutils@Exception	ends
_TEXT	ends
_DATA	segment dword public use32 'DATA'
@_$DCEC$@Sysutils@Exception@$bdtr$qqrv	segment virtual
	align	2
@@_$DCEC$@Sysutils@Exception@$bdtr$qqrv	label	dword
	dd	@@$xt$p18Sysutils@Exception
	dd	1029
	dd	-4
	dd	0
@_$DCEC$@Sysutils@Exception@$bdtr$qqrv	ends
_DATA	ends
_DATA	segment dword public use32 'DATA'
@_$ECTFC$@Sysutils@Exception@$bdtr$qqrv	segment virtual
	align	2
@@_$ECTFC$@Sysutils@Exception@$bdtr$qqrv	label	dword
	dd	0
	dd	-40
	dw	0
	dw	5
	dd	0
	dd	@@_$DCEC$@Sysutils@Exception@$bdtr$qqrv
@_$ECTFC$@Sysutils@Exception@$bdtr$qqrv	ends
_DATA	ends
_TEXT	segment dword public use32 'CODE'
@Sysutils@Exception@$bdtr$qqrv	segment virtual
@@Sysutils@Exception@$bdtr$qqrv	proc	near
?live16390@0:
	?debug	T "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysutils.hpp"
	?debug L 181
	push      ebp
	mov       ebp,esp
	add       esp,-44
	call      __BeforeDestruction
	mov       byte ptr [ebp-41],dl
	mov       dword ptr [ebp-4],eax
@8:
	mov       eax,offset @@_$ECTFC$@Sysutils@Exception@$bdtr$qqrv
	call      @__InitExceptBlockLDTC
	mov       dword ptr [ebp-12],3
	cmp       byte ptr [ebp-41],0
	jl        short @9
	mov       word ptr [ebp-24],8
	dec       dword ptr [ebp-12]
	mov       eax,dword ptr [ebp-4]
	add       eax,4
	mov       edx,2
	call      @@System@AnsiString@$bdtr$qqrv
	dec       dword ptr [ebp-12]
	xor       edx,edx
	mov       eax,dword ptr [ebp-4]
	call      @@System@TObject@$bdtr$qqrv
@9:
	mov       ecx,dword ptr [ebp-40]
	mov       dword ptr fs:[0],ecx
@10:
	cmp       byte ptr [ebp-41],0
	jle       short @11
	mov       eax,dword ptr [ebp-4]
	call      __ClassDestroy
	?debug L 181
@11:
	mov       esp,ebp
	pop       ebp
	ret 
	?debug L 0
@@Sysutils@Exception@$bdtr$qqrv	endp
@Sysutils@Exception@$bdtr$qqrv	ends
_TEXT	ends
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	77
	dw	517
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dw	0
	dd	?patch5
	dd	?patch6
	dd	?patch7
	df	@@Sysutils@Exception@$bdtr$qqrv
	dw	0
	dw	4098
	dw	0
	dw	7
	dw	0
	dw	0
	dw	0
	db	30
	db	64
	db	83
	db	121
	db	115
	db	117
	db	116
	db	105
	db	108
	db	115
	db	64
	db	69
	db	120
	db	99
	db	101
	db	112
	db	116
	db	105
	db	111
	db	110
	db	64
	db	36
	db	98
	db	100
	db	116
	db	114
	db	36
	db	113
	db	113
	db	114
	db	118
	dw	18
	dw	512
	dw	65532
	dw	65535
	dw	4099
	dw	0
	dw	8
	dw	0
	dw	0
	dw	0
	dw	?patch8
	dw	529
	dw	?patch9
	dd	?live16390@0-@@Sysutils@Exception@$bdtr$qqrv
	dd	?live16390@0-?live16390@0
	dw	17
?patch9	equ	1
?patch8	equ	14
?patch5	equ	@10-@@Sysutils@Exception@$bdtr$qqrv+18
?patch6	equ	0
?patch7	equ	@10-@@Sysutils@Exception@$bdtr$qqrv
	dw	2
	dw	6
	dw	4
	dw	531
	dw	0
$$BSYMS	ends
_TEXT	segment dword public use32 'CODE'
@$xt$p18Sysutils@Exception	segment virtual
	align	2
@@$xt$p18Sysutils@Exception	label	dword
	dd	4
	dw	144
	dw	12
	dd	@@$xt$18Sysutils@Exception
	db	69
	db	120
	db	99
	db	101
	db	112
	db	116
	db	105
	db	111
	db	110
	db	32
	db	42
	db	0
@$xt$p18Sysutils@Exception	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$17System@AnsiString	segment virtual
	align	2
@@$xt$17System@AnsiString	label	byte
	dd	4
	dw	3
	dw	48
	dd	-1
	dd	3
	dw	60
	dw	64
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@@System@AnsiString@$bdtr$qqrv
	dw	3
	dw	68
	db	65
	db	110
	db	115
	db	105
	db	83
	db	116
	db	114
	db	105
	db	110
	db	103
	db	0
	db	0
	dd	0
	dd	0
	dd	0
@$xt$17System@AnsiString	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
@$xt$14System@TObject	segment virtual
	align	2
@@$xt$14System@TObject	label	byte
	dd	4
	dw	3
	dw	48
	dd	0
	dd	179
	dw	56
	dw	60
	dd	0
	dw	0
	dw	0
	dd	0
	dd	1
	dd	1
	dd	@@System@TObject@$bdtr$qqrv
	dw	3
	dw	64
	db	84
	db	79
	db	98
	db	106
	db	101
	db	99
	db	116
	db	0
	dd	0
	dd	0
	dd	0
@$xt$14System@TObject	ends
_TEXT	ends
_TEXT	segment dword public use32 'CODE'
_TEXT	ends
	?debug	C FB04075F44726976657201000000
	?debug	C FB041240466F726D73404170706C69636174696F6E01000000
	?debug	C FB040940544472697665724004000000
	extrn	_Driver:dword
@@Forms@TApplication@Initialize$qqrv	equ	@Forms@TApplication@Initialize$qqrv
	extrn	@Forms@TApplication@Initialize$qqrv:near
	extrn	@Forms@Application:dword
@@Forms@TApplication@CreateForm$qqrp17System@TMetaClasspv	equ	@Forms@TApplication@CreateForm$qqrp17System@TMetaClasspv
	extrn	@Forms@TApplication@CreateForm$qqrp17System@TMetaClasspv:near
@@TDriver@	equ	@TDriver@
	extrn	@TDriver@:byte
@@Forms@TApplication@Run$qqrv	equ	@Forms@TApplication@Run$qqrv
	extrn	@Forms@TApplication@Run$qqrv:near
@@Forms@TApplication@ShowException$qqrp18Sysutils@Exception	equ	@Forms@TApplication@ShowException$qqrp18Sysutils@Exception
	extrn	@Forms@TApplication@ShowException$qqrp18Sysutils@Exception:near
@@_CatchCleanup$qv	equ	@_CatchCleanup$qv
	extrn	@_CatchCleanup$qv:near
	extrn	__Exception_list:dword
	extrn	@__InitExceptBlockLDTC:near
@@System@AnsiString@$bdtr$qqrv	equ	@System@AnsiString@$bdtr$qqrv
	extrn	@System@AnsiString@$bdtr$qqrv:near
@@System@TObject@$bdtr$qqrv	equ	@System@TObject@$bdtr$qqrv
	extrn	@System@TObject@$bdtr$qqrv:near
	extrn	__BeforeDestruction:near
	extrn	__ClassDestroy:near
	?debug	C 9F757569642E6C6962
	?debug	C 9F757569642E6C6962
	?debug	C 9F757569642E6C6962
	?debug	C 9F757569642E6C6962
	?debug	C 9F76636C6534302E6C6962
$$BSYMS	segment byte public use32 'DEBSYM'
	dw	?patch10
	dw	37
	dw	10
	dw	0
	dw	0
	dw	0
	dw	0
?patch10	equ	12
	dw	?patch11
	dw	37
	dw	11
	dw	0
	dw	0
	dw	0
	dw	0
?patch11	equ	12
	dw	?patch12
	dw	3
	dw	4101
	dw	0
	dw	12
	dw	0
	dw	0
	dw	0
	dw	2
?patch12	equ	16
	dw	?patch13
	dw	3
	dw	4101
	dw	0
	dw	13
	dw	0
	dw	0
	dw	0
	dw	3
?patch13	equ	16
	dw	?patch14
	dw	3
	dw	4101
	dw	0
	dw	14
	dw	0
	dw	0
	dw	0
	dw	4
?patch14	equ	16
	dw	?patch15
	dw	3
	dw	4101
	dw	0
	dw	15
	dw	0
	dw	0
	dw	0
	dw	5
?patch15	equ	16
	dw	?patch16
	dw	3
	dw	4101
	dw	0
	dw	16
	dw	0
	dw	0
	dw	0
	dw	6
?patch16	equ	16
	dw	?patch17
	dw	3
	dw	4101
	dw	0
	dw	17
	dw	0
	dw	0
	dw	0
	dw	7
?patch17	equ	16
	dw	?patch18
	dw	3
	dw	4101
	dw	0
	dw	18
	dw	0
	dw	0
	dw	0
	dw	8
?patch18	equ	16
	dw	?patch19
	dw	3
	dw	4101
	dw	0
	dw	19
	dw	0
	dw	0
	dw	0
	dw	9
?patch19	equ	16
	dw	?patch20
	dw	3
	dw	4101
	dw	0
	dw	20
	dw	0
	dw	0
	dw	0
	dw	11
?patch20	equ	16
	dw	?patch21
	dw	3
	dw	4101
	dw	0
	dw	21
	dw	0
	dw	0
	dw	0
	dw	12
?patch21	equ	16
	dw	?patch22
	dw	3
	dw	4101
	dw	0
	dw	22
	dw	0
	dw	0
	dw	0
	dw	13
?patch22	equ	16
	dw	?patch23
	dw	3
	dw	4101
	dw	0
	dw	23
	dw	0
	dw	0
	dw	0
	dw	17
?patch23	equ	16
	dw	?patch24
	dw	3
	dw	4102
	dw	0
	dw	24
	dw	0
	dw	0
	dw	0
	dw	16384
?patch24	equ	16
	dw	?patch25
	dw	3
	dw	4101
	dw	0
	dw	25
	dw	0
	dw	0
	dw	0
	dw	0
?patch25	equ	16
	dw	?patch26
	dw	3
	dw	4101
	dw	0
	dw	26
	dw	0
	dw	0
	dw	0
	dw	1
?patch26	equ	16
	dw	?patch27
	dw	3
	dw	4101
	dw	0
	dw	27
	dw	0
	dw	0
	dw	0
	dw	2
?patch27	equ	16
	dw	?patch28
	dw	3
	dw	4101
	dw	0
	dw	28
	dw	0
	dw	0
	dw	0
	dw	3
?patch28	equ	16
	dw	?patch29
	dw	3
	dw	4101
	dw	0
	dw	29
	dw	0
	dw	0
	dw	0
	dw	4
?patch29	equ	16
	dw	?patch30
	dw	3
	dw	4101
	dw	0
	dw	30
	dw	0
	dw	0
	dw	0
	dw	5
?patch30	equ	16
	dw	?patch31
	dw	3
	dw	4101
	dw	0
	dw	31
	dw	0
	dw	0
	dw	0
	dw	6
?patch31	equ	16
	dw	?patch32
	dw	3
	dw	4101
	dw	0
	dw	32
	dw	0
	dw	0
	dw	0
	dw	7
?patch32	equ	16
	dw	?patch33
	dw	3
	dw	4101
	dw	0
	dw	33
	dw	0
	dw	0
	dw	0
	dw	8
?patch33	equ	16
	dw	?patch34
	dw	3
	dw	4101
	dw	0
	dw	34
	dw	0
	dw	0
	dw	0
	dw	9
?patch34	equ	16
	dw	?patch35
	dw	3
	dw	4101
	dw	0
	dw	35
	dw	0
	dw	0
	dw	0
	dw	10
?patch35	equ	16
	dw	?patch36
	dw	3
	dw	4101
	dw	0
	dw	36
	dw	0
	dw	0
	dw	0
	dw	11
?patch36	equ	16
	dw	?patch37
	dw	3
	dw	4101
	dw	0
	dw	37
	dw	0
	dw	0
	dw	0
	dw	12
?patch37	equ	16
	dw	?patch38
	dw	3
	dw	4101
	dw	0
	dw	38
	dw	0
	dw	0
	dw	0
	dw	13
?patch38	equ	16
	dw	?patch39
	dw	37
	dw	39
	dw	0
	dw	0
	dw	0
	dw	0
?patch39	equ	12
	dw	?patch40
	dw	37
	dw	40
	dw	0
	dw	0
	dw	0
	dw	0
?patch40	equ	12
	dw	?patch41
	dw	37
	dw	41
	dw	0
	dw	0
	dw	0
	dw	0
?patch41	equ	12
	dw	?patch42
	dw	37
	dw	42
	dw	0
	dw	0
	dw	0
	dw	0
?patch42	equ	12
	dw	?patch43
	dw	37
	dw	43
	dw	0
	dw	0
	dw	0
	dw	0
?patch43	equ	12
	dw	?patch44
	dw	37
	dw	44
	dw	0
	dw	0
	dw	0
	dw	0
?patch44	equ	12
	dw	?patch45
	dw	37
	dw	45
	dw	0
	dw	0
	dw	0
	dw	0
?patch45	equ	12
	dw	?patch46
	dw	37
	dw	46
	dw	0
	dw	0
	dw	0
	dw	0
?patch46	equ	12
	dw	?patch47
	dw	37
	dw	47
	dw	0
	dw	0
	dw	0
	dw	0
?patch47	equ	12
	dw	?patch48
	dw	37
	dw	48
	dw	0
	dw	0
	dw	0
	dw	0
?patch48	equ	12
	dw	?patch49
	dw	37
	dw	49
	dw	0
	dw	0
	dw	0
	dw	0
?patch49	equ	12
	dw	?patch50
	dw	37
	dw	50
	dw	0
	dw	0
	dw	0
	dw	0
?patch50	equ	12
	dw	?patch51
	dw	37
	dw	51
	dw	0
	dw	0
	dw	0
	dw	0
?patch51	equ	12
	dw	?patch52
	dw	37
	dw	52
	dw	0
	dw	0
	dw	0
	dw	0
?patch52	equ	12
	dw	?patch53
	dw	37
	dw	53
	dw	0
	dw	0
	dw	0
	dw	0
?patch53	equ	12
	dw	?patch54
	dw	37
	dw	54
	dw	0
	dw	0
	dw	0
	dw	0
?patch54	equ	12
	dw	?patch55
	dw	37
	dw	55
	dw	0
	dw	0
	dw	0
	dw	0
?patch55	equ	12
	dw	?patch56
	dw	37
	dw	56
	dw	0
	dw	0
	dw	0
	dw	0
?patch56	equ	12
	dw	?patch57
	dw	37
	dw	57
	dw	0
	dw	0
	dw	0
	dw	0
?patch57	equ	12
	dw	?patch58
	dw	37
	dw	58
	dw	0
	dw	0
	dw	0
	dw	0
?patch58	equ	12
	dw	?patch59
	dw	37
	dw	59
	dw	0
	dw	0
	dw	0
	dw	0
?patch59	equ	12
	dw	?patch60
	dw	37
	dw	60
	dw	0
	dw	0
	dw	0
	dw	0
?patch60	equ	12
	dw	?patch61
	dw	37
	dw	61
	dw	0
	dw	0
	dw	0
	dw	0
?patch61	equ	12
	dw	?patch62
	dw	37
	dw	62
	dw	0
	dw	0
	dw	0
	dw	0
?patch62	equ	12
	dw	?patch63
	dw	37
	dw	63
	dw	0
	dw	0
	dw	0
	dw	0
?patch63	equ	12
	dw	?patch64
	dw	37
	dw	64
	dw	0
	dw	0
	dw	0
	dw	0
?patch64	equ	12
	dw	?patch65
	dw	37
	dw	65
	dw	0
	dw	0
	dw	0
	dw	0
?patch65	equ	12
	dw	16
	dw	4
	dw	4104
	dw	0
	dw	1
	dw	66
	dw	0
	dw	0
	dw	0
	dw	?patch66
	dw	38
	dw	309
	dw	67
	dw	0
	dw	68
	dw	0
	dw	69
	dw	0
	dw	70
	dw	0
	dw	71
	dw	0
	dw	72
	dw	0
	dw	73
	dw	0
	dw	74
	dw	0
	dw	75
	dw	0
	dw	76
	dw	0
	dw	77
	dw	0
	dw	78
	dw	0
	dw	79
	dw	0
	dw	80
	dw	0
	dw	81
	dw	0
	dw	82
	dw	0
	dw	83
	dw	0
	dw	84
	dw	0
	dw	85
	dw	0
	dw	86
	dw	0
	dw	87
	dw	0
	dw	88
	dw	0
	dw	89
	dw	0
	dw	90
	dw	0
	dw	91
	dw	0
	dw	92
	dw	0
	dw	93
	dw	0
	dw	94
	dw	0
	dw	95
	dw	0
	dw	96
	dw	0
	dw	97
	dw	0
	dw	98
	dw	0
	dw	99
	dw	0
	dw	100
	dw	0
	dw	101
	dw	0
	dw	102
	dw	0
	dw	103
	dw	0
	dw	104
	dw	0
	dw	105
	dw	0
	dw	106
	dw	0
	dw	107
	dw	0
	dw	108
	dw	0
	dw	109
	dw	0
	dw	110
	dw	0
	dw	111
	dw	0
	dw	112
	dw	0
	dw	113
	dw	0
	dw	114
	dw	0
	dw	115
	dw	0
	dw	116
	dw	0
	dw	117
	dw	0
	dw	118
	dw	0
	dw	119
	dw	0
	dw	120
	dw	0
	dw	121
	dw	0
	dw	122
	dw	0
	dw	123
	dw	0
	dw	124
	dw	0
	dw	125
	dw	0
	dw	126
	dw	0
	dw	127
	dw	0
	dw	128
	dw	0
	dw	129
	dw	0
	dw	130
	dw	0
	dw	131
	dw	0
	dw	132
	dw	0
	dw	133
	dw	0
	dw	134
	dw	0
	dw	135
	dw	0
	dw	136
	dw	0
	dw	137
	dw	0
	dw	138
	dw	0
	dw	139
	dw	0
	dw	140
	dw	0
	dw	141
	dw	0
	dw	142
	dw	0
	dw	143
	dw	0
	dw	144
	dw	0
	dw	145
	dw	0
	dw	146
	dw	0
	dw	147
	dw	0
	dw	148
	dw	0
	dw	149
	dw	0
	dw	150
	dw	0
	dw	151
	dw	0
	dw	152
	dw	0
	dw	153
	dw	0
	dw	154
	dw	0
	dw	155
	dw	0
	dw	156
	dw	0
	dw	157
	dw	0
	dw	158
	dw	0
	dw	159
	dw	0
	dw	160
	dw	0
	dw	161
	dw	0
	dw	162
	dw	0
	dw	163
	dw	0
	dw	164
	dw	0
	dw	165
	dw	0
	dw	166
	dw	0
	dw	167
	dw	0
	dw	168
	dw	0
	dw	169
	dw	0
	dw	170
	dw	0
	dw	171
	dw	0
	dw	172
	dw	0
	dw	173
	dw	0
	dw	174
	dw	0
	dw	175
	dw	0
	dw	176
	dw	0
	dw	177
	dw	0
	dw	178
	dw	0
	dw	179
	dw	0
	dw	180
	dw	0
	dw	181
	dw	0
	dw	182
	dw	0
	dw	183
	dw	0
	dw	184
	dw	0
	dw	185
	dw	0
	dw	186
	dw	0
	dw	187
	dw	0
	dw	188
	dw	0
	dw	189
	dw	0
	dw	190
	dw	0
	dw	191
	dw	0
	dw	192
	dw	0
	dw	193
	dw	0
	dw	194
	dw	0
	dw	195
	dw	0
	dw	196
	dw	0
	dw	197
	dw	0
	dw	198
	dw	0
	dw	199
	dw	0
	dw	200
	dw	0
	dw	201
	dw	0
	dw	202
	dw	0
	dw	203
	dw	0
	dw	204
	dw	0
	dw	205
	dw	0
	dw	206
	dw	0
	dw	207
	dw	0
	dw	208
	dw	0
	dw	209
	dw	0
	dw	210
	dw	0
	dw	211
	dw	0
	dw	212
	dw	0
	dw	213
	dw	0
	dw	214
	dw	0
	dw	215
	dw	0
	dw	216
	dw	0
	dw	217
	dw	0
	dw	218
	dw	0
	dw	219
	dw	0
	dw	220
	dw	0
	dw	221
	dw	0
	dw	222
	dw	0
	dw	223
	dw	0
	dw	224
	dw	0
	dw	225
	dw	0
	dw	226
	dw	0
	dw	227
	dw	0
	dw	228
	dw	0
	dw	229
	dw	0
	dw	230
	dw	0
	dw	231
	dw	0
	dw	232
	dw	0
	dw	233
	dw	0
	dw	234
	dw	0
	dw	235
	dw	0
	dw	236
	dw	0
	dw	237
	dw	0
	dw	238
	dw	0
	dw	239
	dw	0
	dw	240
	dw	0
	dw	241
	dw	0
	dw	242
	dw	0
	dw	243
	dw	0
	dw	244
	dw	0
	dw	245
	dw	0
	dw	246
	dw	0
	dw	247
	dw	0
	dw	248
	dw	0
	dw	249
	dw	0
	dw	250
	dw	0
	dw	251
	dw	0
	dw	252
	dw	0
	dw	253
	dw	0
	dw	254
	dw	0
	dw	255
	dw	0
	dw	256
	dw	0
	dw	257
	dw	0
	dw	258
	dw	0
	dw	259
	dw	0
	dw	260
	dw	0
	dw	261
	dw	0
	dw	262
	dw	0
	dw	263
	dw	0
	dw	264
	dw	0
	dw	265
	dw	0
	dw	266
	dw	0
	dw	267
	dw	0
	dw	268
	dw	0
	dw	269
	dw	0
	dw	270
	dw	0
	dw	271
	dw	0
	dw	272
	dw	0
	dw	273
	dw	0
	dw	274
	dw	0
	dw	275
	dw	0
	dw	276
	dw	0
	dw	277
	dw	0
	dw	278
	dw	0
	dw	279
	dw	0
	dw	280
	dw	0
	dw	281
	dw	0
	dw	282
	dw	0
	dw	283
	dw	0
	dw	284
	dw	0
	dw	285
	dw	0
	dw	286
	dw	0
	dw	287
	dw	0
	dw	288
	dw	0
	dw	289
	dw	0
	dw	290
	dw	0
	dw	291
	dw	0
	dw	292
	dw	0
	dw	293
	dw	0
	dw	294
	dw	0
	dw	295
	dw	0
	dw	296
	dw	0
	dw	297
	dw	0
	dw	298
	dw	0
	dw	299
	dw	0
	dw	300
	dw	0
	dw	301
	dw	0
	dw	302
	dw	0
	dw	303
	dw	0
	dw	304
	dw	0
	dw	305
	dw	0
	dw	306
	dw	0
	dw	307
	dw	0
	dw	308
	dw	0
	dw	309
	dw	0
	dw	310
	dw	0
	dw	311
	dw	0
	dw	312
	dw	0
	dw	313
	dw	0
	dw	314
	dw	0
	dw	315
	dw	0
	dw	316
	dw	0
	dw	317
	dw	0
	dw	318
	dw	0
	dw	319
	dw	0
	dw	320
	dw	0
	dw	321
	dw	0
	dw	322
	dw	0
	dw	323
	dw	0
	dw	324
	dw	0
	dw	325
	dw	0
	dw	326
	dw	0
	dw	327
	dw	0
	dw	328
	dw	0
	dw	329
	dw	0
	dw	330
	dw	0
	dw	331
	dw	0
	dw	332
	dw	0
	dw	333
	dw	0
	dw	334
	dw	0
	dw	335
	dw	0
	dw	336
	dw	0
	dw	337
	dw	0
	dw	338
	dw	0
	dw	339
	dw	0
	dw	340
	dw	0
	dw	341
	dw	0
	dw	342
	dw	0
	dw	343
	dw	0
	dw	344
	dw	0
	dw	345
	dw	0
	dw	346
	dw	0
	dw	347
	dw	0
	dw	348
	dw	0
	dw	349
	dw	0
	dw	350
	dw	0
	dw	351
	dw	0
	dw	352
	dw	0
	dw	353
	dw	0
	dw	354
	dw	0
	dw	355
	dw	0
	dw	356
	dw	0
	dw	357
	dw	0
	dw	358
	dw	0
	dw	359
	dw	0
	dw	360
	dw	0
	dw	361
	dw	0
	dw	362
	dw	0
	dw	363
	dw	0
	dw	364
	dw	0
	dw	365
	dw	0
	dw	366
	dw	0
	dw	367
	dw	0
	dw	368
	dw	0
	dw	369
	dw	0
	dw	370
	dw	0
	dw	371
	dw	0
	dw	372
	dw	0
	dw	373
	dw	0
	dw	374
	dw	0
	dw	375
	dw	0
?patch66	equ	1240
	dw	?patch67
	dw	1
	db	2
	db	1
	db	8
	db	24
	db	6
	db	66
	db	67
	db	52
	db	46
	db	48
	db	48
?patch67	equ	13
$$BSYMS	ends
$$BTYPES	segment byte public use32 'DEBTYP'
	db        2,0,0,0,14,0,8,0,116,0,0,0,7,0,4,0
	db        1,16,0,0,20,0,1,2,4,0,3,4,0,0,3,4
	db        0,0,112,4,0,0,116,0,0,0,26,0,9,0,3,0
	db        0,0,254,255,255,255,3,16,0,0,4,0,0,0,4,16
	db        0,0,0,0,0,0,8,0,2,0,10,4,254,255,255,255
	db        4,0,1,2,0,0,8,0,1,0,1,0,16,0,0,0
	db        8,0,1,0,1,0,33,0,0,0,8,0,2,0,10,0
	db        8,16,0,0,28,0,4,0,0,0,9,16,0,0,0,0
	db        0,0,0,0,0,0,0,0,0,0,0,0,9,0,0,0
	db        0,0,2,0,4,2,14,0,8,0,3,0,0,0,4,0
	db        1,0,12,16,0,0,8,0,2,0,10,4,253,255,255,255
	db        8,0,1,2,1,0,11,16,0,0,14,0,8,0,3,0
	db        0,0,4,0,3,0,14,16,0,0,16,0,1,2,3,0
	db        11,16,0,0,251,255,255,255,3,4,0,0,14,0,8,0
	db        3,0,0,0,4,0,1,0,16,16,0,0,8,0,1,2
	db        1,0,11,16,0,0,14,0,8,0,3,0,0,0,4,0
	db        2,0,18,16,0,0,12,0,1,2,2,0,11,16,0,0
	db        250,255,255,255,14,0,8,0,3,0,0,0,0,0,0,0
	db        20,16,0,0,4,0,1,2,0,0,8,0,2,0,10,2
	db        3,0,0,0,14,0,8,0,3,0,0,0,4,0,1,0
	db        23,16,0,0,8,0,1,2,1,0,3,4,0,0,14,0
	db        8,0,3,0,0,0,4,0,2,0,26,16,0,0,8,0
	db        2,0,10,4,249,255,255,255,12,0,1,2,2,0,25,16
	db        0,0,116,0,0,0,14,0,8,0,3,0,0,0,4,0
	db        2,0,29,16,0,0,8,0,2,0,10,4,248,255,255,255
	db        12,0,1,2,2,0,28,16,0,0,16,0,0,0,14,0
	db        8,0,116,0,0,0,2,0,0,0,31,16,0,0,4,0
	db        1,2,0,0
$$BTYPES	ends
$$BNAMES	segment byte public use32 'DEBNAM'
	db	7,'WinMain'
	db	1,' '
	db	1,' '
	db	1,' '
	db	1,' '
	db	9,'exception'
	db	30,'@Sysutils@Exception@$bdtr$qqrv'
	db	4,'this'
	db	7,'TDriver'
	db	3,'std'
	db	6,'System'
	db	19,'@System@varSmallint'
	db	18,'@System@varInteger'
	db	17,'@System@varSingle'
	db	17,'@System@varDouble'
	db	19,'@System@varCurrency'
	db	15,'@System@varDate'
	db	17,'@System@varOleStr'
	db	19,'@System@varDispatch'
	db	18,'@System@varBoolean'
	db	18,'@System@varVariant'
	db	18,'@System@varUnknown'
	db	15,'@System@varByte'
	db	16,'@System@varByRef'
	db	17,'@System@vtInteger'
	db	17,'@System@vtBoolean'
	db	14,'@System@vtChar'
	db	18,'@System@vtExtended'
	db	16,'@System@vtString'
	db	17,'@System@vtPointer'
	db	15,'@System@vtPChar'
	db	16,'@System@vtObject'
	db	15,'@System@vtClass'
	db	18,'@System@vtWideChar'
	db	19,'@System@vtPWideChar'
	db	20,'@System@vtAnsiString'
	db	18,'@System@vtCurrency'
	db	17,'@System@vtVariant'
	db	8,'Sysutils'
	db	7,'Sysinit'
	db	7,'Windows'
	db	8,'Messages'
	db	8,'Sysconst'
	db	7,'Classes'
	db	8,'Graphics'
	db	8,'Commctrl'
	db	7,'Imglist'
	db	8,'Actnlist'
	db	3,'Imm'
	db	5,'Menus'
	db	8,'Multimon'
	db	8,'Controls'
	db	5,'Forms'
	db	8,'Stdctrls'
	db	7,'Commdlg'
	db	7,'Dialogs'
	db	8,'Extctrls'
	db	6,'Stdvcl'
	db	7,'Activex'
	db	6,'Comobj'
	db	7,'Axctrls'
	db	7,'Databkr'
	db	6,'Oledlg'
	db	8,'Olectnrs'
	db	8,'Olectrls'
	db	7,'TDriver'
	db	8,'Olectrls'
	db	8,'Olectnrs'
	db	6,'Oledlg'
	db	7,'Databkr'
	db	7,'Axctrls'
	db	6,'Comobj'
	db	7,'Activex'
	db	6,'Stdvcl'
	db	8,'Extctrls'
	db	7,'Dialogs'
	db	7,'Commdlg'
	db	8,'Stdctrls'
	db	5,'Forms'
	db	8,'Controls'
	db	8,'Multimon'
	db	5,'Menus'
	db	3,'Imm'
	db	8,'Actnlist'
	db	7,'Imglist'
	db	8,'Commctrl'
	db	8,'Graphics'
	db	7,'Classes'
	db	8,'Sysutils'
	db	8,'Sysconst'
	db	8,'Messages'
	db	7,'Windows'
	db	7,'Sysinit'
	db	6,'System'
	db	8,'heapwalk'
	db	13,'heapchecknode'
	db	13,'heapcheckfree'
	db	12,'heapfillfree'
	db	9,'heapcheck'
	db	11,'_wgetcurdir'
	db	8,'_wgetcwd'
	db	9,'_wfnmerge'
	db	9,'_wfnsplit'
	db	11,'_wfindclose'
	db	10,'_wfindnext'
	db	11,'_wfindfirst'
	db	8,'_wmktemp'
	db	11,'wsearchpath'
	db	7,'_wrmdir'
	db	7,'_wmkdir'
	db	7,'_wchdir'
	db	5,'rmdir'
	db	6,'mktemp'
	db	5,'mkdir'
	db	7,'setdisk'
	db	10,'searchpath'
	db	6,'_rmdir'
	db	7,'_mktemp'
	db	6,'_mkdir'
	db	7,'getdisk'
	db	6,'getcwd'
	db	9,'getcurdir'
	db	7,'fnsplit'
	db	7,'fnmerge'
	db	9,'findclose'
	db	8,'findnext'
	db	9,'findfirst'
	db	5,'chdir'
	db	5,'_rotr'
	db	5,'_rotl'
	db	6,'_crotr'
	db	6,'_lrotr'
	db	6,'_lrotl'
	db	6,'_crotl'
	db	3,'abs'
	db	6,'wctomb'
	db	7,'wcstoul'
	db	8,'wcstombs'
	db	6,'wcstol'
	db	6,'wcstod'
	db	5,'ultoa'
	db	4,'time'
	db	6,'system'
	db	4,'swab'
	db	7,'strtoul'
	db	6,'strtol'
	db	6,'strtod'
	db	5,'srand'
	db	7,'realloc'
	db	4,'rand'
	db	6,'putenv'
	db	6,'perror'
	db	6,'mbtowc'
	db	8,'mbstowcs'
	db	5,'mblen'
	db	26,'@std@%max$T1%$qrxT1t1$rxT1'
	db	26,'@std@%min$T1%$qrxT1t1$rxT1'
	db	17,'@std@randomize$qv'
	db	14,'@std@random$qi'
	db	4,'ltoa'
	db	4,'gcvt'
	db	4,'fcvt'
	db	4,'ecvt'
	db	6,'malloc'
	db	4,'ldiv'
	db	4,'labs'
	db	4,'itoa'
	db	6,'getenv'
	db	4,'free'
	db	4,'exit'
	db	3,'div'
	db	6,'calloc'
	db	4,'atol'
	db	4,'atoi'
	db	4,'atof'
	db	6,'atexit'
	db	5,'abort'
	db	6,'_wtold'
	db	5,'_wtol'
	db	5,'_wtoi'
	db	5,'_wtof'
	db	8,'_wsystem'
	db	11,'_wsplitpath'
	db	11,'_wsearchstr'
	db	11,'_wsearchenv'
	db	8,'_wputenv'
	db	8,'_wperror'
	db	10,'_wmakepath'
	db	8,'_wgetenv'
	db	10,'_wfullpath'
	db	8,'_wcstold'
	db	8,'_strtold'
	db	10,'_splitpath'
	db	10,'_searchstr'
	db	10,'_searchenv'
	db	9,'_makepath'
	db	7,'_wtoi64'
	db	8,'_ui64tow'
	db	8,'_ui64toa'
	db	7,'_i64tow'
	db	7,'_i64toa'
	db	7,'_atoi64'
	db	5,'_ltow'
	db	5,'_ltoa'
	db	6,'_lrand'
	db	5,'_itow'
	db	6,'_ultow'
	db	5,'_gcvt'
	db	5,'_fcvt'
	db	9,'_fullpath'
	db	5,'_exit'
	db	6,'_atold'
	db	5,'_ecvt'
	db	7,'__errno'
	db	10,'__doserrno'
	db	5,'qsort'
	db	7,'lsearch'
	db	5,'lfind'
	db	7,'bsearch'
	db	7,'wcsxfrm'
	db	6,'wcstok'
	db	6,'wcsstr'
	db	6,'wcsspn'
	db	7,'wcsrchr'
	db	7,'wcspcpy'
	db	7,'wcspbrk'
	db	7,'wcsncpy'
	db	7,'wcsncmp'
	db	7,'wcsncat'
	db	6,'wcslen'
	db	7,'wcscspn'
	db	6,'wcscpy'
	db	7,'wcscoll'
	db	6,'wcscmp'
	db	6,'wcschr'
	db	6,'wcscat'
	db	7,'strcoll'
	db	7,'strxfrm'
	db	6,'strtok'
	db	18,'@std@strstr$qpxct1'
	db	18,'@std@strstr$qpcpxc'
	db	6,'strspn'
	db	19,'@std@strpbrk$qpxct1'
	db	19,'@std@strpbrk$qpcpxc'
	db	8,'strerror'
	db	7,'strcspn'
	db	18,'@std@strrchr$qpxci'
	db	17,'@std@strrchr$qpci'
	db	7,'strncpy'
	db	7,'strncmp'
	db	7,'strncat'
	db	6,'strlen'
	db	6,'strcpy'
	db	6,'strcmp'
	db	17,'@std@strchr$qpxci'
	db	16,'@std@strchr$qpci'
	db	6,'strcat'
	db	6,'strset'
	db	6,'stpcpy'
	db	7,'strnset'
	db	7,'_wcsupr'
	db	7,'_wcsset'
	db	7,'_wcsrev'
	db	8,'_wcspcpy'
	db	8,'_wcsnset'
	db	10,'_wcsnicoll'
	db	9,'_wcsnicmp'
	db	9,'_wcsncoll'
	db	7,'_wcslwr'
	db	9,'_wcsicoll'
	db	8,'_wcsicmp'
	db	7,'_wcsdup'
	db	10,'_strnicoll'
	db	9,'_strncoll'
	db	9,'_stricoll'
	db	9,'_strerror'
	db	9,'_lwcsxfrm'
	db	8,'_lwcsupr'
	db	11,'_lwcsnicoll'
	db	10,'_lwcsncoll'
	db	8,'_lwcslwr'
	db	10,'_lwcsicoll'
	db	9,'_lwcscoll'
	db	9,'_lstrxfrm'
	db	11,'_lstrnicoll'
	db	10,'_lstrncoll'
	db	10,'_lstricoll'
	db	9,'_lstrcoll'
	db	6,'strupr'
	db	6,'strrev'
	db	8,'strnicmp'
	db	6,'strlwr'
	db	7,'stricmp'
	db	6,'strdup'
	db	7,'_stpcpy'
	db	8,'_lstrupr'
	db	8,'_lstrlwr'
	db	10,'_ltowlower'
	db	10,'_ltowupper'
	db	8,'towupper'
	db	8,'towlower'
	db	9,'_ltoupper'
	db	7,'toupper'
	db	9,'_ltolower'
	db	7,'tolower'
	db	8,'iswascii'
	db	9,'iswxdigit'
	db	8,'iswupper'
	db	8,'iswspace'
	db	8,'iswpunct'
	db	8,'iswprint'
	db	8,'iswlower'
	db	8,'iswgraph'
	db	8,'iswdigit'
	db	8,'iswcntrl'
	db	8,'iswalpha'
	db	8,'iswalnum'
	db	7,'isascii'
	db	8,'isxdigit'
	db	7,'isupper'
	db	7,'isspace'
	db	7,'ispunct'
	db	7,'isprint'
	db	7,'islower'
	db	7,'isgraph'
	db	7,'isdigit'
	db	7,'iscntrl'
	db	7,'isalpha'
	db	7,'isalnum'
	db	6,'memset'
	db	6,'memcpy'
	db	6,'memcmp'
	db	19,'@std@memchr$qpxviui'
	db	18,'@std@memchr$qpviui'
	db	7,'memmove'
	db	7,'memicmp'
	db	7,'memccpy'
	db	8,'_wmemset'
	db	8,'_wmemcpy'
	db	21,'@std@_wmemchr$qpxviui'
	db	20,'@std@_wmemchr$qpviui'
	db	10,'__threadid'
	db	14,'@std@ptrdiff_t'
	db	11,'@std@size_t'
	db	11,'@std@wint_t'
	db	13,'@std@wctype_t'
	db	12,'@std@va_list'
	db	9,'_chartype'
	db	6,'_lower'
	db	6,'_upper'
	db	5,'_argc'
	db	5,'_argv'
	db	12,'__mb_cur_max'
	db	16,'_cmdline_escapes'
	db	8,'_environ'
	db	9,'_fileinfo'
	db	6,'_fmode'
	db	8,'_osmajor'
	db	8,'_osminor'
	db	7,'_osmode'
	db	10,'_osversion'
	db	12,'_sys_errlist'
	db	9,'_sys_nerr'
	db	9,'_wenviron'
	db	13,'@std@atexit_t'
	db	10,'@std@div_t'
	db	11,'@std@ldiv_t'
	db	6,'_TCHAR'
	db	7,'_TSCHAR'
	db	7,'_TUCHAR'
	db	7,'_TXCHAR'
	db	5,'_TINT'
	db	10,'@std@ffblk'
	db	12,'@std@_wffblk'
	db	13,'@std@heapinfo'
$$BNAMES	ends
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\OleCtrls.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\DocObj.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\dlgs.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\oledlg.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\OleDlg.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\OleCtnrs.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\databkr.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\objsafe.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\docobj.H" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\ocidl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\olectl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\ActiveX.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\ComObj.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\StdVCL.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\AxCtrls.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\stddef.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\shellapi.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\oleauto.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\ole2.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\oaidl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\msxml.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\servprov.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\oleidl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\urlmon.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\objidl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\pshpack8.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\objbase.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\alloc.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\malloc.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\tchar.h" 9921 6176
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\dir.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\cguid.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\extctrls.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\commdlg.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\CommDlg.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\StdCtrls.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\dialogs.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\forms.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\multimon.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\MultiMon.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\Menus.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\Imm.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\prsht.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\CommCtrl.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\Commctrl.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\ImgList.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\ActnList.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\controls.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\graphics.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\classes.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\SysConst.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysutils.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\messages.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\dde.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\SysInit.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\windows.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\unknwn.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysvari.h" 9921 6176
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysopen.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\search.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\stdlib.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysdyn.h" 9921 6176
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\systvar.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysset.h" 9921 6176
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\syscomp.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\syscurr.h" 9921 6176
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\systdate.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\systobj.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcnsip.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcndr.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcnterr.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcnsi.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcdcep.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpcdce.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\rpc.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\wtypes.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\wstring.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysmac.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\dstring.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysclass.H" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\basetyps.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\imm.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\mcx.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winsvc.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winnetwk.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winreg.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winver.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\wincon.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winnls.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winuser.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\pshpack1.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\wingdi.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winerror.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winbase.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\string.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\pshpack2.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\poppack.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\pshpack4.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\ctype.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\winnt.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\windef.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\stdarg.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\excpt.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\_null.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\_defs.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\_stddef.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\mem.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\windows.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\sysmac.H" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\system.hpp" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\vcl0.h" 9787 6144
	?debug	D "C:\PROGRA~1\BORLAND\CBUILD~1\INCLUDE\VCL\VCL2.H" 9787 6144
	?debug	D "D:\develop\SmartController\controller\source\link_driver\hal_windows\windows_driver\WindowsCommDriver.cpp" 12415 11864
	?debug	C FB062A633A5C50524F4752417E315C626F726C616E645C434255494C447E315C6C69625C76636C34302E2330314C7B1A005B2E7F30
	?debug	C FB050B2326457863657074696F6E
	?debug	C FB050A23457863657074696F6E
	?debug	C FB050D23544170706C69636174696F6E
	?debug	C FB050E232A544170706C69636174696F6E
	?debug	C FB050C232A544D657461436C617373
	?debug	C FB050B232A457863657074696F6E
	?debug	C FB050B23416E7369537472696E67
	?debug	C FB050823544F626A656374
	end
