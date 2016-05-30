#ifndef RECIPIENT_PARSER_INCLUDE_PARSER_HPP_
#define RECIPIENT_PARSER_INCLUDE_PARSER_HPP_

#include <sstream>
#include <stdexcept>

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

            throw std::runtime_error(out.str());
        }
};

}

#endif //RECIPIENT_PARSER_INCLUDE_PARSER_HPP_
