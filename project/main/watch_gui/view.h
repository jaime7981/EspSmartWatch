#include <vector>
#include <TFT_eSPI.h>
#include "option.h"

#ifndef VIEW_H
#define VIEW_H

class View {
    private:
        String name;
        std::vector<Option> view_options;
        int selected_option;
        TFT_eSPI* tft_pointer;

    public:
        View();
        View(TFT_eSPI* new_tft_pointer);
        View(TFT_eSPI* new_tft_pointer, std::vector<Option> new_view_options);

        void addOption(Option new_option);
        int getSelectedOptionCounter(int encoder_value);
        void drawView();

        std::vector<Option> getViewOptions() { return view_options; };
        void setViewOptions(std::vector<Option> new_view_options) { view_options = new_view_options; };      
};

#endif