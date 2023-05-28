#include "watch_gui.h"

WatchGUI::WatchGUI() {
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    std::vector<String> menu_options{"start", "middle", "extra", "end"};
    selected_option = 0;
    x_menu_cursor = 0;
    y_menu_cursor = 0;
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
    selected_option = encoder_value % menu_options.size();
    x_menu_cursor = MENU_RECT_SPACING;

    for (int option = 0; option < menu_options.size(); option ++) {
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
        tft.drawString(menu_options[option], 
                       x_menu_cursor + MENU_RECT_SPACING, 
                       y_menu_cursor + MENU_RECT_H/2);
    }
}
