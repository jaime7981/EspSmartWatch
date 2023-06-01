#include <TFT_eSPI.h>
#include "view.h"

#ifndef MENU_VIEW_H
#define MENU_VIEW_H

class MenuView : public View {
    private:
        int MENU_RECT_H = 30;
        int MENU_RECT_W = 120;
        int MENU_RECT_SPACING = 10;
        int MENU_BORDER_RADIUS = 10;

        int x_menu_cursor;
        int y_menu_cursor;

    public:
        MenuView();
        MenuView(std::vector<Option> new_view_options);

        void drawView();
};

#endif