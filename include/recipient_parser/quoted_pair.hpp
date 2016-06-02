#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_

#include "spirit.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct QuotedPair : qi::rule<Iterator, char()> {
    QuotedPair() {
        symbol.name("quoted-pair symbol");
        symbol %= qi::char_("\x21-\x7e") | qi::blank;

        this->name("quoted-pair");
        static_cast<typename QuotedPair::this_type&>(*this) %=
                qi::lit('\\') >> symbol;
    }
    qi::rule<Iterator, char()> symbol;
};

template<typename Iterator>
void debug(QuotedPair<Iterator>& qp) {
    debug(static_cast<typename QuotedPair<Iterator>::this_type&>(qp));
    debug(qp.symbol);
}

} // namespace rcpt_parser

#endif
