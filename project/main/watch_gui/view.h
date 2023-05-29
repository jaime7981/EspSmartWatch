#include <vector>
#include <TFT_eSPI.h>
#include "option.h"

#ifndef VIEW_H
#define VIEW_H

class View {
    private:
        String name = "Default ViewName";
        std::vector<Option> view_options{Option("no_options")};

    public:
        View();
        View(std::vector<Option> new_view_options);

        std::vector<Option> getViewOptions() { return view_options; };
        void setViewOptions(std::vector<Option> new_view_options) { view_options = new_view_options; };
};

#endif