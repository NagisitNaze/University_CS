;  Procedures Template.

; --------------------------------------------------------------------
;  Write some assembly language functions.

;  The function, shellSort(), sorts the numbers into ascending
;  order (small to large).  Uses the shell sort algorithm from
;  assignment #7 (modified to sort in ascending order).

;  The function, basicStats(), finds the minimum, median, and maximum,
;  sum, and average for a list of numbers.
;  Note, the median is determined after the list is sorted.
;   This function must call the lstSum() and lstAvergae()
;   functions to get the corresponding values.
;   The lstAvergae() function must call the lstSum() function.

;  The function, linearRegression(), computes the linear regression of
;  the two data sets.  Summation and division performed as integer.


; ********************************************************************************

section .data

; -----
;  Define constants.

TRUE        equ 1
FALSE       equ 0

; -----
;  Local variables for shellSort() function (if any).

h       dd  0
i       dd  0
j       dd  0
tmp     dd  0
dThree      dd  3

; -----
;  Local variables for basicStats() function (if any).



section .bss

; -----
;  Local variables for linearRegression() function (if any).

qSum        resq    1
dSum        resd    1


; ********************************************************************************

section .text

; --------------------------------------------------------
;  Shell sort function.

; -----
; Shell Sort

;   h = 1;
;       while ( (h*3+1) < a.length) {
;       h = 3 * h + 1;
;   }

;       while( h > 0 ) {
;           for (i = h-1; i < a.length; i++) {
;               tmp = a[i];
;               j = i;
;               for( j = i; (j >= h) && (a[j-h] > B); j -= h) {
;                   a[j] = a[j-h];
;               }
;               a[j] = tmp;
;           }
;           h = h / 3;
;       }

; -----
;  HLL Call:
;   call shellSort(list, len)

;  Arguments Passed:
;   1) list, addr - rdi
;   2) length, value - rsi

;  Returns:
;   sorted list (list passed by reference)

global  shellSort
shellSort:


;   YOUR CODE GOES HERE


    ret

; --------------------------------------------------------
;  Find basic statistical information for a list of integers:
;   minimum, median, maximum, sum, and average

;  Note, for an odd number of items, the median value is defined as
;  the middle value.  For an even number of values, it is the integer
;  average of the two middle values.

;  This function must call the lstSum() and lstAvergae() functions
;  to get the corresponding values.

;  Note, assumes the list is already sorted.

; -----
;  Call:
;   call basicStats(list, len, min, med, max, sum, ave)

;  Arguments Passed:
;   1) list, addr - rdi
;   2) length, value - rsi
;   3) minimum, addr - rdx
;   4) median, addr - rcx
;   5) maximum, addr - r8
;   6) sum, addr - r9
;   7) ave, addr - stack, rbp+16

;  Returns:
;   minimum, median, maximum, sum, and average
;   via pass-by-reference (addresses on stack)

global basicStats
basicStats:


;   YOUR CODE GOES HERE



    ret

; --------------------------------------------------------
;  Function to calculate the sum of a list.

; -----
;  Call:
;   ans = lstSum(lst, len)

;  Arguments Passed:
;   1) list, address - rdi
;   1) length, value - rsi

;  Returns:
;   sum (in eax)


global  lstSum
lstSum:


;   YOUR CODE GOES HERE



    ret

; --------------------------------------------------------
;  Function to calculate the average of a list.
;  Note, must call the lstSum() fucntion.

; -----
;  Call:
;   ans = lstAve(lst, len)

;  Arguments Passed:
;   1) list, address - rdi
;   1) length, value - rsi

;  Returns:
;   average (in eax)


global  lstAve
lstAve:


;   YOUR CODE GOES HERE


    ret

; --------------------------------------------------------
;  Function to calculate the linear regression
;  between two lists (of equal size).

; -----
;  Call:
;   linearRegression(xList, yList, len, xAve, yAve, b0, b1)

;  Arguments Passed:
;   1) xList, address - rdi
;   2) yList, address - rsi
;   3) length, value - rdx
;   4) xList average, value - rcx
;   5) yList average, value - r8
;   6) b0, address - r9
;   7) b1, address - stack, rpb+16

;  Returns:
;   b0 and b1 via reference

global linearRegression
linearRegression:


;   YOUR CODE GOES HERE


    ret

; ********************************************************************************


