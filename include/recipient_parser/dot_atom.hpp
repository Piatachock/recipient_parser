#ifndef RECIPIENT_PARSER_INCLUDE_DOT_ATOM_HPP_
#define RECIPIENT_PARSER_INCLUDE_DOT_ATOM_HPP_

#include "spirit.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator, typename Skipper = ascii::space_type>
struct DotAtom : qi::rule<Iterator, std::string(), Skipper> {
    using Base = qi::rule<Iterator, std::string(), Skipper>;
    DotAtom() {
        this->name("Word containing dots (neither first nor last symbol)");

        atext %= qi::no_skip[ascii::alnum | ascii::char_("!#$%&'*+|=?^_`{|}~") | ascii::char_('-')];
        dot_atom_text %= +atext > *(qi::char_('.') > +atext);
        static_cast<Base&>(*this) %= qi::eps > -cfws > dot_atom_text > -cfws;
    }
    CFWS<Iterator, Skipper> cfws;
    qi::rule<Iterator, char(), Skipper> atext;
    qi::rule<Iterator, std::string(), Skipper> dot_atom_text;
};

} // namespace rcpt_parser

#endif
