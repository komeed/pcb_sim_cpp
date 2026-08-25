//
// Created by Omeed on 8/20/26.
//

#include "mcu.h"
#include "components/peripheral.h"
#include <stdlib.h>

template<typename TARGET_MCU>
void MCU<TARGET_MCU>::init_all_peripherals() {
    auto& peripherals = MCU<TARGET_MCU>::get_peripherals();
    for (int i = 0; i < peripherals.size(); i++) {
        peripherals[i]->init();
    }
}