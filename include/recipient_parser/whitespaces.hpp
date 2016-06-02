#ifndef RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_
#define RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_

#include "spirit.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct FWS : qi::rule<Iterator> {
    FWS() {
        this->name("fws (folding whitespace)");
        static_cast<typename FWS::this_type&>(*this) = 
                (*qi::blank >> qi::eol >> +qi::blank) | +qi::blank;
    }
};


// Non-RFC, no comments so far
template<typename Iterator>
struct CFWS : qi::rule<Iterator> {
    CFWS() {
        this->name("cwfs (commented folding whitespace)");
        static_cast<typename CFWS::this_type&>(*this) = fws;
    }

    FWS<Iterator> fws;
};

} // namespace rcpt_parser

#endif
