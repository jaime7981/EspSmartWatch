#include "view.h"

View::View() {
    name = "Default ViewName";
    selected_option = 0;
    view_options.push_back(Option("no_options"));
}

View::View(std::vector<Option> new_view_options) {
    name = "Default ViewName";
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
