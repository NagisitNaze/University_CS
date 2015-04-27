#  Nellis Parking Lot Program

###########################################################################
#  data segment

.data

# -----
#  Constants

TRUE = 1
FALSE = 0

# -----
#  Variables for main

hdr:        .ascii  "\nMIPS Assignment #5\n"
            .asciiz "Nellis Parking Lot Program\n\n"

againPrompt:    .asciiz "Try another parking lot size (y/n)? "

endMsg:     .ascii  "\nYou have reached recursive nirvana.\n"
            .asciiz "Program Terminated.\n"

# -----
#  Local variables for prtNewline function.

newLine:    .asciiz "\n"

# -----
#  Local variables for displayResult() function.

maxMsg1:    .ascii  "The maximum number of ways to park "
            .asciiz "for a parking lot size of "
maxMsg2:    .asciiz " is "
maxMsg3:    .asciiz "."

# -----
#  Local variables for readParkingLotSize() function.

MINSIZE = 1
MAXSIZE = 50

strtMsg1:   .asciiz "Enter parking lots size ("
strtMsg2:   .asciiz "-"
strtMsg3:   .asciiz "): "

errValue:   .ascii  "\nError, invalid size. "
            .asciiz "Please re-enter.\n"

# -----
#  Local variables for askPrompt() function.

ansErr:     .asciiz "Error, must answer with (y/n).\n"
ans:        .space  3


###########################################################################
#  text/code segment

.text
.globl main
.ent main
main:

# -----
#  Display program header.

    la  $a0, hdr
    li  $v0, 4
    syscall                 # print header

# -----
#  Basic steps:
#   read praking lot size
#   compute max
#   display result

tryAgain:
    jal readParkingLotSize
    move    $s0, $v0            # parking lot size

    move    $a0, $v0
    jal nellisParkingLot

    move    $a0, $s0
    move    $a1, $v0
    jal displayResult

# -----
#  See if user want to try another?

    jal prtNewline
    la  $a0, againPrompt
    jal askPrompt

    beq $v0, TRUE, tryAgain

# -----
#  Done, show message and terminate program.

gameOver:
    li  $v0, 4
    la  $a0, endMsg
    syscall

    li  $v0, 10
    syscall                 # all done...
.end main

# =========================================================================
#  Very simple function to print a new line.
#   Note, use of this routine is optional.

.globl  prtNewline
.ent    prtNewline
prtNewline:
    la  $a0, newLine
    li  $v0, 4
    syscall

    jr  $ra
.end    prtNewline

# =========================================================================
#  Prompt for, read, and check starting position.
#   must be > 0 and <= length

# -----
#    Arguments:
#   none

#    Returns:
#   $v0, parking lot size

.globl  readParkingLotSize
.ent    readParkingLotSize
readParkingLotSize:

    readAgain:
    la $a0, strtMsg1 
    li $v0, 4
    syscall

    la $a0, MINSIZE
    li $v0, 1
    syscall

    la $a0, strtMsg2
    li $v0, 4
    syscall
    
    la $a0, MAXSIZE
    li $v0, 1
    syscall
    
    la $a0, strtMsg3
    li $v0, 4
    syscall

    li $v0, 5       # call code for read int
    syscall         # read int

    bgt $v0, MINSIZE, checkDone
        la $a0, errValue
        li $v0, 4
        syscall
        b readAgain
    checkDone:
    ble $v0, MAXSIZE, _checkDone
        la $a0, errValue
        li $v0, 4
        syscall
        b readAgain
    _checkDone:

    jr $ra
.end    readParkingLotSize

# =========================================================================
#  Function to recursivly determine the maximum number of
#   ways to park in the Nellis parking lot.

# -----
#  Arguments:
#   $a0 - parking lot size

#  Returns:
#   $v0 - maximum ways

.globl  nellisParkingLot
.ent    nellisParkingLot
nellisParkingLot:

    li $v0, 10   
 
    jr $ra

.end nellisParkingLot

# =========================================================================
#  Function to display formatted final result.

# -----
#    Arguments:
#   $a0 - parking lot size
#   $a1 - maximum number of ways to park

#    Returns:
#   n/a

.globl  displayResult
.ent    displayResult
displayResult:

    subu $sp, $sp, 8
    sw $s0, ($sp)
    sw $s1, 4($sp)

    move $s0, $a0
    move $s1, $a1

    la $a0, maxMsg1 
    li $v0, 4
    syscall

    move $a0, $s0
    li $v0, 1
    syscall

    la $a0, maxMsg2
    li $v0, 4
    syscall
    
    move $a0, $s1
    li $v0, 1
    syscall 

    lw $s0, ($sp)
    lw $s1, 4($sp)
    addu $sp, $sp, 8

    jr $ra

.end    displayResult

# =========================================================================
#  Function to ask user if they want to do another start position.

#  Basic flow:
#   prompt user
#   read user answer (as character)
#       if y/Y -> return TRUE
#       if n/N -> return FALSE
#   otherwise, display error and re-prompt
#  Note, uses read string syscall.

# -----
#  Arguments:
#   $a0 - prompt string
#  Returns:
#   $v0 - TRUE/FALSE

.globl  askPrompt
.ent    askPrompt
askPrompt:

    rePrompt:
    la $a0, againPrompt
    li $v0, 4
    syscall

    la $a0, ans
    li $a1, 3
    li $v0, 8
    syscall

    lb $t0, ($a0)
    li $t1, 0x79

    beq $t0, $t1, isYes
    li $t1, 0x59
    beq $t0, $t1, isYes
    li $t1, 0x6E
    beq $t0, $t1, isNo
    li $t1, 0x4E
    beq $t0, $t1, isNo
        
    la $a0, ansErr
    li $v0, 4   
    syscall
    b rePrompt
        
    isNo:
        la $v0, FALSE
        b dn
    isYes:
        la $v0, TRUE
        b dn
    dn:
    jr $ra

.end    askPrompt

#####################################################################


