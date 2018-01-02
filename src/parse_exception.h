#ifndef PARSE_EXCEPTION_H
#define PARSE_EXCEPTION_H

#include <exception>
#include <string>

class ParseException : public std::exception
{
public:
    ParseException(const std::string& message);
    const char * what() const noexcept;
private:
    std::string message;
};

#endif // PARSE_EXCEPTION_H
