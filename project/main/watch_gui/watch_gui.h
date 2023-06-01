#include <vector>
#include <string>
#include <TFT_eSPI.h>
#include "view.h"
#include "option.h"
#include "menu_view.h"

#ifndef WATCH_GUI_H
#define WATCH_GUI_H

class WatchGUI {
    private:
        TFT_eSPI tft = TFT_eSPI();

        int MENU_RECT_H = 30;
        int MENU_RECT_W = 120;
        int MENU_RECT_SPACING = 10;
        int MENU_BORDER_RADIUS = 10;

        std::vector<MenuView> views{};
        MenuView actual_view;
        MenuView default_view;

        int selected_option;
        int x_menu_cursor;
        int y_menu_cursor;

    public:
        WatchGUI();

        MenuView getLastView();
        void updateView();
        void pushView(MenuView new_view);
        void popView();
        MenuView createMenuView();
        void executeSelectedAction();

        MenuView defaultView();
        void setDefaultView(MenuView new_default_view);

        int getSelectedOption() { return selected_option; };
        void setSelectedOption(int new_selected_option);
};

#endif