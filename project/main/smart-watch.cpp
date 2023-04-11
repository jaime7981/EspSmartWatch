
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_pm.h"

#include <iostream>
#include <TFT_eSPI.h>

#define LED_PIN     GPIO_NUM_21
#define BUTTON_PRIMARY_PIN  GPIO_NUM_12


TFT_eSPI tft = TFT_eSPI();       // Invoke custom library



void trigger_action(int selector) {
    switch(selector) {
        case 0:
            printf("go back\n");
            break;
        case 1:
            printf("first option\n");
            break;
        case 2:
            printf("turn on led\n");
            gpio_set_level(LED_PIN, 1);
            break;
        case 3:
            printf("turn of led\n");
            gpio_set_level(LED_PIN, 0);
            break;
        default:
            printf("selector out of the scope\n");
            break;
    }
}

extern "C" void app_main()
{
    int selector = 0;
    bool is_pressed = false;

    tft.init();
    tft.setRotation(1);

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PRIMARY_PIN, GPIO_MODE_INPUT);

    while(1) {

        
        tft.fillScreen(TFT_BLACK);

        // Draw some random circles
        for (int i = 0; i < 40; i++)
        {
            int rx = random(60);
            int ry = random(60);
            int x = rx + random(480 - rx - rx);
            int y = ry + random(320 - ry - ry);
            tft.fillEllipse(x, y, rx, ry, random(0xFFFF));
        }

        delay(2000);
        tft.fillScreen(TFT_BLACK);

        for (int i = 0; i < 40; i++)
        {
            int rx = random(60);
            int ry = random(60);
            int x = rx + random(480 - rx - rx);
            int y = ry + random(320 - ry - ry);
            tft.drawEllipse(x, y, rx, ry, random(0xFFFF));
        }
        
        
        // printf("button status: %d\n", gpio_get_level(BUTTON_PRIMARY_PIN));
        if (!is_pressed && gpio_get_level(BUTTON_PRIMARY_PIN) == 1) {
            trigger_action(selector);
            is_pressed = true;
        }
        else if (gpio_get_level(BUTTON_PRIMARY_PIN) == 0) {
            is_pressed = false;
        }
        vTaskDelay(1); // Add 1 tick delay (10 ms) so that current task does not starve idle task and trigger watchdog timer
    }
}

/*
extern void app_main(void) {
    int selector = 0;
    bool is_pressed = false;

    //tft.init();
    //tft.setRotation(1);

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_PRIMARY_PIN, GPIO_MODE_INPUT);

    while(1) {

        
        tft.fillScreen(TFT_BLACK);

        // Draw some random circles
        for (int i = 0; i < 40; i++)
        {
            int rx = random(60);
            int ry = random(60);
            int x = rx + random(480 - rx - rx);
            int y = ry + random(320 - ry - ry);
            tft.fillEllipse(x, y, rx, ry, random(0xFFFF));
        }

        delay(2000);
        tft.fillScreen(TFT_BLACK);

        for (int i = 0; i < 40; i++)
        {
            int rx = random(60);
            int ry = random(60);
            int x = rx + random(480 - rx - rx);
            int y = ry + random(320 - ry - ry);
            tft.drawEllipse(x, y, rx, ry, random(0xFFFF));
        }
        
        
        // printf("button status: %d\n", gpio_get_level(BUTTON_PRIMARY_PIN));
        if (!is_pressed && gpio_get_level(BUTTON_PRIMARY_PIN) == 1) {
            trigger_action(selector);
            is_pressed = true;
        }
        else if (gpio_get_level(BUTTON_PRIMARY_PIN) == 0) {
            is_pressed = false;
        }
        vTaskDelay(1); // Add 1 tick delay (10 ms) so that current task does not starve idle task and trigger watchdog timer
    }  
}
*/