//============================================================================
// Name        : boost-x3-test.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
struct EmailParser : qi::grammar<Iterator, LoginDomain(), Skipper> {
    EmailParser() : EmailParser::base_type(start) {
        fws %= qi::eps;         // TODO
        cfws %= qi::eps;        // TODO

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
    qi::rule<Iterator, qi::unused_type, Skipper> fws, cfws;

    qi::rule<Iterator, char(), Skipper> atext;
    qi::rule<Iterator, std::string(), Skipper> atom, dot_atom_text, dot_atom,
            local_part, domain;

    qi::rule<Iterator, LoginDomain(), Skipper> start;
};


int main(int argc, char* argv[]) {
    auto input = std::string(argv[1]);

    using qi::phrase_parse;
    using ascii::space;

    auto begin = input.begin();
    const auto end = input.end();

    EmailParser<std::string::iterator> parser;
    LoginDomain result;

    bool r = phrase_parse(
        begin,                          // Start Iterator
        end,                            // End Iterator
        parser,                         // The Parser
        space,                          // The Skip-Parser
        result
    );

    if (r && begin == end)
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded. Login: " << result.login
                << ", Domain: " << result.domain << std::endl;
        std::cout << "-------------------------\n";
    }
    else
    {
        std::string rest(begin, end);
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "stopped at: \"" << rest << "\"\n";
        std::cout << "-------------------------\n";
    }

    std::cout << (r ? "OK" : "NO") << std::endl;
}
