#include <stdio.h>

#include <dirent.h>
#include <stdlib.h>
#include "unicorn/unicorn.h"
#include <chrono>

#include "global_vars.h"
#include "mcu/nrf52840/nrf52840.h"


int main() {
    system(
        "cd ../" NRF_CODE_DIR " && "
        "arm-none-eabi-gcc "
    "-mcpu=cortex-m4 "
    "-mthumb "
    "-mfloat-abi=hard "
    "-mfpu=fpv4-sp-d16 "
    "-O0 "
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
    bool running = 1;
    auto start = std::chrono::steady_clock::now();
    while (running) {
        if (!mcu->process_instructions()) {
            running = 0;
        }
        auto next = std::chrono::steady_clock::now();
        if (next - start >= std::chrono::seconds(1)) {
            start = next;
            printf("clock: %" PRIu64 "\n", mcu->get_clock_cycle());
        }
    }
    mcu->close_emulation();
}