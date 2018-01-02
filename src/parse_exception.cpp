#include "parse_exception.h"

ParseException::ParseException(const std::string& message) {
    this->message = message;
}

const char * ParseException::what() const noexcept {
    return message.c_str();
}
