//
// Created by Omeed on 8/20/26.
//

#ifndef MCU_H
#define MCU_H
#include "../components/pin.h"
//#include "../components/peripheral.h"
#include "vector"


class IPeripheral;

template<typename TARGET_MCU>
class MCU {
protected:
    //std::vector<std::unique_ptr<IPeripheral>> peripherals;

    //some weird bs gemini cooked up idk if it works lol
    static std::vector<std::unique_ptr<IPeripheral>>& get_peripherals() {
        static std::vector<std::unique_ptr<IPeripheral>> list;
        return list;
    }
public:
    virtual ~MCU() = default;
    static void add_peripheral(std::unique_ptr<IPeripheral> peripheral) {
        if (peripheral != nullptr) {
            get_peripherals().push_back(std::move(peripheral));
        }
    }
    static void init_all_peripherals();
};



#endif //MCU_H
