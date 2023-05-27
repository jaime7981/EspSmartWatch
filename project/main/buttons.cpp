#include "buttons.h";

// Button
Button::Button(gpio_num_t button_gpio_input) {
    gpio_input = button_gpio_input;
    setupGPIO();
}

void Button::setupGPIO() {
    // Setup Button Pin
    gpio_pad_select_gpio(gpio_input);
    gpio_set_direction(gpio_input, GPIO_MODE_INPUT);
    gpio_pullup_dis(gpio_input);
    gpio_pulldown_en(gpio_input);
}

bool Button::isButtonDebounced() {
    static uint16_t btndbc = 0;
    
    btndbc=(btndbc<<1) | gpio_get_level(gpio_input) | 0xe000;

    if (btndbc==0xf000) {
        return true;
    }
    return false;
}

// Rotary Encoder
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

    if ((b_actual_status == 1 && b_last_status == 0) && a_actual_status == 1) {
        counter = counter + 1;
    }
    else if ((a_actual_status == 0 && a_last_status == 1) && b_actual_status == 0) {
        counter = counter - 1;
    }

    a_last_status = a_actual_status;
    b_last_status = b_actual_status;
    return 1;
}
