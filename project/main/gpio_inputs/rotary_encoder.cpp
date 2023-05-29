#include "rotary_encoder.h";

RotaryEncoder::RotaryEncoder(gpio_num_t rotary_gpio_input_a, gpio_num_t rotary_gpio_input_b) {
    gpio_input_a = rotary_gpio_input_a;
    gpio_input_b = rotary_gpio_input_b;
    a_last_status = 0;
    b_last_status = 0;
    counter = 0;

    setupGPIO();
}

void RotaryEncoder::setupGPIO() {
    // Rotary Encoder Setup Pin A
    gpio_pad_select_gpio(gpio_input_a);
    gpio_set_direction(gpio_input_a, GPIO_MODE_INPUT);
    gpio_pullup_dis(gpio_input_a);
    gpio_pulldown_en(gpio_input_a);

    // Rotary Encoder Setup Pin B
    gpio_pad_select_gpio(gpio_input_b);
    gpio_set_direction(gpio_input_b, GPIO_MODE_INPUT);
    gpio_pullup_dis(gpio_input_b);
    gpio_pulldown_en(gpio_input_b);

    updateGPIOStatus();
}

void RotaryEncoder::updateGPIOStatus() {
    a_actual_status = gpio_get_level(gpio_input_a);
    b_actual_status = gpio_get_level(gpio_input_b);
}

int RotaryEncoder::encoderStatus() {
    updateGPIOStatus();

    if (a_last_status == a_actual_status && b_last_status == b_actual_status) {
        return 0;
    }

    if (clockwiseRotation()) {
        counter ++;
    }
    else if (anticlockwiseRotation()) {
        counter --;
    }

    a_last_status = a_actual_status;
    b_last_status = b_actual_status;
    return 1;
}

bool RotaryEncoder::clockwiseRotation() {
    if ((a_actual_status == 1 && a_last_status == 0) && b_actual_status == 0) {
        // A turns on and B is off
        return false;
    }
    else if ((a_actual_status == 0 && a_last_status == 1) && b_actual_status == 1) {
        // A turns off and B is on
        return true;
    }
    else if ((b_actual_status == 1 && b_last_status == 0) && a_actual_status == 1) {
        // B turns on and A is on
        return true;
    }
    else if ((b_actual_status == 0 && b_last_status == 1) && a_actual_status == 0) {
        // B turns off and A is off
        return false;
    }

    return false;
}

bool RotaryEncoder::anticlockwiseRotation() {
    if ((a_actual_status == 1 && a_last_status == 0) && b_actual_status == 1) {
        // A turns on and B is on
        return false;
    }
    else if ((a_actual_status == 0 && a_last_status == 1) && b_actual_status == 0) {
        // A turns off and B is off
        return true;
    }
    else if ((b_actual_status == 1 && b_last_status == 0) && a_actual_status == 0) {
        // B turns on and A is off
        return true;
    }
    else if ((b_actual_status == 0 && b_last_status == 1) && a_actual_status == 1) {
        // B turns off and A is on
        return false;
    }

    return false;
}
