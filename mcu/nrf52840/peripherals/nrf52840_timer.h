//
// Created by Omeed on 9/16/26.
//

#ifndef NRF52840_TIMER_H
#define NRF52840_TIMER_H

#include "components/peripheral.h"
#include "mcu/nrf52840/nrf52840_registers.h"

//stores all 4cc timers (0 1 and 2)
class NRF52840_4CC_TIMER
	: public virtual Peripheral<NRF52840_4CC_TIMER_BASE, NRF52840_4CC_TIMER_PAGE_SIZE> {
private:
	//actual timer registers
	uint32_t timer_reg[3];
	//cc registers per timer
	uint32_t timer0_cc[3][4];
public:
	NRF52840_4CC_TIMER() = default;
	void init() override;
	uint64_t mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) override;
	void mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) override;
};

#endif //NRF52840_TIMER_H
