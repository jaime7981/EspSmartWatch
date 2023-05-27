#include "driver/gpio.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button {
    private:
        gpio_num_t gpio_input;

    public:
        Button(gpio_num_t button_gpio_input);

        void setupGPIO();
        bool isButtonDebounced();
};

#endif