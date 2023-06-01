#include "watch_gui.h"

WatchGUI::WatchGUI() {
    selected_option = 0;
    x_menu_cursor = 0;
    y_menu_cursor = 0;

    tft.init();
    tft.setRotation(1);

    updateView();
}

View WatchGUI::getLastView() {
    if (views.size() <= 0) {
        return defaultView();
    }

    return views.back();
}

void WatchGUI::updateView() {
    actual_view = getLastView();
    actual_view.drawView();
}

void WatchGUI::pushView(View new_view) { 
    views.push_back(new_view);
    updateView();
}

void WatchGUI::popView() {
    if (views.size() <= 0) {
        return ;
    }
    selected_option = 0;
    views.pop_back(); 
    updateView();
}

void WatchGUI::executeSelectedAction() {
    if (actual_view.getViewOptions().size() <= 0) {
        return ;
    }

    actual_view.getViewOptions()[actual_view.getSelectedOptionCounter(selected_option)].executeAction();
}

View WatchGUI::defaultView() {
    View defaultView = View(&tft);
    Option default_first_option = Option("firstOption");
    defaultView.addOption(default_first_option);
    // pushView(defaultView);
    return defaultView;
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

void WatchGUI::setSelectedOption(int new_selected_option) {
    selected_option = new_selected_option;
    actual_view.drawView();
}