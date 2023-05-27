#include "driver/gpio.h"

#ifndef BUTTONS_H
#define BUTTONS_H

class Button {
    private:
        gpio_num_t gpio_input;

    public:
        Button(gpio_num_t button_gpio_input);

        void setupGPIO();
        bool isButtonDebounced();
};

class RotaryEncoder {
    private:
        gpio_num_t gpio_input_a;
        gpio_num_t gpio_input_b;
        int a_last_status;
        int b_last_status;
        int a_actual_status;
        int b_actual_status;
        int counter;

    public:
        RotaryEncoder(gpio_num_t rotary_gpio_input_a, gpio_num_t rotary_gpio_input_b);

        void setupGPIO();
        void updateGPIOStatus();
        int encoderStatus();

        int getCounter()  { return counter; }
        void setCounter(int set_value) { counter = set_value; }
};

#endif