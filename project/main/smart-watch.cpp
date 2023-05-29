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

void add_test_view() {
    watch_gui.pushView(View({Option("test"), Option("view"), Option("options")}));
}

void first_loaded_menu() {
    Option option_push_view = Option("push view");
    option_push_view.setAction(&add_test_view);
    watch_gui.pushView(View({Option("start"), Option("middle"), Option("end"), Option("back"), option_push_view}));
}

void inputs_task(void *params)
{
    int encoder_last_value = 0;
    first_loaded_menu();
    while (1) {
        if (primary_button.isButtonDebounced()) {
            // watch_gui.drawRandomCircles();
            rotary_encoder.setCounter(0);
            watch_gui.popView();
            watch_gui.drawSelectionMenu(rotary_encoder.getCounter());
        }
        else if(secondary_button.isButtonDebounced()) {
            watch_gui.executeSelectedAction(rotary_encoder.getCounter());
            rotary_encoder.setCounter(0);
            watch_gui.drawSelectionMenu(rotary_encoder.getCounter());
        }
        else if(rotary_encoder.encoderStatus()) {
            if (encoder_last_value != rotary_encoder.getCounter()) {
                encoder_last_value = rotary_encoder.getCounter();
                printf("Encoder Counter -> %d\n\n", encoder_last_value);
                watch_gui.drawSelectionMenu(encoder_last_value);
            }
        }
        vTaskDelay(1);
    }
}

extern "C" void app_main()
{
    xTaskCreate(inputs_task, "INPUTS_TASK", 2048, NULL, 1, NULL);
}
