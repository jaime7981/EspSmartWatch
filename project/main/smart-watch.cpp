#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_pm.h"

#include <iostream>
#include <TFT_eSPI.h>

#define BUTTON_PRIMARY_PIN  GPIO_NUM_12
#define BUTTON_SECONDARY_PIN  GPIO_NUM_14
#define ROTARY_ENCODER_A GPIO_NUM_25
#define ROTARY_ENCODER_B GPIO_NUM_26

TFT_eSPI tft = TFT_eSPI();
// xQueueHandle interputQueue;

int selector = 0;
bool led_on = false;

struct RotaryEncoderValues {
    int a_last_status;
    int b_last_status;
    int counter;
};

struct RotaryEncoderValues rotary_encoder_values = {0, 0, 0};

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
            break;
        case 3:
            printf("turn of led\n");
            break;
        default:
            printf("selector out of the scope\n");
            break;
    }
}

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

bool is_button_debounced(gpio_num_t debounce_pin) {
    static uint16_t btndbc = 0, lastb = 0;
    
    btndbc=(btndbc<<1) | gpio_get_level(debounce_pin) | 0xe000;

    if (btndbc!=lastb) {
        // printf("btndbc: %d / hex: %d\n" ,btndbc,HEX);
    }
    lastb = btndbc;

    if (btndbc==0xf000) {
        printf("debounced action\n");
        return true;
    }
    return false;
}

int update_encoder_counter(int parameter_update) {
    rotary_encoder_values.counter = rotary_encoder_values.counter + parameter_update;
    return 0;
}

void set_encoder_counter(int set_value) {
    rotary_encoder_values.counter = set_value;
    printf("Encoder counter reseted to -> %d\n", rotary_encoder_values.counter);
}

int encoder_status(int rot_a, int rot_b) {
    if (rotary_encoder_values.a_last_status == rot_a && rotary_encoder_values.b_last_status == rot_b) {
        return 0;
    }

    if ((rot_a == 0 && rotary_encoder_values.a_last_status == 1) && rot_b == 1) {
        printf("clockwise status a\n");
        update_encoder_counter(1);
    }
    else if ((rot_a == 0 && rotary_encoder_values.a_last_status == 1) && rot_b == 0) {
        printf("anti clockwise status a\n");
        update_encoder_counter(-1);
    }

    rotary_encoder_values.a_last_status = rot_a;
    rotary_encoder_values.b_last_status = rot_b;
    return 1;
}

void inputs_task(void *params)
{
    while (1) {
        if (is_button_debounced(BUTTON_PRIMARY_PIN)) {
            draw_random_circles(tft);
        }
        else if(is_button_debounced(BUTTON_SECONDARY_PIN)) {
            set_encoder_counter(0);
        }
        else if(encoder_status(gpio_get_level(ROTARY_ENCODER_A), gpio_get_level(ROTARY_ENCODER_B))) {
            printf("Encoder Counter -> %d\n\n", rotary_encoder_values.counter);
        }
        vTaskDelay(10);
    }
}

void load_gpio() {
    // Push Button Primary Setup
    gpio_pad_select_gpio(BUTTON_PRIMARY_PIN);
    gpio_set_direction(BUTTON_PRIMARY_PIN, GPIO_MODE_INPUT);
    gpio_pullup_dis(BUTTON_PRIMARY_PIN);
    gpio_pulldown_en(BUTTON_PRIMARY_PIN);
    
    // Push Button Secondary Setup
    gpio_pad_select_gpio(BUTTON_SECONDARY_PIN);
    gpio_set_direction(BUTTON_SECONDARY_PIN, GPIO_MODE_INPUT);
    gpio_pullup_dis(BUTTON_SECONDARY_PIN);
    gpio_pulldown_en(BUTTON_SECONDARY_PIN);

    // Rotary Encoder Setup Pin A
    gpio_pad_select_gpio(ROTARY_ENCODER_A);
    gpio_set_direction(ROTARY_ENCODER_A, GPIO_MODE_INPUT);
    gpio_pullup_dis(ROTARY_ENCODER_A);
    gpio_pulldown_en(ROTARY_ENCODER_A);

    // Rotary Encoder Setup Pin B
    gpio_pad_select_gpio(ROTARY_ENCODER_B);
    gpio_set_direction(ROTARY_ENCODER_B, GPIO_MODE_INPUT);
    gpio_pullup_dis(ROTARY_ENCODER_B);
    gpio_pulldown_en(ROTARY_ENCODER_B);

    xTaskCreate(inputs_task, "INPUTS_TASK", 2048, NULL, 1, NULL);
}

extern "C" void app_main()
{
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    load_gpio();

}
