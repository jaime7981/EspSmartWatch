#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_pm.h"

#include <iostream>
#include <TFT_eSPI.h>

#define LED_PIN     GPIO_NUM_21
#define BUTTON_PRIMARY_PIN  GPIO_NUM_12
#define ROTARY_ENCODER_A GPIO_NUM_25
#define ROTARY_ENCODER_B GPIO_NUM_26


TFT_eSPI tft = TFT_eSPI();

int state = 0;
xQueueHandle interputQueue;

int selector = 0;
bool led_on = false;

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

static void IRAM_ATTR gpio_interrupt_handler(void *args)
{
    int pinNumber = (int)args;
    xQueueSendFromISR(interputQueue, &pinNumber, NULL);
}

void change_led_status() {
    if (led_on) {
        gpio_set_level(LED_PIN, 0);
        led_on = false;
    }
    else {
        gpio_set_level(LED_PIN, 1);
        led_on = true;
    }
}

void LED_Control_Task(void *params)
{
    int pinNumber, count = 0;
    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
        {
            if (pinNumber == 12) {
                // trigger_action(selector);
                change_led_status();
                printf("unbounced button\n");
            }
            else {
                printf("GPIO %d was pressed %d times. The state is %d\n", pinNumber, count++, gpio_get_level(ROTARY_ENCODER_A));
            }
        }
    }
}

void load_interrupts() {
    // Push Button Primary Setup
    gpio_pad_select_gpio(BUTTON_PRIMARY_PIN);
    gpio_set_direction(BUTTON_PRIMARY_PIN, GPIO_MODE_INPUT);
    gpio_pullup_dis(BUTTON_PRIMARY_PIN);
    gpio_pulldown_en(BUTTON_PRIMARY_PIN);
    gpio_set_intr_type(BUTTON_PRIMARY_PIN, GPIO_INTR_POSEDGE);

    // Rotary Encoder Setup Pin A
    gpio_pad_select_gpio(ROTARY_ENCODER_A);
    gpio_set_direction(ROTARY_ENCODER_A, GPIO_MODE_INPUT);
    gpio_pulldown_dis(ROTARY_ENCODER_A);
    gpio_pullup_en(ROTARY_ENCODER_A);
    gpio_set_intr_type(ROTARY_ENCODER_A, GPIO_INTR_ANYEDGE);

    // Rotary Encoder Setup Pin B
    gpio_pad_select_gpio(ROTARY_ENCODER_B);
    gpio_set_direction(ROTARY_ENCODER_B, GPIO_MODE_INPUT);
    gpio_pulldown_dis(ROTARY_ENCODER_B);
    gpio_pullup_en(ROTARY_ENCODER_B);
    gpio_set_intr_type(ROTARY_ENCODER_B, GPIO_INTR_ANYEDGE);

    // Setup Interrrupts
    interputQueue = xQueueCreate(10, sizeof(int));
    xTaskCreate(LED_Control_Task, "LED_Control_Task", 2048, NULL, 1, NULL);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_PRIMARY_PIN, gpio_interrupt_handler, (void *)BUTTON_PRIMARY_PIN);
    gpio_isr_handler_add(ROTARY_ENCODER_A, gpio_interrupt_handler, (void *)ROTARY_ENCODER_A);
    gpio_isr_handler_add(ROTARY_ENCODER_B, gpio_interrupt_handler, (void *)ROTARY_ENCODER_B);
}

extern "C" void app_main()
{
    tft.init();
    tft.setRotation(1);

    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    load_interrupts();
}