#ifndef RECIPIENT_PARSER_INCLUDE_ERROR_HANDLER_HPP_
#define RECIPIENT_PARSER_INCLUDE_ERROR_HANDLER_HPP_

#include <sstream>

#include "error.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct ErrorHandler {
    typedef void result_type;

    template<class I>
        void operator()(Iterator /*begin*/, Iterator end, Iterator where,
                I const& info) const {
            std::stringstream out;
            out << "expecting " << info << " here: "
                    << boost::iterator_range<Iterator>(where, end) << std::endl;

            throw ParseError(out.str());
        }
};

}

#endif //RECIPIENT_PARSER_INCLUDE_ERROR_HANDLER_HPP_
