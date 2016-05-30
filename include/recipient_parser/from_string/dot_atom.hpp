#ifndef RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_
#define RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_

#include <string>

namespace rcpt_parser {

std::string::const_iterator parse_dot_atom(const std::string& input, std::string& result);

}

#endif /* RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_ */
