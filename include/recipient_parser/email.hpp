#ifndef RECIPIENT_PARSER_INCLUDE_EMAIL_HPP_
#define RECIPIENT_PARSER_INCLUDE_EMAIL_HPP_

#include "spirit.hpp"
#include "atoms.hpp"
#include "error_handler.hpp"
#include "types/login_domain.hpp"

namespace rcpt_parser {

template<typename Iterator, typename Skipper = ascii::space_type>
struct EmailParser : qi::grammar<Iterator, LoginDomain(), Skipper> {
    EmailParser() : EmailParser::base_type(start) {
        start.name("Login+domain");
        start %= local_part > "@" > domain;
        qi::on_error<qi::fail>(start, error(qi::_1, qi::_2, qi::_3, qi::_4));
    }
    DotAtom<Iterator, Skipper> local_part, domain;
    qi::rule<Iterator, LoginDomain(), Skipper> start;
    phx::function<ErrorHandler<Iterator>> const error;
};

} // namespace rcpt_parser

#endif
