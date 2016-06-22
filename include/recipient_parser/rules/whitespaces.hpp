#ifndef RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_
#define RECIPIENT_PARSER_INCLUDE_WHITESPACES_HPP_

#include "../detail/spirit.hpp"

namespace rcpt_parser {

namespace traits {
namespace whitespaces {

struct PreserveCRLF {};  //leave data as-is
struct RemoveCRLF {};   //throw away crlf (RFC)

using Default = RemoveCRLF;

}}

template<typename Iterator>
struct FWS : qi::rule<Iterator, std::string()> {
    template<typename Tag = traits::whitespaces::Default>
    FWS(Tag tag = Tag{}) {
        // Non-RFC, because RFC stricts newline to be CRLF only, and here we support CR or LF.
        crlf.name("crlf");
        crlf %= qi::hold[(qi::char_('\r') >> -qi::char_('\n')) | qi::char_('\n')];

        folded.name("folded fws");
        init_folded(tag);

        nonfolded.name("nonfolded fws");
        nonfolded %= +qi::blank;

        this->name("fws (folding whitespace)");
        static_cast<typename FWS::this_type&>(*this) %= folded | nonfolded;
    }

    void init_folded(traits::whitespaces::PreserveCRLF) {
        folded %= qi::hold[*qi::blank >> crlf >> +qi::blank];
    }

    void init_folded(traits::whitespaces::RemoveCRLF) {
        folded %= qi::hold[*qi::blank >> qi::omit[crlf] >> +qi::blank];
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
    template<typename Tag = traits::whitespaces::Default>
    CFWS(Tag tag = Tag{}) : fws(tag) {
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
