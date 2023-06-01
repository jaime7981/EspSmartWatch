#include <stdio.h>
#include <iostream>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_pm.h"

#include "gpio_inputs/button.h"
#include "gpio_inputs/rotary_encoder.h"
#include "watch_gui/watch_gui.h"
#include "watch_gui/view.h"

#define BUTTON_PRIMARY_PIN  GPIO_NUM_12
#define BUTTON_SECONDARY_PIN  GPIO_NUM_14
#define ROTARY_ENCODER_A GPIO_NUM_25
#define ROTARY_ENCODER_B GPIO_NUM_26

WatchGUI watch_gui = WatchGUI();

RotaryEncoder rotary_encoder = RotaryEncoder(ROTARY_ENCODER_A, ROTARY_ENCODER_B);
Button primary_button = Button(BUTTON_PRIMARY_PIN);
Button secondary_button = Button(BUTTON_SECONDARY_PIN);

void inputs_task(void *params)
{
    int encoder_last_value = 0;
    while (1) {
        if (primary_button.isButtonDebounced()) {
            rotary_encoder.setCounter(0);
            watch_gui.popView();
        }
        else if(secondary_button.isButtonDebounced()) {
            watch_gui.executeSelectedAction();
            rotary_encoder.setCounter(0);
        }
        else if(rotary_encoder.encoderStatus()) {
            if (encoder_last_value != rotary_encoder.getCounter()) {
                watch_gui.setSelectedOption(rotary_encoder.getCounter());
                encoder_last_value = rotary_encoder.getCounter();
                printf("Encoder Counter -> %d\n\n", encoder_last_value);
            }
        }
        vTaskDelay(1);
    }
}

extern "C" void app_main()
{
    xTaskCreate(inputs_task, "INPUTS_TASK", 2048, NULL, 1, NULL);
}
