;   Name
;   Assignmnet Number
;   Section

; -----
;  Short description of program goes here...


; *****************************************************************
;  Static Data Declarations (initialized)

section .data

; -----
;  Define standard constants.

NULL            equ 0           ; end of string

TRUE            equ 1
FALSE           equ 0

EXIT_SUCCESS    equ 0           ; Successful operation
SYS_exit        equ 60          ; call code for terminate

; -----
;  Declare variables.

;   Place data declarations here...

NULL        equ 0

bVar1       db  30
bVar2       db  19
bAns1       db  0
bAns2       db  0
wVar1       dw  4813
wVar2       dw  2189
wAns1       dw  0
wAns2       dw  0
dVar1       dd  185752666
dVar2       dd  101789321
dVar3       dd  -57142
dAns1       dd  0
dAns2       dd  0
flt1        dd  -17.75
flt2        dd  7.125
tao         dd  6.28318
qVar1       dq  122169417133
myClass     db  "CS 218", NULL
edName      db  "Edward Jorgensen", NULL
myName      db  "Grant Mercer", NULL

; ----------------------------------------------
;  Uninitialized Static Data Declarations.

section .bss

;   Place data declarations for uninitialized data here...
;   (i.e., large arrays that are not initialized)


; *****************************************************************

section .text
global _start
_start:


; -----
;   YOUR CODE GOES HERE...




; *****************************************************************
;   Done, terminate program.

last:
    mov eax, SYS_exit       ; call call for exit (SYS_exit)
    mov ebx, EXIT_SUCCESS   ; return code of 0 (no error)
    syscall


