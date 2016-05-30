#ifndef RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_
#define RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_

#include "spirit.hpp"

namespace rcpt_parser {

template<typename Iterator, typename Skipper = ascii::space_type>
struct FWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    FWS() {
        this->name("folding whitespace");
        static_cast<typename FWS::this_type&>(*this) = qi::eps;
    }
};

template<typename Iterator, typename Skipper = ascii::space_type>
struct CFWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    CFWS() {
        this->name("commented folding whitespace");
        static_cast<typename CFWS::this_type&>(*this) = qi::eps;
    }
};

} // namespace rcpt_parser

#endif
