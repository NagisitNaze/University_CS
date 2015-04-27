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


#   YOUR CODE GOES HERE



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


#   YOUR CODE GOES HERE



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


#   YOUR CODE GOES HERE



.end    askPrompt

#####################################################################


