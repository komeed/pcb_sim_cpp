//
// Created by Omeed on 8/20/26.
//

#include "pin.h"

//initialization of global pins array
inline std::vector<pin*> global_pins_arr = std::vector<pin*>();

global_pin_arr::global_pin_arr() {
    size = 0;
    capacity = INIT_PIN_ARR_CAPACITY;
    pins = (pin**)malloc(capacity * sizeof(pin*));
}

void global_pin_arr::resize_pin_arr() {
    capacity *= PIN_ARR_R_FACTOR;
    pins = (pin**)realloc(pins, capacity * sizeof(pin*));
}

uint32_t global_pin_arr::add_pin_to_arr(pin* pin) {
    if (size >= capacity) {
        resize_pin_arr();
    }
    pins[size] = pin;
    size++;
    return size - 1;
}