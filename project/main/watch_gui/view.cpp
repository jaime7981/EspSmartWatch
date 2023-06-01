#include "view.h"

void View::addOption(Option new_option) {
    view_options.push_back(new_option);
}

int View::getSelectedOptionCounter(int encoder_value) {
    if (view_options.size() <= 0) {
        selected_option = 0;
        return 0;
    }

    *selected_option = encoder_value % view_options.size();
    return encoder_value % view_options.size();
}

void View::drawView() {
    tft_pointer->fillScreen(TFT_BLACK);
    tft_pointer->drawString(name, 100, 100);
}

void View::drawRandomCircles() {
    tft_pointer->fillScreen(TFT_BLACK);

    // Draw some random circles
    for (int i = 0; i < 40; i++)
    {
        int rx = random(60);
        int ry = random(60);
        int x = rx + random(320 - rx - rx);
        int y = ry + random(170 - ry - ry);
        tft_pointer->fillEllipse(x, y, rx, ry, random(0xFFFF));
    }
}