#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_

#include "spirit.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct QuotedPair : qi::rule<Iterator, char()> {
    QuotedPair() {
        this->name("quoted-pair");
        static_cast<typename QuotedPair::this_type&>(*this) %=
                qi::lit('\\') >> (qi::char_("\x21-\x7e") | qi::blank);
    }
};

} // namespace rcpt_parser

#endif
