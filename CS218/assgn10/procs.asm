;  Support Procedures.
;  Provided Template

; -----
;  Function getParams()
;   Gets, checks, converts, and returns command line arguments.

;  Function drawCircle()
;   Plots provided function

; ---------------------------------------------------------

;   MACROS (if any) GO HERE

;  Call: senary2int <string>, <integer>
;   Arguments:
;       %1 -> <string>, string address MUST be NULL terminated
;       %2 -> <integer>, address (for result)

%macro senary2int 2
    push rcx
    push rdx
    push rsi
    push rdi
    push rax
    push r10
    push r11

    mov r10, %1  ; move addresses to safe reg
    mov r11, %2  ; move addresses to safe reg
    mov rsi, 0
    mov eax, 0
    mov ecx, 6
    %%loop:
        cmp byte[r10], NULL  ; compare character to NULL
        je  %%loopdone       ; if NULL end loop
        mov sil, byte[r10]   ; move character into registry
        cmp sil, 0x30
        jge %%isAlpha1
            mov dword[r11], -1
            jmp %%dn
        %%isAlpha1:
        cmp sil, 0x36
        jle %%isAlpha2
            mov dword[r11], -1
            jmp %%dn
        %%isAlpha2:
        sub sil, 0x30       ; convert to integer
        mul ecx             ; running sum *= 6
        add eax, esi        ; running sum += integer digit
        inc r10             ; increment rdi
        jmp %%loop
    %%loopdone:
    mov dword[r11], eax      ; move answer into integer address

    %%dn:
    
    pop r11
    pop r10
    pop rax
    pop rdi
    pop rsi
    pop rdx
    pop rcx
%endmacro

; ---------------------------------------------------------

section  .data

; -----
;  Define standard constants.

TRUE        equ 1
FALSE       equ 0

SUCCESS     equ 0           ; successful operation
NOSUCCESS   equ 1

STDIN       equ 0           ; standard input
STDOUT      equ 1           ; standard output
STDERR      equ 2           ; standard error

SYS_read    equ 0           ; code for read
SYS_write   equ 1           ; code for write
SYS_open    equ 2           ; code for file open
SYS_close   equ 3           ; code for file close
SYS_fork    equ 57          ; code for fork
SYS_exit    equ 60          ; code for terminate
SYS_creat   equ 85          ; code for file open/create
SYS_time    equ 201         ; code for get time

LF      equ 10
SPACE       equ " "
NULL        equ 0
ESC     equ 27

; -----
;  OpenGL constants

GL_COLOR_BUFFER_BIT equ 16384
GL_POINTS       equ 0
GL_POLYGON      equ 9
GL_PROJECTION       equ 5889

GLUT_RGB        equ 0
GLUT_SINGLE     equ 0

; -----
;  Define program constants.

SP_MIN      equ 1
SP_MAX      equ 1000

DC_MIN      equ 0
DC_MAX      equ 16777215

BK_MIN      equ 0
BK_MAX      equ 16777215


; -----
;  Local variables for getParams procedure.

STR_LENGTH  equ 12

ddSix       dd  6

errUsage    db  "Usage: circles -sp <senaryNumber> -dc <senaryNumber> "
            db  "-bk <senaryNumber>"
            db  LF, NULL
errBadCL    db  "Error, invalid or incomplete command line argument."
            db  LF, NULL

errSPsp     db  "Error, speed specifier incorrect."
            db  LF, NULL
errSPvalue  db  "Error, speed value must be between 1 and 4344(6)."
            db  LF, NULL

errDCsp     db  "Error, draw color specifier incorrect."
            db  LF, NULL
errDCvalue  db  "Error, draw color value must be between "
            db  "0 and 1355332143(6)."
            db  LF, NULL

errBKsp     db  "Error, background color specifier incorrect."
            db  LF, NULL
errBKvalue  db  "Error, background color value must be between "
            db  "0 and 1355332143(6)."
            db  LF, NULL

errDCBKsame db  "Error, draw color and background color can "
            db  "not be the same."
            db  LF, NULL

; -----
;  Local variables for draw circles routine.

red         dd  0           ; 0-255
green       dd  0           ; 0-255
blue        dd  0           ; 0-255

pi          dq  3.14159265358979    ; constant
fltZero     dq  0.0
fltOne      dq  1.0
fltTwo      dq  2.0

t           dq  0.0         ; loop variable
tStep       dq  0.001           ; t step
x           dq  0.0         ; current x
y           dq  0.0         ; current y
speed       dq  0.0         ; circle deformation speed
s           dq  0.0
scale       dq  10000.0         ; scale factor for speed

tmp1        dq  0.0
tmp2        dq  0.0

; ------------------------------------------------------------

section  .text

; -----
; Open GL routines.

