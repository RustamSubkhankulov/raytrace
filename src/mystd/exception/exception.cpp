#include <iostream>

#include "../../../include/mystd/exception/exception.hpp"

//=========================================================

namespace MyStd{

std::ostream& operator<< (std::ostream& os, const Exception& excp)
{
    if (!excp.descr_.empty())
        os << excp.descr_ << '\n';

    os << "Error code: " << excp.code_ << ' ';
    os << "Error summary: " << get_error_descr(excp.code_) << '\n';
    os << "Occured at " << excp.loc_;

    os << "\n\n" "due to the fact that" "\n\n";

    if (excp.reason_ != nullptr)
        return os << *(excp.reason_);
    else
        return os << Base_reason << '\n';
}

}; // namespace MyStd