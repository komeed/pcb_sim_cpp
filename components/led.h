//
// Created by Omeed on 8/19/26.
//

#ifndef LED_H
#define LED_H

#include "pin.h"
#include "component.h"

class led : public virtual component {
public:
    pin pos;
    pin neg;
private:
};

#endif //LED_H