extern glutInit, glutInitDisplayMode, glutInitWindowSize
extern glutInitWindowPosition
extern glutCreateWindow, glutMainLoop
extern glutDisplayFunc, glutIdleFunc, glutReshapeFunc, glutKeyboardFunc
extern glutSwapBuffers
extern gluPerspective
extern glClearColor, glClearDepth, glDepthFunc, glEnable, glShadeModel
extern glClear, glLoadIdentity, glMatrixMode, glViewport
extern glTranslatef, glRotatef, glBegin, glEnd, glVertex3f, glColor3f
extern glVertex2f, glVertex2i, glColor3ub, glOrtho, glFlush, glVertex2d
extern glutPostRedisplay

extern  cos, sin


; ******************************************************************
;  Generic procedure to display a string to the screen.
;  String must be NULL terminated.
;  Algorithm:
;   Count characters in string (excluding NULL)
;   Use syscall to output characters

;  Arguments:
;   1) address, string
;  Returns:
;   nothing

global  printString
printString:
    push    rbp
    mov rbp, rsp
    push    rbx
    push    rsi
    push    rdi
    push    rdx

; -----
;  Count characters in string.

    mov rbx, rdi            ; str addr
    mov rdx, 0
strCountLoop:
    cmp byte [rbx], NULL
    je  strCountDone
    inc rbx
    inc rdx
    jmp strCountLoop
strCountDone:

    cmp rdx, 0
    je  prtDone

; -----
;  Call OS to output string.

    mov rax, SYS_write          ; system code for write()
    mov rsi, rdi            ; address of characters to write
    mov rdi, STDOUT         ; file descriptor for standard in
                        ; EDX=count to write, set above
    syscall                 ; system call

; -----
;  String printed, return to calling routine.

prtDone:
    pop rdx
    pop rdi
    pop rsi
    pop rbx
    pop rbp
    ret

; ******************************************************************
;  Procedure getParams()
;   Gets radius 1, radius 2, offset position and color code
;   letter from the line argument.

;   Performs error checking, converts ASCII/Hex to integer.
;   Command line format (fixed order):
;     "-sp <senaryNumber> -dc <senaryNumber> -bk <senaryNumber>"

; -----
;  Arguments:
;   1) ARGC, double-word, value
;   2) ARGV, double-word, address
;   3) speed, double-word, address
;   4) draw color, double-word, address
;   5) background color, double-word, address

global getParams
getParams:
    push rbx
    
    cmp rdi, 1              ; if no args 
    jne noUsage
        mov rdi, errUsage   ; print usage to user
        call printString    ; call print fucntion
        mov rax, FALSE
    jmp dn            
    noUsage:
    cmp rdi, 7              ; if not correct arg count
    je compltArgs
        mov rdi, errBadCL   ; print bad argument count to user
        call printString    ; call print function
        mov rax, FALSE
    jmp dn              
    compltArgs:             ; at this point argument count checking has passed
    mov rbx, qword[rsi+8]   ; rbx = argv[1] ( speed specifier )
    cmp dword[rbx], 0x0070732D
    je noErrorSpeedSpec
        mov rdi, errSPsp    ; print bad speed specifier
        call printString    ; call print function
        mov rax, FALSE
    jmp dn
    noErrorSpeedSpec:
    mov rbx, qword[rsi+16]  ; rbx = argv[2] ( speed value )
    senary2int rbx, rdx     ; convert string to integer and store in argument address
    cmp dword[rdx], -1      ; check if conversion failed
    jne goodSpeed   
        mov rdi, errSPvalue ; print bad color value 
        call printString    ; call print function
        mov rax, FALSE
    jmp dn
    goodSpeed:
    mov rbx, qword[rsi+24]  ; rbx = argv[3] ( color specifier )
    cmp dword[rbx], 0x0063642D
    je noErrorColorSpec
        mov rdi, errDCsp    ; print bad color specifier
        call printString    ; call print function
        mov rax, FALSE
    jmp dn
    noErrorColorSpec:
    mov rbx, qword[rsi+32]  ; rbx = argv[4] ( color value )
    senary2int rbx, rcx     ; convert string to integer and store in argument address
    cmp dword[rcx], -1      ; check if conversion failed
    jne goodColor
        mov rdi, errDCvalue ; print bad color value
        call printString    ; call print function
    jmp dn 
    goodColor:
    mov rbx, qword[rsi+40]  ; rbx = argv[5] ( background color specifier )
    cmp dword[rbx], 0x006B622D
    je noErrorBkColorSpec
        mov rdi, errBKsp    ; print bad bk color specifier
        call printString    ; call print function
        mov rax, FALSE
    jmp dn
    noErrorBkColorSpec:
    mov rbx, qword[rsi+48]  ; rbx = argv[6] ( background color value )
    senary2int rbx, r8      ; convert string to integer and store in argument address
    cmp dword[r8], -1       ; check if conversion failed
    jne goodBkColor
        mov rdi, errBKvalue ; print bad bk value
        call printString    ; call print function
        mov rax, FALSE
    jmp dn
    goodBkColor:
    mov rbx, 0
    mov ebx, dword[r8]
    cmp ebx, dword[rcx]
    jne returnTrue
        mov rdi, errDCBKsame; print cant be same message
        call printString    
        mov rax, FALSE
        jmp dn
    returnTrue:
    mov rax, TRUE
    dn:

    pop rbx
    ret

