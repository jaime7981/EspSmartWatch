#include "button.h";

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
