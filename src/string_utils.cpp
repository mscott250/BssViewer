#include "string_utils.h"

#include <ctype.h>

bool StringUtils::isBlank(std::string& str) {

    std::string::const_iterator it = str.begin();
    while (it != str.end()) {
        if (!std::isspace(*it)) {
            return false;
        }
    }

    return true;
}
