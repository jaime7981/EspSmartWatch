#include <vector>
#include <string>
#include <TFT_eSPI.h>
#include "view.h"
#include "option.h"

#ifndef WATCH_GUI_H
#define WATCH_GUI_H

class WatchGUI {
    private:
        TFT_eSPI tft = TFT_eSPI();

        int MENU_RECT_H = 30;
        int MENU_RECT_W = 120;
        int MENU_RECT_SPACING = 10;
        int MENU_BORDER_RADIUS = 10;

        std::vector<View> views{};
        std::vector<Option> view_options{};
        View actual_view;

        int selected_option;
        int x_menu_cursor;
        int y_menu_cursor;

    public:
        WatchGUI();

        View getLastView();
        void updateView();
        void pushView(View new_view);
        void popView();
        
        void drawRandomCircles();
        void drawSelectionMenu(int encoder_value);
};

#endif