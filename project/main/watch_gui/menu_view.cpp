#include "menu_view.h"

MenuView::MenuView() {
    name = "Menu View";
    selected_option = 0;
    view_options.push_back(Option("no_options"));
}

MenuView::MenuView(std::vector<Option> new_view_options) {
    name = "Menu View";
    selected_option = 0;
    view_options = new_view_options;
}

void MenuView::drawView() {
    tft_pointer.fillScreen(TFT_BLACK);

    for (int option = 0; option < actual_view.getViewOptions().size(); option ++) {
        y_menu_cursor = MENU_RECT_SPACING*2 + option*MENU_RECT_H;
        
        if (actual_view.getSelectedOptionCounter(selected_option) == option) {
            tft_pointer.fillRoundRect(MENU_RECT_SPACING, 
                              y_menu_cursor, 
                              MENU_RECT_W, 
                              MENU_RECT_H, 
                              MENU_BORDER_RADIUS, 
                              TFT_GREEN);
        }
        else {
            tft_pointer.drawRoundRect(MENU_RECT_SPACING, 
                              y_menu_cursor, 
                              MENU_RECT_W, 
                              MENU_RECT_H, 
                              MENU_BORDER_RADIUS, 
                              TFT_BROWN);
        }
        tft_pointer.drawString(actual_view.getViewOptions()[option].getName(), 
                       MENU_RECT_SPACING*2, 
                       y_menu_cursor + MENU_RECT_H/2);
    }
}
