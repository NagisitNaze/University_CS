;  Provided Template

; -----
;  The provided main calls four functions.

;  1) checkParameters()
;   Get command line arguments (word, match case flag, and
;   file descriptor), performs appropriate error checking,
;   opens file, and returns the word, match case flag, and
;   the file descriptor and word.  Ifthere any errors in
;   command line arguments, display appropriate error
;   message, and return NOSUCCESS status code.

;  2) getWord()
;   Get a single word of text (which is expected to be
;   no more than MAXWORDLENGTH characters).
;   Returned word is terminated with an NULL.
;   Note, this routine performs all buffer management.

;  NOTE: The buffer management is a significant portion of
;   the assignment.  Omitting or skipping the I/O
;   buffering will significantly impact the score.

;  3) checkWord()
;       Given the new word from the file and the user specified
;       word and the current count, update the count if the 
;   words match.

;  4) displayResults()
;   Display a formatted summary of the results.


;----------------------------------------------------------------------------

section .data

; -----
;  Define standard constants.

LF      equ 10          ; line feed
NULL        equ 0           ; end of string
SPACE       equ 0x20            ; space

TRUE        equ 1
FALSE       equ 0

SUCCESS     equ 0           ; Successful operation
NOSUCCESS   equ 1           ; Unsuccessful operation

STDIN       equ 0           ; standard input
STDOUT      equ 1           ; standard output
STDERR      equ 2           ; standard error

SYS_read    equ 0           ; system call code for read
SYS_write   equ 1           ; system call code for write
SYS_open    equ 2           ; system call code for file open
SYS_close   equ 3           ; system call code for file close
SYS_fork    equ 57          ; system call code for fork
SYS_exit    equ 60          ; system call code for terminate
SYS_creat   equ 85          ; system call code for file open/create
SYS_time    equ 201         ; system call code for get time

O_CREAT     equ 0x40
O_TRUNC     equ 0x200
O_APPEND    equ 0x400

O_RDONLY    equ 000000q         ; file permission - read only
O_WRONLY    equ 000001q         ; file permission - write only
O_RDWR      equ 000002q         ; file permission - read and write

S_IRUSR     equ 00400q
S_IWUSR     equ 00200q
S_IXUSR     equ 00100q

; -----
;  Variables for getFileDescriptors()

usageMsg    db  "Usage: ./wc -w <searchWord> <-mc|-ic> -f <inputFile>"
        db  LF, NULL

errbadCLQ   db  "Error, invalid command line arguments."
        db  LF, NULL

errWordSpec db  "Error, invalid search word specifier."
        db  LF, NULL

errWordLength   db  "Error, search word length must be < 80 "
        db  "characters."
        db  LF, NULL

errFileSpec db  "Error, invalid input file specifier."
        db  LF, NULL

errCaseSpec db  "Error, invalid match case specifier."
        db  LF, NULL

errOpenIn   db  "Error, can not open input file."
        db  LF, NULL

; -----
;  Define constants and variables for getWord()

MAXWORDLENGTH   equ 80
BUFFSIZE    equ 250000
;BUFFSIZE   equ 3

bfMax       dq  BUFFSIZE
curr        dq  BUFFSIZE

wasEOF      db  FALSE

errFileRead db  "Error reading input file."
        db  LF, NULL

; -----
;  Define constants and variables for displayResults()

resultStart db  "Found '", NULL
resultSpace db  "' ", NULL
resultEnd   db  " times.", LF, NULL

; -------------------------------------------------------

section .bss

buff        resb    BUFFSIZE+1
tmpString   resb    MAXWORDLENGTH+1


; -------------------------------------------------------

section .text

; -------------------------------------------------------
;  Check and return command line parameters.
;   Assignment #11 requires a word and file name.
;   Example:    % ./wc -w <searchWord> <-mc|-ic> -f <infile>

; -----
; HLL Call:
;   bool = checkParameters(ARGC, ARGV, searchWord, matchCase, rdFileDesc)

;  Arguments passed:
;   1) argc, value
;   2) argv, address
;   3) search word string, address
;   4) match case boolean, address
;   5) input file descriptor, address


