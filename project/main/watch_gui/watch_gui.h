#include <vector>
#include <string>
#include <TFT_eSPI.h>
#include "driver/gpio.h"

#ifndef WATCH_GUI_H
#define WATCH_GUI_H

class WatchGUI {
    private:
        TFT_eSPI tft = TFT_eSPI();

        int MENU_RECT_H = 30;
        int MENU_RECT_W = 120;
        int MENU_RECT_SPACING = 10;
        int MENU_BORDER_RADIUS = 10;

        std::vector<String> menu_options;
        int selected_option;
        int x_menu_cursor;
        int y_menu_cursor;

    public:
        WatchGUI();

        void drawRandomCircles();
        void drawSelectionMenu(int encoder_value);
};

#endif