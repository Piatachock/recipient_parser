#ifndef RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_
#define RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_

#include "../detail/spirit.hpp"

namespace rcpt_parser {

//TODO: rework this tag-system to match style in QuotedPair and QuotedString
namespace normalize {
    struct None {};   //leave data as-is
    struct Crlf {};   //throw away crlf (RFC)
    struct All {};    //squash FWS into single whitespace
}

template<typename Iterator>
struct FWS : qi::rule<Iterator, std::string()> {
    template<typename NormalizeStrategy = normalize::None>
    FWS(NormalizeStrategy normalize_tag = NormalizeStrategy{}) {
        // Non-RFC, because RFC stricts newline to be CRLF only, and here we support CR or LF.
        crlf.name("crlf");
        crlf %= qi::hold[(qi::char_('\r') >> -qi::char_('\n')) | qi::char_('\n')];

        folded.name("folded fws");
        init_folded(normalize_tag);

        nonfolded.name("nonfolded fws");
        nonfolded %= +qi::blank;

        this->name("fws (folding whitespace)");
        static_cast<typename FWS::this_type&>(*this) %= folded | nonfolded;
    }

    void init_folded(normalize::None) {
        folded %= qi::hold[*qi::blank >> crlf >> +qi::blank];
    }

    void init_folded(normalize::Crlf) {
        folded %= qi::hold[*qi::blank >> qi::omit[crlf] >> +qi::blank];
    }

    void init_folded(normalize::All) {
        folded %= qi::omit[*qi::blank >> crlf >> +qi::blank] >> qi::attr(" ");
    }

    qi::rule<Iterator, std::string()> crlf, folded, nonfolded;
};

template<typename Iterator>
void debug(FWS<Iterator>& fws) {
    debug(static_cast<typename FWS<Iterator>::this_type&>(fws));
    debug(fws.crlf);
    debug(fws.folded);
    debug(fws.nonfolded);
}


// Non-RFC, no comments so far
template<typename Iterator>
struct CFWS : qi::rule<Iterator, std::string()> {
    template<typename NormalizeStrategy = normalize::None>
    CFWS(NormalizeStrategy normalize_tag = NormalizeStrategy{}) : fws(normalize_tag) {
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
