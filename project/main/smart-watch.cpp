#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_pm.h"

#include <iostream>
#include <TFT_eSPI.h>

#include "gpio_inputs/button.h"
#include "gpio_inputs/rotary_encoder.h"

#define BUTTON_PRIMARY_PIN  GPIO_NUM_12
#define BUTTON_SECONDARY_PIN  GPIO_NUM_14
#define ROTARY_ENCODER_A GPIO_NUM_25
#define ROTARY_ENCODER_B GPIO_NUM_26

TFT_eSPI tft = TFT_eSPI();

RotaryEncoder rotary_encoder = RotaryEncoder(ROTARY_ENCODER_A, ROTARY_ENCODER_B);
Button primary_button = Button(BUTTON_PRIMARY_PIN);
Button secondary_button = Button(BUTTON_SECONDARY_PIN);

void draw_random_circles(TFT_eSPI &tft) {
    tft.fillScreen(TFT_BLACK);

    // Draw some random circles
    for (int i = 0; i < 40; i++)
    {
        int rx = random(60);
        int ry = random(60);
        int x = rx + random(320 - rx - rx);
        int y = ry + random(170 - ry - ry);
        tft.fillEllipse(x, y, rx, ry, random(0xFFFF));
    }
}

void inputs_task(void *params)
{
    int encoder_last_value = 0;
    while (1) {
        if (primary_button.isButtonDebounced()) {
            draw_random_circles(tft);
        }
        else if(secondary_button.isButtonDebounced()) {
            rotary_encoder.setCounter(0);
        }
        else if(rotary_encoder.encoderStatus()) {
            if (encoder_last_value != rotary_encoder.getCounter()) {
                encoder_last_value = rotary_encoder.getCounter();
                printf("Encoder Counter -> %d\n\n", encoder_last_value);
            }
        }
        vTaskDelay(1);
    }
}

extern "C" void app_main()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    xTaskCreate(inputs_task, "INPUTS_TASK", 2048, NULL, 1, NULL);
}
