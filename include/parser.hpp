#include <iostream>
#include <tuple>

#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::qi::ascii;

BOOST_FUSION_DEFINE_STRUCT(
    (),
    LoginDomain,
    (std::string, login)
    (std::string, domain)
);


template<typename Iterator, typename Skipper = ascii::space_type>
struct FWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    FWS() {
        this->name("folding whitespace");
        static_cast<typename FWS::base_type&>(*this) = qi::eps;
    }
};


template<typename Iterator, typename Skipper = ascii::space_type>
struct CFWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    CFWS() {
        this->name("commented folding whitespace");
        static_cast<typename CFWS::base_type&>(*this) = qi::eps;
    }
};


template<typename Iterator, typename Skipper = ascii::space_type>
struct EmailParser : qi::grammar<Iterator, LoginDomain(), Skipper> {
    EmailParser() : EmailParser::base_type(start) {

        atext %= ascii::alnum |
                "!" | "#" |     //  SP, and specials.
                "$" | "%" |     //  Used for atoms
                "&" | "'" |
                "*" | "+" |
                "-" | "|" |
                "=" | "?" |
                "^" | "_" |
                "`" | "{" |
                "|" | "}" |
                "~";
        atom %= -cfws >> +atext >> -cfws;

        dot_atom_text %= +atext >> *(qi::char_('.') >> +atext);
        dot_atom %= -cfws >> dot_atom_text >> -cfws;

        local_part %= dot_atom;
        domain %= dot_atom;

        start %= local_part
                >> "@"
                >> domain;
    }
    CFWS<Iterator, Skipper> cfws;
    qi::rule<Iterator, char(), Skipper> atext;
    qi::rule<Iterator, std::string(), Skipper> atom, dot_atom_text, dot_atom,
            local_part, domain;

    qi::rule<Iterator, LoginDomain(), Skipper> start;
};


