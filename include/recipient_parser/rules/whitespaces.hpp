#ifndef RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_
#define RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_

#include "../detail/spirit.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct FWS : qi::rule<Iterator, std::string()> {
    FWS() {
        folded.name("folded fws");
        folded %= qi::hold[*qi::blank >> qi::omit[qi::eol] >> +qi::blank];

        nonfolded.name("nonfolded fws");
        nonfolded = +qi::blank;

        this->name("fws (folding whitespace)");
        static_cast<typename FWS::this_type&>(*this) %= folded | nonfolded;
    }

    qi::rule<Iterator, std::string()> folded, nonfolded;
};

template<typename Iterator>
void debug(FWS<Iterator>& fws) {
    debug(static_cast<typename FWS<Iterator>::this_type&>(fws));
    debug(fws.folded);
    debug(fws.nonfolded);
}


// Non-RFC, no comments so far
template<typename Iterator>
struct CFWS : qi::rule<Iterator, std::string()> {
    CFWS() {
        this->name("cwfs (commented folding whitespace)");
        static_cast<typename CFWS::this_type&>(*this) %= fws;
    }

    FWS<Iterator> fws;
};

template<typename Iterator>
void debug(CFWS<Iterator>& cfws) {
    debug(static_cast<typename CFWS<Iterator>::this_type&>(cfws));
    debug(cfws.fws);
}

} // namespace rcpt_parser

#endif
