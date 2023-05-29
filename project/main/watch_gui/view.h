#include <vector>
#include <TFT_eSPI.h>

#ifndef VIEW_H
#define VIEW_H

class View {
    private:
        std::vector<String> view_options{"no_options"};

    public:
        View();
        View(std::vector<String> new_view_options);

        std::vector<String> getViewOptions() { return view_options; };
        void setViewOptions(std::vector<String> new_view_options) { view_options = new_view_options; };
};

#endif