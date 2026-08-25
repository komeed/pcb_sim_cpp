//
// Created by Omeed on 8/18/26.
//

#include "nrf52840.h"
#include "../../elf/elf32.h"
#include "../../utils/errorhandler.h"

static void hook_code(
    uc_engine *uc,
    uint64_t address,
    uint32_t size,
    void *user_data) {
    printf("Executing 0x%08llX, size %u\n", address, size);
}

void NRF52840::nrf52840_init_mem(uc_engine *uc) {
    uc_err err;

    //init all the mandatory ram/flash stuff for chip
    err = uc_mem_map(
        uc,
        0x00000000,
        1024 * 1024,
        UC_PROT_ALL
    );
    if (err != UC_ERR_OK) {
        printf("FLASH map failed: %s\n", uc_strerror(err));
        return;
    }

    err = uc_mem_map(
        uc,
        0x20000000,
        256 * 1024,
        UC_PROT_ALL
    );
    if (err != UC_ERR_OK) {
        printf("RAM map failed: %s\n", uc_strerror(err));
        return;
    }
    //nrf52840_gpio_controller* gpio_cont = &mcu->gpio_controller;
    //initialize P0 GPIO pins using mmio map

    //so many options; we can have the gpio be controlled by peripheral or chip
    //we can also initialize peripherals manually through chip or what
    auto& list = get_peripherals();
    for (int i = 0; i < list.size(); i++) {
        printf("the peripherals are working i think!! offset: \n");
    }
}

static void nrf52840_load_data(uc_engine *uc) {
    const char *file = "../" NRF_CODE_DIR "/firmware.elf";
    FILE *elf = fopen(file, "rb");
    if (!elf) {
        fprintf(stderr, "Failed to open file %s\n", file);
        return;
    }
    Elf32_Ehdr ehdr;
    fread(&ehdr, sizeof(ehdr), 1, elf);
    printf("Program headers: %u\n", ehdr.e_phnum);
    printf("Program header offset: 0x%x\n", ehdr.e_phoff);
    printf("Program header size: %u\n", ehdr.e_phentsize);

    for (int i = 0; i < ehdr.e_phnum; i++) {

        Elf32_Phdr phdr;

        fseek(
            elf,
            ehdr.e_phoff + i * ehdr.e_phentsize,
            SEEK_SET
        );

        fread(&phdr, sizeof(phdr), 1, elf);

        if (phdr.p_type == PT_LOAD) {
            printf("LOAD:\n");
            printf("  offset: 0x%x\n", phdr.p_offset);
            printf("  vaddr:  0x%x\n", phdr.p_vaddr);
            printf("  filesz: 0x%x\n", phdr.p_filesz);
            printf("  memsz:  0x%x\n", phdr.p_memsz);
            printf("LOADING INTO UNICORN");

            fseek(elf, phdr.p_offset, SEEK_SET);
            uint8_t *buffer = (uint8_t*)malloc(phdr.p_filesz);
            size_t n = fread(buffer, 1, phdr.p_filesz, elf);
            if (n != phdr.p_filesz) {
                perror("fread");
                free(buffer);
                exit(1);
            }

            uc_mem_write(
                uc,
                phdr.p_vaddr,
                buffer,
                phdr.p_filesz);
            free(buffer);
        }
    }
}

void NRF52840::unicorn_nrf52840_init() {

    uc_engine *uc;
    if (uc_open(UC_ARCH_ARM, UC_MODE_THUMB, &uc) != UC_ERR_OK) {
        printf("Failed to initialize Unicorn\n");
        return;
    }
    nrf52840_init_mem(uc);
    nrf52840_load_data(uc);

    uint32_t vector[2];
    uc_mem_read(
        uc,
        0x00000000,
        vector,
         sizeof(vector));
    printf("Initial SP:    0x%08X\n", vector[0]);
    printf("Reset vector:  0x%08X\n", vector[1]);

    uint32_t pc = vector[1] & ~1u;

    uc_reg_write(uc, UC_ARM_REG_SP, &vector[0]);
    uc_reg_write(uc, UC_ARM_REG_PC, &pc);

    printf("Starting emulation with pc %d...\n", pc);


    uc_err err2 = uc_emu_start(
    uc,
    vector[1],
0,
0,
10000
    );

    printf("Emulation stopped: %s\n",
           uc_strerror(err2));

    uc_close(uc);
}

NRF52840::NRF52840() {
    unicorn_nrf52840_init();
}

