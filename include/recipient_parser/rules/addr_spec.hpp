#ifndef RECIPIENT_PARSER_INCLUDE_ADDR_SPEC_HPP_
#define RECIPIENT_PARSER_INCLUDE_ADDR_SPEC_HPP_

#include "../types/addr_spec.hpp"

#include "../detail/spirit.hpp"

#include "atoms.hpp"
#include "whitespaces.hpp"
#include "quoted_string.hpp"


namespace rcpt_parser {

template<typename Iterator>
struct LocalPart : qi::rule<Iterator, std::string()> {
    struct QSTraits :
            traits::quoted_string::PreserveQuotes,
            traits::quoted_string::RemoveOuterCWFS
    {};

    LocalPart() : quoted_string(QSTraits{}) {
        this->name("local-part");
        static_cast<typename LocalPart::this_type&>(*this) %=
                dot_atom | quoted_string;
    }
    DotAtom<Iterator> dot_atom;
    QuotedString<Iterator> quoted_string;
};

template<typename Iterator>
void debug(LocalPart<Iterator>& lp) {
    debug(static_cast<typename LocalPart<Iterator>::this_type&>(lp));
    debug(lp.dot_atom);
    debug(lp.quoted_string);
}

template<typename Iterator>
struct Domain : qi::rule<Iterator, std::string()> {
    Domain() {
        this->name("domain");
        static_cast<typename Domain::this_type&>(*this) %=
                dot_atom | domain_literal;

        domain_literal.name("domain-literal");
        domain_literal %=
                -qi::omit[cfws]
              >> qi::hold[qi::char_('[')
              >> *qi::hold[-fws >> dtext] >> -end_fws
              >> qi::char_(']')]
              >> -qi::omit[cfws];

        dtext.name("dtext");
        dtext %= qi::char_("\x21-\x7e") - '[' - ']' - '\\';
    }
    DotAtom<Iterator> dot_atom;

    CFWS<Iterator> cfws;
    FWS<Iterator> fws, end_fws;

    qi::rule<Iterator, char()> dtext;
    qi::rule<Iterator, std::string()> domain_literal;
};

template<typename Iterator>
void debug(Domain<Iterator>& dom) {
    debug(static_cast<typename Domain<Iterator>::this_type&>(dom));
    debug(dom.dot_atom);
    debug(dom.cfws);
    debug(dom.fws);
    debug(dom.end_fws);
    debug(dom.dtext);
    debug(dom.domain_literal);
}

template<typename Iterator>
struct AddrSpec : qi::rule<Iterator, types::AddrSpec()> {
    AddrSpec() {
        this->name("addr-spec");
        static_cast<typename AddrSpec::this_type&>(*this) %= local_part >> "@" >> domain;
    }
    Domain<Iterator> domain;
    LocalPart<Iterator> local_part;
};

template<typename Iterator>
void debug(AddrSpec<Iterator>& addr_spec) {
    debug(static_cast<typename AddrSpec<Iterator>::this_type&>(addr_spec));
    debug(addr_spec.local_part);
    debug(addr_spec.domain);
}

} // namespace rcpt_parser

#endif
