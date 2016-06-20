#ifndef RECIPIENT_PARSER_INCLUDE_SPIRIT_HPP_
#define RECIPIENT_PARSER_INCLUDE_SPIRIT_HPP_

#ifndef BOOST_RESULT_OF_USE_DECLTYPE
#define BOOST_RESULT_OF_USE_DECLTYPE
#endif

#ifndef BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_USE_PHOENIX_V3
#endif

#include <boost/spirit/include/qi.hpp>
#include <boost/phoenix/function/function.hpp>

namespace rcpt_parser {

namespace spirit = boost::spirit;
namespace qi = spirit::qi;
namespace ascii = qi::ascii;
namespace phx = boost::phoenix;

} // namespace rcpt_parser

#endif

