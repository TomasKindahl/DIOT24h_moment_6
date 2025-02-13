.syntax unified
.cpu cortex-m4
.thumb

.global sum_array

.type sum_array, %function
sum_array:
    MOV r2, #0           @ r2 = sum = 0
    MOV r3, #5           @ r3 = array length

loop_sum_array:
    LDR r1, [r0], #4     @ Load next array element into r1, advance pointer
    ADD r2, r2, r1       @ prod += element
    SUBS r3, r3, #1      @ Decrease count
    BNE loop_sum_array   @ Repeat if count > 0

    MOV r0, r2           @ Return sum in r0
    BX lr
