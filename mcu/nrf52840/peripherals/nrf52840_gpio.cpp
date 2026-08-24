//
// Created by Omeed on 8/23/26.
//

#include "nrf52840_gpio.h"

NRF52840_GPIO::NRF52840_GPIO() : Peripheral (NRF52840_GPIO_BASE,
    NRF52840_GPIO_PAGE_SIZE) {

}

uint64_t NRF52840_GPIO::mmio_read(uc_engine *uc, uint64_t offset, unsigned size, void *user_data) {
    // If code reads OUTSET or OUTCLR, return the current state of OUT
    //the quesiton is, what is userdata in this case? is it
    // - a: the nrf52840 microcontroller or something
    // - b: a peripheral that it then has to static cast?
    NRF52840_GPIO *gpio = (NRF52840_GPIO *) user_data;
    nrf52840_gpio_controller* gpio_cont = static_cast<nrf52840_gpio_controller*>(user_data);
    nrf52840_gpio_port* port = &gpio_cont->gpio_p1;
    uint64_t rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    if (offset < NRF52840_P1_OUT_OFFSET) {
        port = &gpio_cont->gpio_p0;
        rel_offset = offset;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET || rel_offset == NRF52840_GPIO_OUTSET_OFFSET ||
        rel_offset == NRF52840_GPIO_OUTCLR_OFFSET || rel_offset == NRF52840_GPIO_IN_OFFSET) {
        return port->out;
    }
    else {
        // unhandled resort to unhandled array
        printf("unhandled read mem found at addr 0x%" PRIx64 "\n", offset + NRF52840_GPIO_BASE);
        uint64_t val = 0;
        memcpy(&val, &gpio_cont->unhandled_mem_arr[offset], size);
        return val;
    }
}

// Write callback: triggers whenever CPU writes to MMIO range
void NRF52840_GPIO::mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {
    auto gpio_cont = static_cast<nrf52840_gpio_controller *>(user_data);
    nrf52840_gpio_port* port = &gpio_cont->gpio_p1;
    uint64_t rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    if (offset < NRF52840_P1_OUT_OFFSET) {
        port = &gpio_cont->gpio_p0;
        rel_offset = offset;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET) {
        port->out = value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTSET_OFFSET) {
        port->out |= value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTCLR_OFFSET) {
        port->out &= ~value;
    }
    else {
        //unhandled, resort to gpio backing array
        printf("unhandled write mem found at addr 0x%" PRIx64 "\n", offset + NRF52840_GPIO_BASE);
        if (offset + size <= NRF52840_GPIO_PAGE_SIZE) {
            memcpy(&gpio_cont->unhandled_mem_arr[offset], &value, size);
        }
        else {
            throw_exception(INDEX_OUT_OF_BOUNDS, "mmio_write exceeds unhandled_mem_arr");
        }
    }
}