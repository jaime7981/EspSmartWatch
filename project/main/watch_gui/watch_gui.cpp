#include "watch_gui.h"

WatchGUI::WatchGUI() {
    tft.init();
    tft.setRotation(1);

    updateView();
    
    selected_option = 0;
    x_menu_cursor = 0;
    y_menu_cursor = 0;
}

View WatchGUI::getLastView() {
    if (views.size() <= 0) {
        return View();
    }

    return views.back();
}

void WatchGUI::updateView() {
    actual_view = getLastView();
    view_options = actual_view.getViewOptions();
}

void WatchGUI::pushView(View new_view) { 
    views.push_back(new_view);
    updateView();
}

void WatchGUI::popView() {
    if (views.size() <= 0) {
        return ;
    }
    views.pop_back(); 
    updateView();
}

void WatchGUI::drawRandomCircles() {
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

void WatchGUI::drawSelectionMenu(int encoder_value) {
    tft.fillScreen(TFT_BLACK);

    if (view_options.size() <= 0) {
        return ;
    }

    selected_option = encoder_value % view_options.size();
    x_menu_cursor = MENU_RECT_SPACING;

    for (int option = 0; option < view_options.size(); option ++) {
        y_menu_cursor = MENU_RECT_SPACING*2 + option*MENU_RECT_H;
        
        if (selected_option == option) {
            tft.fillRoundRect(x_menu_cursor, 
                              y_menu_cursor, 
                              MENU_RECT_W, 
                              MENU_RECT_H, 
                              MENU_BORDER_RADIUS, 
                              TFT_GREEN);
        }
        else {
            tft.drawRoundRect(x_menu_cursor, 
                              y_menu_cursor, 
                              MENU_RECT_W, 
                              MENU_RECT_H, 
                              MENU_BORDER_RADIUS, 
                              TFT_BROWN);
        }
        tft.drawString(view_options[option].getName(), 
                       x_menu_cursor + MENU_RECT_SPACING, 
                       y_menu_cursor + MENU_RECT_H/2);
    }
}
