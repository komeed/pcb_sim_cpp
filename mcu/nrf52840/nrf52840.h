//
// Created by Omeed on 8/18/26.
//

#ifndef NRF52840_H
#define NRF52840_H
#include <stdio.h>
#include "../../global_vars.h"
#include "../../utils/errorhandler.h"
#include <inttypes.h>
#include "../mcu.h"

#include "peripherals/nrf52840_gpio.h"

class NRF52840 : public MCU<NRF52840> {
public:
    NRF52840();
    void unicorn_nrf52840_init();
    void nrf52840_init_mem(uc_engine *uc);
};


void mem_write_decoder(uint64_t address, uint64_t value);


#endif //NRF52840_H
