//
// Created by Omeed on 8/23/26.
//

#include "nrf52840_gpio.h"

REGISTER_PERIPHERAL(NRF52840_GPIO, NRF52840)

void NRF52840_GPIO::init() {
    out = 0;
}

uint64_t NRF52840_GPIO::mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) {
    // If code reads OUTSET or OUTCLR, return the current state of OUT
    //the quesiton is, what is userdata in this case? is it
    // - a: the nrf52840 microcontroller or something
    // - b: a peripheral that it then has to static cast?
   // nrf52840_gpio_controller* gpio_cont = user_data;
    // nrf52840_gpio_port* port = &gpio_cont->gpio_p1;
    uint64_t rel_offset = offset;
    uint32_t rel_out = out;
    if (offset >= NRF52840_P1_OUT_OFFSET) { // if it's port 1
        rel_out = (out >> 32); // bitwise shift 32 right
        rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET || rel_offset == NRF52840_GPIO_OUTSET_OFFSET ||
        rel_offset == NRF52840_GPIO_OUTCLR_OFFSET || rel_offset == NRF52840_GPIO_IN_OFFSET) {
        return rel_out;
        }
    else {
        // unhandled resort to unhandled array
        printf("unhandled read mem found at addr 0x%" PRIx64 "\n", offset + NRF52840_GPIO_BASE);
        uint64_t val = 0;
        memcpy(&val, &unhandled_mem_arr[offset], size);
        return val;
    }
}

// Write callback: triggers whenever CPU writes to MMIO range
void NRF52840_GPIO::mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {
    //so I guess we don't really need user data now because it's already linked to the nrf52840
    //   nrf52840_gpio_port* port = &gpio_cont->gpio_p1;
    uint32_t relative_port = out;
    uint64_t rel_offset = offset;
    uint32_t is_p1_bool = 0;
    if (offset >= NRF52840_P1_OUT_OFFSET) { // if we're p1
        is_p1_bool = 1;
        // port = &gpio_cont->gpio_p0;
        relative_port = out >> 32;
        rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET) {
        relative_port = value;
        //  port->out = value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTSET_OFFSET) {
        relative_port |= value;
        //  port->out |= value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTCLR_OFFSET) {
        relative_port &= ~value;
        //port->out &= ~value;
    }
    else {
        //unhandled, resort to gpio backing array
        printf("unhandled write mem found at addr 0x%" PRIx64 "\n", offset + NRF52840_GPIO_BASE);
        if (offset + size <= NRF52840_GPIO_PAGE_SIZE) {
            memcpy(&unhandled_mem_arr[offset], &value, size);
        }
        else {
            throw_exception(INDEX_OUT_OF_BOUNDS, "mmio_write exceeds unhandled_mem_arr");
        }
    }
    if (is_p1_bool) {
        //if it is p1, replace the top half
        out = (out & 0x00000000FFFFFFFF) | ((uint64_t)relative_port << 32);
    }
    else {
        out = (out & 0xFFFFFFFF00000000) | (uint64_t) (relative_port);
    }
}