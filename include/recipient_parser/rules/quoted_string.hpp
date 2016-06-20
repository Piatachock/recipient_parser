#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_

#include "../detail/spirit.hpp"

#include "quoted_pair.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct QuotedString : qi::rule<Iterator, std::string()> {
    QuotedString() {
        qtext.name("qtext");
        //Printable characters except backslash and quote
        qtext %= qi::char_("\x21-\x7e") - '\\' - '"';

        qcontent.name("qcontent");
        qcontent %= qtext | qp;

        this->name("quoted-string");
        static_cast<typename QuotedString::this_type&>(*this) %=
                -qi::omit[cfws]
              >> qi::hold[qi::char_('"')
              >> *qi::hold[-fws >> qcontent]
              >> -end_fws
              >> qi::char_('"')]
              >> -qi::omit[end_cfws];
    }
    CFWS<Iterator> cfws, end_cfws;
    FWS<Iterator> fws, end_fws;
    QuotedPair<Iterator> qp;
    qi::rule<Iterator, std::string()> qtext, qcontent;
};

template<typename Iterator>
void debug(QuotedString<Iterator>& qs) {
    debug(static_cast<typename QuotedString<Iterator>::this_type&>(qs));
    debug(qs.cfws);
    debug(qs.end_cfws);
    debug(qs.fws);
    debug(qs.end_fws);
    debug(qs.qp);
    debug(qs.qtext);
    debug(qs.qcontent);
}

} // namespace rcpt_parser

#endif // RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
