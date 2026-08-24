//
// Created by Omeed on 8/23/26.
//

#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "unicorn/unicorn.h"
#define UNICORN_DEFAULT_PAGE_SIZE 0x1000

typedef enum {
    GPIO,
    OTHER
} PERIPHERAL_TYPE;

template<uint64_t START_ADDR, uint64_t SIZE>
class Peripheral {
private:
    uint64_t start_addr;
    uint64_t size;
    unsigned char* unhandled_mem_arr[SIZE];
protected:
    void set_mem_info(uint64_t start_addr, uint64_t size) : start_addr(start_addr), size(size) {}
public:
    Peripheral() : start_addr(START_ADDR), size(SIZE) {}
    virtual ~Peripheral() = default;
    virtual uint64_t mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) = 0;
    virtual void mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) = 0;
};

#endif //PERIPHERAL_H
