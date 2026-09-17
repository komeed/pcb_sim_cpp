.syntax unified
.cpu cortex-m4
.thumb

.global Reset_Handler
.global __StackTop

.section .isr_vector, "a"
.align 2
.word __StackTop
.word Reset_Handler

.section .text
.thumb_func
.align 2

Reset_Handler:
    /* Explicitly initialize SP (safety for emulators) */
    ldr   r0, =__StackTop
    mov   sp, r0

    /* Copy .data section from Flash to RAM */
    ldr   r1, =_sdata
    ldr   r2, =_edata
    ldr   r3, =_sidata
copy_data_loop:
    cmp   r1, r2
    bcs   zero_bss_init
    ldr   r0, [r3], #4
    str   r0, [r1], #4
    b     copy_data_loop

zero_bss_init:
    /* Zero out .bss section in RAM */
    ldr   r1, =_sbss
    ldr   r2, =_ebss
    movs  r0, #0
zero_bss_loop:
    cmp   r1, r2
    bcs   call_main
    str   r0, [r1], #4
    b     zero_bss_loop

call_main:
    bl    main

hang:
    b     hang