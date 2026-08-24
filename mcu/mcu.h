//
// Created by Omeed on 8/20/26.
//

#ifndef MCU_H
#define MCU_H
#include "../components/pin.h"
#include "../components/peripheral.h"
#include "vector"

class MCU {
private:
    std::vector<std::unique_ptr<Peripheral>> peripherals;
protected:
    void add_peripheral(std::unique_ptr<Peripheral> peripheral) {
        if (peripheral != nullptr) {
            peripherals.push_back(std::move(peripheral));
        }
    }
public:
    virtual ~MCU() = default;
    virtual void init_peripherals() = 0;
};



#endif //MCU_H
