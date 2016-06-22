#ifndef RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_
#define RECIPIENT_PARSER_INCLUDE_QUOTED_PAIR_HPP_

#include "../detail/spirit.hpp"

namespace rcpt_parser {

namespace traits {
namespace quoted_pair {

struct PreserveBackslash {};
struct RemoveBackslash {};

using Default = RemoveBackslash;

}}

template<typename Iterator>
struct QuotedPair : qi::rule<Iterator, std::string()> {
    template<typename Tag = traits::quoted_pair::Default>
    QuotedPair(Tag tag = Tag{}) {
        symbol.name("quoted-pair symbol");
        //Printable characters plus whitespaces and horizontal tabs
        symbol %= qi::char_("\x21-\x7e") | qi::blank;

        this->name("quoted-pair");
        parse_pair(tag);
    }

    void parse_pair(traits::quoted_pair::PreserveBackslash) {
        static_cast<typename QuotedPair::this_type&>(*this) %=
                qi::char_('\\') >> symbol;
    }

    void parse_pair(traits::quoted_pair::RemoveBackslash) {
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
