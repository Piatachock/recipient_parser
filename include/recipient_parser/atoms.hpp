#ifndef RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_
#define RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_

#include "spirit.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator, typename Skipper = ascii::space_type>
struct AText : qi::rule<Iterator, char(), Skipper> {
    AText() {
        this->name("atext");
        static_cast<typename AText::this_type&>(*this) %=
                ascii::alnum
              | ascii::char_("!#$%&'*+|=?^_`{|}~")
              | ascii::char_('-');
    }
};

template<typename Iterator, typename Skipper = ascii::space_type>
struct DotAtom : qi::rule<Iterator, std::string(), Skipper> {
    DotAtom() {
        this->name("Word containing dots (neither first nor last symbol)");

        dot_atom_text %= +atext > *(qi::char_('.') > +atext);
        static_cast<typename DotAtom::this_type&>(*this) %=
                qi::eps > -cfws > dot_atom_text > -cfws;
    }
    CFWS<Iterator, Skipper> cfws;
    AText<Iterator, Skipper> atext;
    qi::rule<Iterator, std::string(), Skipper> dot_atom_text;
};

} // namespace rcpt_parser

#endif
