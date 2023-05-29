#include "option.h"

void functionNotAssigned() {

}

Option::Option() {
    action = &functionNotAssigned;
}

Option::Option(String option_name) {
    action = &functionNotAssigned;
    name = option_name;
}
