.syntax unified
.cpu cortex-m4
.thumb

.global Reset_Handler
.global __StackTop

.section .isr_vector
.word __StackTop
.word Reset_Handler

.section .text
.thumb_func

Reset_Handler:
    bl main

loop:
    b loop