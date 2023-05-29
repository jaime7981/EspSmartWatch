#include "view.h"

View::View() {
    selected_option = 0;
}

View::View(std::vector<Option> new_view_options) {
    selected_option = 0;
    view_options = new_view_options;
}

int View::getSelectedOptionCounter(int encoder_value) {
    if (view_options.size() <= 0) {
        selected_option = 0;
        return 0;
    }

    selected_option = encoder_value % view_options.size();
    return encoder_value % view_options.size();
}
