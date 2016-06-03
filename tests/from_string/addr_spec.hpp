#ifndef RECIPIENT_PARSER_FROM_STRING_EMAIL_HPP_
#define RECIPIENT_PARSER_FROM_STRING_EMAIL_HPP_

#include <string>

#include <recipient_parser/types/login_domain.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_domain(const std::string& input, std::string& result);
std::string::const_iterator parse_addr_spec(const std::string& input, LoginDomain& result);

}

#endif /* RECIPIENT_PARSER_FROM_STRING_EMAIL_HPP_ */
