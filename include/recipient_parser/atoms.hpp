#ifndef RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_
#define RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_

#include "spirit.hpp"
#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct AText : qi::rule<Iterator, char()> {
    AText() {
        this->name("atext");
        static_cast<typename AText::this_type&>(*this) %=
                ascii::alnum
              | ascii::char_("!#$%&'*+|=?^_`{|}~")
              | ascii::char_('-');
    }
};

template<typename Iterator>
struct DotAtom : qi::rule<Iterator, std::string()> {
    DotAtom() {
        dot_atom_text.name("dot-atom-text");
        dot_atom_text %= +atext >> *qi::hold[qi::char_('.') >> +atext];

        this->name("dot-atom (trimmed word with dots, except first and last symbol)");
        static_cast<typename DotAtom::this_type&>(*this) %=
                -qi::omit[cfws] >> dot_atom_text >> -qi::omit[cfws];
    }
    CFWS<Iterator> cfws;
    AText<Iterator> atext;
    qi::rule<Iterator, std::string()> dot_atom_text;
};

template<typename Iterator>
void debug(DotAtom<Iterator>& dot_atom) {
    debug(static_cast<typename DotAtom<Iterator>::this_type&>(dot_atom));
    debug(dot_atom.cfws);
    debug(dot_atom.atext);
    debug(dot_atom.dot_atom_text);
}

} // namespace rcpt_parser

#endif
