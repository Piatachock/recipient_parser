#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_

#include "spirit.hpp"
#include "quoted_pair.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct QuotedString : qi::rule<Iterator, std::string()> {
    QuotedString() {
        qtext.name("qtext");
        qtext %= qi::char_("\x21-\x7e") - '\'' - '"';

        qcontent.name("qcontent");
        qcontent %= qtext | qp;

        this->name("quoted-string");
        static_cast<typename QuotedString::this_type&>(*this) %=
                -qi::omit[cfws]
              >> qi::lit('"')
              >> *qi::hold[-fws >> qcontent]
              >> -end_fws
              >> qi::lit('"')
              >> -qi::omit[cfws];
    }
    CFWS<Iterator> cfws;
    FWS<Iterator> fws, end_fws;
    QuotedPair<Iterator> qp;
    qi::rule<Iterator, char()> qtext, qcontent;
};

} // namespace rcpt_parser

#endif // RECIPIENT_PARSER_INCLUDE_QUOTED_STRING_HPP_
