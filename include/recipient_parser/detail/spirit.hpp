#ifndef RECIPIENT_PARSER_INCLUDE_SPIRIT_HPP_
#define RECIPIENT_PARSER_INCLUDE_SPIRIT_HPP_

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/function/function.hpp>

namespace rcpt_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace ascii = qi::ascii;
namespace phx = boost::phoenix;

} // namespace rcpt_parser

#endif

