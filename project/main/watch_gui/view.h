#include <vector>
#include <TFT_eSPI.h>
#include "option.h"

#ifndef VIEW_H
#define VIEW_H

class View {
    protected:
        String name;
        std::vector<Option> view_options;
        int* selected_option;
        TFT_eSPI* tft_pointer;

    public:
        void addOption(Option new_option);
        void cleanOptions();
        int getSelectedOptionCounter(int encoder_value);
        virtual void drawView() = 0;

        void drawRandomCircles();

        std::vector<Option> getViewOptions() { return view_options; };
        void setViewOptions(std::vector<Option> new_view_options) { view_options = new_view_options; };      
};

#endif