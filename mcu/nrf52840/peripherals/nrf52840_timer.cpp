//
// Created by Omeed on 9/16/26.
//

#include "nrf52840_timer.h"

void NRF52840_4CC_TIMER::init() {
	std::memset(timer_reg, 0, sizeof(timer_reg));
	std::memset(timer0_cc, 0, sizeof(timer0_cc));
}

uint64_t NRF52840_4CC_TIMER::mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) {

}
void NRF52840_4CC_TIMER::mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {

}
