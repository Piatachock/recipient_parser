#ifndef RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_
#define RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_

#include <string>

#include <recipient_parser/types/login_domain.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_email(const std::string& input, LoginDomain& result);

}

#endif /* RECIPIENT_PARSER_SRC_PARSE_EMAIL_HPP_ */
