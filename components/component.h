//
// Created by Omeed on 8/19/26.
//

#ifndef COMPONENTS_H
#define COMPONENTS_H
/*
typedef enum {
    COMPONENT_NRF52840,
    COMPONENT_LED,
    COMPONENT_SENSOR
} component_type_t;*/
/*
typedef struct {
    component_type_t type;
    void *impl;
} component;*/

class component {
public:
    virtual ~component() = default; // Essential for proper memory cleanup
};



#endif //COMPONENTS_H
