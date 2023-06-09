#include "watch_gui.h"

WatchGUI::WatchGUI() {
    selected_option = 0;
    x_menu_cursor = 0;
    y_menu_cursor = 0;

    tft.init();
    tft.setRotation(1);

    setDefaultView(createMenuView());
    updateView();
}

MenuView WatchGUI::getLastView() {
    if (views.size() <= 0) {
        return defaultView();
    }

    return views.back();
}

void WatchGUI::updateView() {
    actual_view = getLastView();
    actual_view.drawView();
}

void WatchGUI::pushView(MenuView new_view) { 
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

MenuView WatchGUI::createMenuView() {
    MenuView new_menu_view = MenuView(&tft, &selected_option);
    return new_menu_view;
}

void WatchGUI::executeSelectedAction() {
    if (actual_view.getViewOptions().size() <= 0) {
        return ;
    }

    actual_view.getViewOptions()[actual_view.getSelectedOptionCounter(selected_option)].executeAction();
}

MenuView WatchGUI::defaultView() {
    return default_view;
}

void WatchGUI::setDefaultView(MenuView new_default_view) {
    default_view = new_default_view;
    updateView();
}

void WatchGUI::setSelectedOption(int new_selected_option) {
    selected_option = new_selected_option;
    actual_view.drawView();
}