#include <stdio.h>

#include <dirent.h>
#include <stdlib.h>
#include "unicorn/unicorn.h"
#include <chrono>

#include "global_vars.h"
#include "mcu/nrf52840/nrf52840.h"
#include "thread"

#if defined(__aarch64__)
#include <arm_acle.h>
#elif defined(__x86_64__) || defined(_M_X64)
#include <immintrin.h>
#endif

static inline void cpu_relax() {
#if defined(__aarch64__) || defined(__arm__)
#if defined(__GNUC__) || defined(__clang__)
    asm volatile("yield" ::: "memory");
#else
    __yield();
#endif
#elif defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
#if defined(_MSC_VER)
    _mm_pause();
#else
    __builtin_ia32_pause();
#endif
#else
    // Fallback for RISC-V or other architectures
#if defined(__riscv)
    asm volatile("pause");
#else
    // Generic memory barrier to prevent compiler from optimizing the loop away
    asm volatile("" ::: "memory");
#endif
#endif
}

int main() {
    system(
    "cd ../" NRF_CODE_DIR " && "
    "arm-none-eabi-gcc "
    "-mcpu=cortex-m4 "
    "-mthumb "
    "-mfloat-abi=hard "
    "-mfpu=fpv4-sp-d16 "
    "-O2 "               // <-- Change -O0 to -O2
    "-g "
    "-nostartfiles "
    "-nostdlib "
    "-I. "
    "main.c "
    "startup.S "
    "-T linker.ld "
    "-o firmware.elf"
);
    NRF52840* mcu = new NRF52840();
    mcu->unicorn_nrf52840_init();
    int8_t running = 1;
    //double expected_instructions = ((double) NRF52840_CLOCK_FREQ) / NRF52840_BATCH_SIZE;
    double expected_time_per_iter = ((double) NRF52840_BATCH_SIZE) / (double) NRF52840_CLOCK_FREQ; // in seconds
    std::chrono::duration<double> time_per_iter(expected_time_per_iter);
    auto initial = std::chrono::steady_clock::now();
    auto curr = initial;
    auto next_deadline = curr + time_per_iter;
    while (running) {
        if (!mcu->process_instructions()) {
            running = 0;
        }
        while (std::chrono::steady_clock::now() < next_deadline) {
            cpu_relax();
        }
        curr = std::chrono::steady_clock::now();
        if (curr - initial >= std::chrono::seconds(1)) {
            initial = curr;
            printf("clock: %" PRIu64 "\n", mcu->get_clock_cycle());
        }
        next_deadline += time_per_iter;
    }
    mcu->close_emulation();
}