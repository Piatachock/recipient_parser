#ifndef RECIPIENT_PARSER_FROM_STRING_ADDRESS_HPP_
#define RECIPIENT_PARSER_FROM_STRING_ADDRESS_HPP_

#include <string>

#include <recipient_parser/types/login_domain.hpp>

namespace rcpt_parser {

std::string::const_iterator parse_name_addr(const std::string& input, types::NameAddr& result);
std::string::const_iterator parse_mailbox(const std::string& input, types::NameAddr& result);
std::string::const_iterator parse_group(const std::string& input, types::MailboxGroup& result);

std::string::const_iterator parse_address(const std::string& input, types::Address& result);
}

#endif /* RECIPIENT_PARSER_FROM_STRING_EMAIL_HPP_ */
