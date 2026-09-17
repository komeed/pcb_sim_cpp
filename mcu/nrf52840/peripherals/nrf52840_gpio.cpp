//
// Created by Omeed on 8/23/26.
//

#include "nrf52840_gpio.h"

REGISTER_PERIPHERAL(NRF52840_GPIO, NRF52840)

void NRF52840_GPIO::init() {
    out = 0;
    dir = 0;
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
    uint32_t rel_dir = dir;
    if (offset >= NRF52840_P1_OUT_OFFSET) { // if it's port 1
        rel_out = (out >> 32); // bitwise shift 32 right
        rel_dir = (dir >> 32);
        rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET || rel_offset == NRF52840_GPIO_OUTSET_OFFSET ||
        rel_offset == NRF52840_GPIO_OUTCLR_OFFSET || rel_offset == NRF52840_GPIO_IN_OFFSET) {
        return rel_out;
    }
    if (rel_offset == NRF52840_GPIO_DIR_OFFSET || rel_offset == NRF52840_GPIO_DIRSET_OFFSET ||
        rel_offset == NRF52840_GPIO_DIRCLR_OFFSET) {
        return rel_dir;
    }
    else {
        // unhandled resort to unhandled array
        printf("unhandled read mem found at addr 0x%" PRIx64 "\n", offset + NRF52840_GPIO_BASE);
        uint64_t val = 0;
        memcpy(&val, &unhandled_mem_arr[offset], size);
        return val;
    }
}

#define NEW_OUT(is_p1_bool, out, relative_port_out) \
((is_p1_bool) ? \
(((uint64_t)(out) & 0x00000000FFFFFFFFULL) | (((uint64_t)(uint32_t)(relative_port_out)) << 32)) : \
(((uint64_t)(out) & 0xFFFFFFFF00000000ULL) |  ((uint64_t)(uint32_t)(relative_port_out))))

// Write callback: triggers whenever CPU writes to MMIO range
void NRF52840_GPIO::mmio_write(uc_engine *uc, uint64_t offset, unsigned size, uint64_t value, void *user_data) {
    //so I guess we don't really need user data now because it's already linked to the nrf52840
    //   nrf52840_gpio_port* port = &gpio_cont->gpio_p1;
    uint32_t relative_port_out = out;
    uint32_t relative_port_dir = dir;
    uint64_t rel_offset = offset;
    uint32_t is_p1_bool = 0;
    if (offset >= NRF52840_P1_OUT_OFFSET) { // if we're p1
        is_p1_bool = 1;
        // port = &gpio_cont->gpio_p0;
        relative_port_out = out >> 32;
        relative_port_dir = dir >> 32;
        rel_offset = offset - NRF52840_P1_RELATIVE_OFFSET;
    }
    if (rel_offset == NRF52840_GPIO_OUT_OFFSET) {
        relative_port_out = value;
        set_out(NEW_OUT(is_p1_bool, out, relative_port_out));
        //  port->out = value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTSET_OFFSET) {
        relative_port_out |= value;
        set_out(NEW_OUT(is_p1_bool, out, relative_port_out));
        //  port->out |= value;
    }
    else if (rel_offset == NRF52840_GPIO_OUTCLR_OFFSET) {
        relative_port_out &= ~value;
        set_out(NEW_OUT(is_p1_bool, out, relative_port_out));
        //port->out &= ~value;
    }
    else if (rel_offset == NRF52840_GPIO_DIR_OFFSET) {
        relative_port_dir = value;
        set_dir(NEW_OUT(is_p1_bool, dir, relative_port_dir));
    }
    else if (rel_offset == NRF52840_GPIO_DIRSET_OFFSET) {
        relative_port_dir |= value;
        set_dir(NEW_OUT(is_p1_bool, dir, relative_port_dir));
    }
    else if (rel_offset == NRF52840_GPIO_DIRCLR_OFFSET) {
        relative_port_dir &= ~value;
        set_dir(NEW_OUT(is_p1_bool, dir, relative_port_dir));
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
   /* if (relative_port_out != out) {
        if (is_p1_bool) {
            //if it is p1, replace the top half
            set_out((out & 0x00000000FFFFFFFF) | ((uint64_t)relative_port_out << 32));
        }
        else {
            set_out((out & 0xFFFFFFFF00000000) | (uint64_t) (relative_port_out));
        }
    }
    else if (relative_port_dir != dir) {
        if (is_p1_bool) {
            //if it is p1, replace the top half
            set_dir((dir & 0x00000000FFFFFFFF) | ((uint64_t)relative_port_dir << 32));
        }
        else {
            set_dir((dir & 0xFFFFFFFF00000000) | (uint64_t) (relative_port_dir));
        }
    }*/
    /*if (is_p1_bool) {
        //if it is p1, replace the top half
        set_out((out & 0x00000000FFFFFFFF) | ((uint64_t)relative_port_out << 32));
    }
    else {
        set_out((out & 0xFFFFFFFF00000000) | (uint64_t) (relative_port_out));
    }*/
}

void NRF52840_GPIO::set_out(uint64_t new_out) {
    uint64_t old_out = out;
    out = new_out;
    if (old_out != out) {
        //printf("out changed from %" PRId64 " to %" PRId64 "\n", old_out, out);
        nrf52840_gpio_val_on_changed_64(old_out, out, "GPIO Out Changed");
    }
}
void NRF52840_GPIO::set_dir(uint64_t new_dir) {
    uint64_t old_dir = dir;
    dir = new_dir;
    if (old_dir != dir) {
        //printf("out changed from %" PRId64 " to %" PRId64 "\n", old_out, out);
        nrf52840_gpio_val_on_changed_64(old_dir, dir, "GPIO Dir Changed");
    }
}

void NRF52840_GPIO::nrf52840_gpio_val_on_changed_64(uint64_t old_value, uint64_t new_value, const char* msg) {
    uint64_t diff = old_value ^ new_value;

    while (diff != 0) {
        // 1. Find index of the lowest changed bit (0 to 47 for nRF52840 P0/P1)
        int pin_idx = __builtin_ctzll(diff);

        // 2. Extract the new state directly from new_value
        int new_val = (int)((new_value >> pin_idx) & 1ULL);

        printf("%s: #%d, new val: %d\n", msg, pin_idx, new_val);

        // set_gpio_value(pin_idx, new_val);

        // 3. Clear the lowest set bit (generates BLSR instruction on x86/ARM)
        diff &= (diff - 1);
    }
}
/*
void NRF52840_GPIO::set_gpio_value(uint32_t gpio) {

}*/