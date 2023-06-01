#include "view.h"

View::View() {
    name = "Default ViewName";
    selected_option = 0;
    view_options.push_back(Option("no_options"));
}

View::View(TFT_eSPI* new_tft_pointer) {
    name = "Default ViewName";
    selected_option = 0;
    view_options.push_back(Option("no_options"));
    tft_pointer = new_tft_pointer;
}

View::View(TFT_eSPI* new_tft_pointer, std::vector<Option> new_view_options) {
    name = "Default ViewName";
    selected_option = 0;
    view_options = new_view_options;
    tft_pointer = new_tft_pointer;
}

void View::addOption(Option new_option) {
    view_options.push_back(new_option);
}

int View::getSelectedOptionCounter(int encoder_value) {
    if (view_options.size() <= 0) {
        selected_option = 0;
        return 0;
    }

    selected_option = encoder_value % view_options.size();
    return encoder_value % view_options.size();
}

void View::drawView() {
    tft_pointer->fillScreen(TFT_BLACK);
    tft_pointer->drawString("No View", 100, 100);
}
