#ifndef RECIPIENT_PARSER_INCLUDE_PARSER_HPP_
#define RECIPIENT_PARSER_INCLUDE_PARSER_HPP_

#include <iostream>
#include <tuple>

#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/spirit/include/phoenix_object.hpp>

#include <recipient_parser/types/login_domain.hpp>

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace ascii = qi::ascii;


template<typename Iterator, typename Skipper = ascii::space_type>
struct FWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    using Base = qi::rule<Iterator, qi::unused_type, Skipper>;
    FWS() {
        this->name("folding whitespace");
        static_cast<Base&>(*this) = qi::eps;
    }
};


template<typename Iterator, typename Skipper = ascii::space_type>
struct CFWS : qi::rule<Iterator, qi::unused_type, Skipper> {
    using Base = qi::rule<Iterator, qi::unused_type, Skipper>;
    CFWS() {
        this->name("commented folding whitespace");
        static_cast<Base&>(*this) = qi::eps;
    }
};


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


template<typename Iterator>
struct ErrorHandler {
    typedef void result_type;

    template<class I>
        void operator()(Iterator /*begin*/, Iterator end, Iterator where,
                I const& info) const {
            std::stringstream out;
            out << "expecting " << info << " here: "
                    << boost::iterator_range<Iterator>(where, end) << std::endl;

            throw std::runtime_error(out.str());
        }
};

template<typename Iterator, typename Skipper = ascii::space_type>
struct EmailParser : qi::grammar<Iterator, LoginDomain(), Skipper> {
    EmailParser() : EmailParser::base_type(start) {

        start %= local_part > "@" > domain;

        qi::on_error<qi::fail>(start, error(qi::_1, qi::_2, qi::_3, qi::_4));
    }
    DotAtom<Iterator, Skipper> local_part, domain;
    qi::rule<Iterator, LoginDomain(), Skipper> start;
    boost::phoenix::function<ErrorHandler<Iterator>> const error;
};


#endif
