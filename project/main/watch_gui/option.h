#include <TFT_eSPI.h>

#ifndef OPTION_H
#define OPTION_H

class Option {
    private:
        String name = "Default OptionName";
        void (*action)() { nullptr };

    public:
        Option();
        Option(String option_name);

        String getName() { return name; };
        void setName(String new_name) { name = new_name; };

        void executeAction() { action(); };
        void setAction(void (*new_action)()) { action = new_action; };
};

#endif