; ******************************************************************
;  Draw circles function.
;  Plots the following equations:

;   for (s=0.0; s<=1.0; sStep)
;       for (t=0.0; t<(2*pi); t+=tStep)
;           x = (1-s)*cos(t+pi*s)+s*cos(2*t)
;           y = (1-s)*sin(t+pi*s)-s*sin(2*t)
;       plot

; -----
;  Global variables accessed.

common  drawSpeed   1:4         ; speed
common  drawColor   1:4         ; draw color
common  backColor   1:4         ; background color

; -----

global drawCircles
drawCircles:

; -----
;  Save registers

    push rbx
    push r10
    push r12
    push r13
    push r14
    push r15

; -----
; Prepare for drawing
    ; glClear(GL_COLOR_BUFFER_BIT);
    mov rdi, GL_COLOR_BUFFER_BIT
    call    glClear

; -----
;  set draw colors, red, green and blue.

    mov rax, 125            ; TMP
    mov dword[red], eax     ; TMP
    mov dword[green], eax   ; TMP
    mov dword[blue], eax    ; TMP

; ----
;  Set openGL drawing color.

    mov edi, dword [red]
    mov esi, dword [green]
    mov edx, dword [blue]
    call    glColor3ub          ; call glColor3ub(r,g,b)

; ----
;  Init drawing canvas.

    ; glBegin();
    mov rdi, GL_POINTS
    call    glBegin

; -----
;  Set speed based on user entered drawSpeed
;   speed = drawSpeed / 10000
    
    mov rax, 0
    mov eax, dword[drawSpeed]
    cvtsi2sd xmm0, rax
    movsd xmm1, qword[scale]
    divsd xmm0, xmm1
    movsd qword[speed], xmm0

; -----
;  Plot (x,y) based on provided equations
;   x = (1-s)*cos(t+pi*s)+s*cos(2*t)
;   y = (1-s)*sin(t+pi*s)-s*sin(2*t)

    mov r12, 0
    movsd xmm1, qword[fltOne]
    divsd xmm1, qword[s]
    cvtsd2si rax, xmm1
    mov r13, rax

    mov r14, 0
    movsd xmm0, qword[fltTwo]
    mulsd xmm0, qword[pi]
    divsd xmm0, qword[tStep]
    cvtsd2si rax, xmm0
    mov r15, rax

    movsd xmm0, qword[fltZero]
    movsd qword[s], xmm0
    outerForLoop
        cmp r12, r13
        jg endOuterForLoop
        movsd xmm0, qword[fltZero]
        movsd qword[t], xmm0
        innerForLoop:
            cmp r14, r15
            jge endInnerForLoop         ; if not end inner for loop
            
            movsd xmm0, qword[pi]       ; move pi into reg
            mulsd xmm0, qword[speed]        ; pi * s
            addsd xmm0, qword[t]        ; (pi * s) + t
            call cos                    ; cos(pi * s + t)

            movsd xmm1, qword[fltOne]   ; move 1.0 into reg
            subsd xmm1, qword[speed]        ; 1.0 - s

            mulsd xmm0, xmm1            ; (1.0 - s) * cos(t + pi * s)
            movsd qword[tmp1], xmm0     ; mov value above into tmp

            movsd xmm0, qword[t]        ; move t into reg
            mulsd xmm0, qword[fltTwo]   ; t * 2.0
            call cos                    ; cos(t * 2.0)
            mulsd xmm0, qword[speed]        ; cos(t * 2.0) * s
            addsd xmm0, qword[tmp1]     ; (1.0 - s) * cos(t + pi * s) + s * cos(t * 2.0)
            movsd qword[x], xmm0        ; set y equal to above

            movsd xmm0, qword[t]        ; move t into reg
            mulsd xmm0, qword[fltTwo]   ; t * 2.0
            call cos                    ; cos(t * 2.0)
            mulsd xmm0, qword[speed]        ; s * cos(t * 2.0)
            movsd xmm1, qword[tmp1]     ; move previous sum into reg
            subsd xmm1, xmm0            ; (1.0 - s) * cos(t + pi * s) - s * cos(t * 2.0)
            movsd qword[y], xmm1        ; set x equal to above

            movsd xmm0, qword[x]
            movsd xmm1, qword[y]
            call glVertex2d
            inc r14
        endInnerForLoop:
        inc r12
    endOuterForLoop:

; -----
;  End drawing operations and flush unwritten operations.
;  Set-up for next call.

    call    glEnd
    call    glFlush

    call    glutPostRedisplay

; -----
;  Update speed for next call.




; -----
;  Restore registers and return to main.
    pop r15
    pop r14
    pop r13
    pop r12
    pop r10
    pop rbx
    ret


; ******************************************************************


