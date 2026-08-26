//
// Created by Omeed on 8/20/26.
//

#pragma once

#ifndef PIN_H
#define PIN_H

#include "vector"
#define INIT_PIN_ARR_CAPACITY 10
#define PIN_ARR_R_FACTOR 1.5

//basiclaly the problem is, how can we go from a pin class to a component? and know the component's type
// basically instantly? (we're not just doing a million dynamic casts)


class net;

class pin {
private:
    uint32_t ID; // unique id assigned to pin correlating to position in global pin array
    net* net;
};

class global_pin_arr {
private:
    pin** pins;
    uint32_t size;
    uint32_t capacity;
    void resize_pin_arr();
public:
    global_pin_arr();
    uint32_t add_pin_to_arr(pin* pin);
};

class net {
    std::vector<pin*> pins;
};



#endif //PIN_H
