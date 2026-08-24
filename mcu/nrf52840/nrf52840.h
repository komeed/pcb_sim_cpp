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

class NRF52840 : public virtual MCU {
public:
    NRF52840();
};


void mem_write_decoder(uint64_t address, uint64_t value);
//void unicorn_nrf52840_init(mcu_nrf52840 mcu);

#endif //NRF52840_H
