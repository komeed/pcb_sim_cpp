//
// Created by Omeed on 8/23/26.
//

#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "unicorn/unicorn.h"
#include "mcu/mcu.h"

#define REGISTER_PERIPHERAL(PERIPHERAL_TYPE, TARGET_MCU) \
static AutoRegister<PERIPHERAL_TYPE, TARGET_MCU>::Registerer \
global_reg_##PERIPHERAL_TYPE;

#define UNICORN_DEFAULT_PAGE_SIZE 0x1000
template<typename TARGET_MCU>
class MCU;


class IPeripheral {
public:
    virtual ~IPeripheral() = default;
    virtual void init() = 0;
    virtual uint64_t get_start_addr() = 0;
    virtual uint64_t get_size() = 0;
    virtual uint64_t mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) = 0;
    virtual void mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) = 0;
};

template<uint64_t START_ADDR, uint64_t SIZE>
class Peripheral : public IPeripheral {
private:
    static constexpr uint64_t start_addr = START_ADDR;
    static constexpr uint64_t size = SIZE;
protected:
    //void set_mem_info(uint64_t start_addr, uint64_t size) : start_addr(start_addr), size(size) {}
    static inline unsigned char unhandled_mem_arr[SIZE] = {};
public:
    uint64_t get_start_addr() override { return start_addr; }
    uint64_t get_size() override { return size; }
};

template <typename PERIPHERAL_TYPE, typename TARGET_MCU>
class AutoRegister {
public:
    // A dummy struct whose constructor registers the peripheral
    struct Registerer {
        Registerer() {
            MCU<TARGET_MCU>::add_peripheral(std::make_unique<PERIPHERAL_TYPE>());
        }
    };
};

#endif //PERIPHERAL_H
