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
        void (*draw_view)() { nullptr };

    public:
        View();
        View(std::vector<Option> new_view_options);

        int getSelectedOptionCounter(int encoder_value);

        std::vector<Option> getViewOptions() { return view_options; };
        void setViewOptions(std::vector<Option> new_view_options) { view_options = new_view_options; };
        
        void drawView() { draw_view(); };
        void setView(void (*new_draw_view)()) { draw_view = new_draw_view; };
};

#endif