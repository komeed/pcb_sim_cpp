#include <stdio.h>

#include <dirent.h>
#include <stdlib.h>
#include "unicorn/unicorn.h"

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
    mcu_nrf52840 mcu = {0};

    unicorn_nrf52840_init(mcu);
}