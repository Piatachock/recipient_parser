#ifndef RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_
#define RECIPIENT_PARSER_INCLUDE_ATOMS_HPP_

#include "../detail/spirit.hpp"

#include "whitespaces.hpp"

namespace rcpt_parser {

template<typename Iterator>
struct AText : qi::rule<Iterator, char()> {
    AText() {
        this->name("atext");
        static_cast<typename AText::this_type&>(*this) %=
                standard::alnum
              | standard::char_("!#$%&'*+|=?^_`{|}~")
            // minus symbol is given separately because char_() treats symbols in string
            // as if it is inside symbol class in regexp, like [a-z0-9]. So minus has
            // special meaning here.
              | standard::char_('-');
    }
};

template<typename Iterator>
struct Atom : qi::rule<Iterator, std::string()> {
    Atom() {
        this->name("atom");
        static_cast<typename Atom::this_type&>(*this) %=
                -qi::omit[cfws] >> +atext >> -qi::omit[end_cfws];
    }
    CFWS<Iterator> cfws, end_cfws;
    AText<Iterator> atext;
};

template<typename Iterator>
void debug(Atom<Iterator>& atom) {
    debug(static_cast<typename Atom<Iterator>::this_type&>(atom));
    debug(atom.cfws);
    debug(atom.end_cfws);
    debug(atom.atext);
}

template<typename Iterator>
struct DotAtom : qi::rule<Iterator, std::string()> {
    DotAtom() {
        dot_atom_text.name("dot-atom-text");
        dot_atom_text %= +atext >> *qi::hold[qi::char_('.') >> +atext];

        this->name("dot-atom (trimmed word with dots, except first and last symbol)");
        static_cast<typename DotAtom::this_type&>(*this) %=
                -qi::omit[cfws] >> dot_atom_text >> -qi::omit[end_cfws];
    }
    CFWS<Iterator> cfws, end_cfws;
    AText<Iterator> atext;
    qi::rule<Iterator, std::string()> dot_atom_text;
};

template<typename Iterator>
void debug(DotAtom<Iterator>& dot_atom) {
    debug(static_cast<typename DotAtom<Iterator>::this_type&>(dot_atom));
    debug(dot_atom.cfws);
    debug(dot_atom.end_cfws);
    debug(dot_atom.atext);
    debug(dot_atom.dot_atom_text);
}

} // namespace rcpt_parser

#endif
