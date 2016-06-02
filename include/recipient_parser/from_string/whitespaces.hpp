#ifndef RECIPIENT_PARSER_FROM_STRING_WHITESPACES_HPP_
#define RECIPIENT_PARSER_FROM_STRING_WHITESPACES_HPP_

#include <string>

namespace rcpt_parser {

std::string::const_iterator parse_fws(const std::string& input);
std::string::const_iterator parse_cfws(const std::string& input);

}

#endif /* RECIPIENT_PARSER_FROM_STRING_WHITESPACES_HPP_ */
