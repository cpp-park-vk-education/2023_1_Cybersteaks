#pragma once

#include <string>

class Error : public std::exception
{
public:
    Error(const std::string &message) : message_(message) {}

    const char *what() const noexcept override
    {
        return message_.c_str();
    }
    const std::string getMessage() const
    {
        return message_;
    }

private:
    std::string message_;
};
