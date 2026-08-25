//
// Created by Omeed on 8/23/26.
//

#ifndef NRF52840_GPIO_H
#define NRF52840_GPIO_H

#include "components/peripheral.h"
#include "../nrf52840_registers.h"
#include <cstring>
#include "utils/errorhandler.h"

class NRF52840;

//specifying the memory specifications of this peripheral
class NRF52840_GPIO : public virtual Peripheral<NRF52840_GPIO_BASE, NRF52840_GPIO_PAGE_SIZE> {
private:
    uint64_t out;
public:
    NRF52840_GPIO() = default;
    void init() override;
    uint64_t mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) override;
    void mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) override;


};



#endif //NRF52840_GPIO_H
