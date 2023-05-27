#include "driver/gpio.h"

#ifndef ROATARY_ENCODER_H
#define ROATARY_ENCODER_H

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
        bool isAOn();
        bool clockwiseRotation();
        bool anticlockwiseRotation();

        int getCounter()  { return counter; }
        void setCounter(int set_value) { counter = set_value; }
};

#endif