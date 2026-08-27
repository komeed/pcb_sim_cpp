//
// Created by Omeed on 8/20/26.
//

#include "pin.h"

//initialization of global pins array
/*inline std::vector<pin*> global_pins_arr = std::vector<pin*>();

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
}*/

pin::pin(component* comp, uint32_t is_sink) : is_sink(is_sink), parent_comp(comp) {
    wired_net = nullptr;

}

//this assumes that the current pin is
void pin::connect_to_pin(pin* other) {
    if (wired_net == nullptr && other->wired_net == nullptr) {
        // both pins don't have nets, create a net connecting them
        auto n = new net();
        wired_net = n;
        other->wired_net = n;

    }
}

net::net() {
    pins = std::vector<pin*>();
    voltage = 0; // initial voltage is 0
}