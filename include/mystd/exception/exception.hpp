#pragma once 

//---------------------------------------------------------

#include <exception>
#include <string>

//---------------------------------------------------------

#include "../../logs/logs.hpp"

//=========================================================

#define EXCP(...) Exception(__VA_ARGS__, LOG_ARGS)

//=========================================================

namespace MyStd
{

const static std::string Base_reason = "it is what it is";

class Exception : public std::exception
{

    public:

        error_code code_;
        std::string descr_;
        std::string loc_;

        Exception* reason_ = nullptr;

        Exception(const error_code code, const char* function,
                  const char*      file, const int   line):
            code_(code),
            loc_ (std::string(function) + std::string(":") +    std::string(file)
                                        + std::string(":") + std::to_string(line))
            {}
            
        Exception(const error_code  code, std::string descr, const char* function,
                  const char* file, const int line):
            code_(code),
            descr_(descr),
            loc_ (std::string(function) + std::string(":") +    std::string(file)
                                        + std::string(":") + std::to_string(line))
            {}

        Exception(const error_code code, std::string descr, Exception* reason, 
                  const char* function,  const char* file,  const int line):
            code_(code),
            descr_(descr),
            loc_ (std::string(function) + std::string(":") +    std::string(file)
                                        + std::string(":") + std::to_string(line)),
            reason_(reason)
            {}

        ~Exception()
            {
                Exception* cur = reason_;

                while(cur != nullptr)
                {
                    Exception* next = cur->reason_;
                    delete cur;
                    cur = next;
                }
            }

        const char* what() const noexcept override
            {
                return descr_.c_str();
            }
};

std::ostream& operator<< (std::ostream& os, const Exception& excp);

}; // namespace MyStd