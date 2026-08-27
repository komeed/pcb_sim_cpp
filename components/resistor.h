//
// Created by Omeed on 8/26/26.
//

#ifndef RESISTOR_H
#define RESISTOR_H

#include "pin.h"

class resistor : public net {
private:
    pin* a;
    pin* b;
    float resistance; // ohms
public:
    resistor();
};

#endif //RESISTOR_H
