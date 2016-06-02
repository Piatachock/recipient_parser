#ifndef RECIPIENT_PARSER_INCLUDE_EMAIL_HPP_
#define RECIPIENT_PARSER_INCLUDE_EMAIL_HPP_

#include "spirit.hpp"
#include "error_handler.hpp"
#include "atoms.hpp"
#include "whitespaces.hpp"
#include "quoted_string.hpp"
#include "types/login_domain.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct LocalPart : qi::rule<Iterator, std::string()> {
    LocalPart() {
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
              >> qi::lit('[')
              >> *qi::hold[-fws >> dtext]
              >> -end_fws
              >> qi::lit(']')
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
struct EmailParser : qi::grammar<Iterator, LoginDomain()> {
    EmailParser() : EmailParser::base_type(addr_spec) {
        addr_spec.name("addr-spec");
        addr_spec %= local_part > "@" > domain;
        qi::on_error<qi::fail>(addr_spec, error(qi::_1, qi::_2, qi::_3, qi::_4));
    }
    Domain<Iterator> domain;
    LocalPart<Iterator> local_part;
    qi::rule<Iterator, LoginDomain()> addr_spec;
    phx::function<ErrorHandler<Iterator>> const error;
};

template<typename Iterator>
void debug(EmailParser<Iterator>& parser) {
    debug(parser.domain);
    debug(parser.local_part);
    debug(parser.addr_spec);
}

} // namespace rcpt_parser

#endif