global checkParameters
checkParameters:
    push rbx

    cmp rdi, 1                  ; if no args
    jne noUsage
        mov rdi, usageMsg       ; move usage message into rdi
        call printString        ; call print function
        mov rax, FALSE          ; return false
    jmp dn
    noUsage:
    cmp rdi, 6                  ; if correct amount of args 
    je goodArgCount
        mov rdi, errbadCLQ      ; move bad arg counts into rdi
        call printString        ; call print function
        mov rax, FALSE          ; return false
    jmp dn
    goodArgCount:
    mov rbx, qword[rsi+8]       ; rbx = argv[1] ( word specifier )
    cmp word[rbx], 0x772D
    je noErrorWordSpec      
        mov rdi, errWordSpec    ; move bad word specifier into rdi
        call printString        ; call print functino
        mov rax, FALSE          ; return false
    jmp dn
    noErrorWordSpec:
    mov rbx, qword[rsi+16]      ; rbx = argv[2] ( word value )
    xor r11, r11
    xor r10, r10                ; set r10 to zero
    length:                 
        mov r11b, byte[rbx+r10]
        cmp r11b, NULL            ; end loop if NULL reached
        je endLength
        inc r10                 ; find length
        jmp length
    endLength:
    cmp r10, MAXWORDLENGTH      ; compare length to max word length
    jl goodLength
        mov rdi, errWordLength  ; move error word length into rdi
        call printString        ; call print function
        mov rax, FALSE          ; return false
    jmp dn
    goodLength:
    mov qword[rdx], rbx
    mov rbx, qword[rsi+24]      ; rbx = argv[3] ( search specifier )
    cmp dword[rbx], 0x00636D2D  ; check search specifier (mc)
    jne checkTwo
        mov dword[rcx], TRUE    ; set match case specifier to true
    jmp caseGood                ; skip next check
    checkTwo:
    cmp dword[rbx], 0x0063692D  ; check search specifier (ic)    
    je caseGood
        mov rdi, errCaseSpec    ; move match case error into rdi
        call printString        ; call print function
        mov rax, FALSE          ; return false
    jmp dn
    mov dword[rcx], FALSE       ; set match case sepcifier to false
    caseGood:
    mov rbx, qword[rsi+32]      ; rbx = argv[4] ( file specifier )
    cmp word[rbx], 0x662D
    je goodFileSpec
        mov rdi, errFileSpec    ; move error file specifier into rdi
        call printString        ; call printString
        mov rax, FALSE          ; return false
    jmp dn
    goodFileSpec:
    mov rbx, qword[rsi+40]      ; rbx = argv[5] ( file string )
    mov rax, SYS_open           ; read file
    mov rdi, rbx                ; move file name
    mov rsi, O_RDONLY           ; read only
    syscall                     ; attempt to open file
    cmp rax, 0
    jge noError
        mov rdi, errOpenIn      ; move error file open into rdi
        call printString        ; call print function
        mov rax, FALSE          ; return false
    jmp dn
    noError:
    mov qword[r8], rax          ; save descriptor
    mov rax, TRUE               ; function ran successfully
    dn:
    pop rbx
    ret

; -------------------------------------------------------
;  Get a single word of text and return.
;  Implements standard C++ (searchWord << inFile) functionality.

;  A "word" is considered a set of contiguous non-white space
;  characters.  White space includes spaces, tabs, and LF.
;  Any character <= a space character is considered white space.
;  Function terminates word string with a NULL.

;  This routine handles the I/O buffer management.
;   - if buffer is empty, get more chars from file
;   - return word and update buffer pointers

;  If a word is returned, return TRUE.
;  Otherwise, return FALSE.

; -----
; HLL Call:
;   bool = getWord(currentWord, rdFileDesc)

;  Arguments passed:
;   1) word buffer, address
;   2) file descriptor, value

global getWord
getWord:

    ret

; -------------------------------------------------------
;  Compare strings, searchWord to currWord.
;  If same, increment word count.

; -----
;  HLL Call:
;   call checkWord(searchWord, currentWord, matchCase, wordCount)

;  Argument passed:
;   1) searchWord, address
;   2) currentWord, address
;   3) match case flag, value
;   4) word count, address

global checkWord
checkWord:

    ret

; -------------------------------------------------------
;  Display formatted results to screen.
;   includes search word and count (in senary).
;   format:
;       found <searchWord> <wordCount> times.

; -----
;  HLL Call:
;   displayResults(searchWord, wordCount)

;  Arguments passed:
;   1) search word string, address
;   2) word count, value

global displayResults
displayResults:

    ret

; ******************************************************************
;  Generic procedure to display a string to the screen.
;  String must be NULL terminated.

;  Algorithm:
;   Count characters in string (excluding NULL)
;   Use syscall to output characters

; -----
;  HLL Call:
;   printString(stringAddr);

;  Arguments:
;   1) address, string
;  Returns:
;   nothing

global  printString
printString:

; -----
;  Count characters to write.

    mov rdx, 0
strCountLoop:
    cmp byte [rdi+rdx], NULL
    je  strCountLoopDone
    inc rdx
    jmp strCountLoop
strCountLoopDone:
    cmp rdx, 0
    je  printStringDone

; -----
;  Call OS to output string.

    mov rax, SYS_write          ; system code for write()
    mov rsi, rdi            ; address of characters to write
    mov rdi, STDOUT         ; file descriptor for standard in
                        ; rdx=count to write, set above
    syscall                 ; system call

; -----
;  String printed, return to calling routine.

printStringDone:
    ret

; ******************************************************************


