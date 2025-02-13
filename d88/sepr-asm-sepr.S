.syntax unified
.cpu cortex-m4
.thumb

.global add_numbers
.type add_numbers, %function

add_numbers:
    ADD r0, r0, r1  // r0 = r0 + r1
    BX lr           // Return
