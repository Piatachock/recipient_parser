#include <recipient_parser/rules/address.hpp>

#include "address.hpp"
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_name_addr(const std::string& input, types::NameAddr& result) {
    return detail::parse_template<NameAddr>(input, result);
}

std::string::const_iterator parse_mailbox(const std::string& input, types::NameAddr& result) {
    return detail::parse_template<Mailbox>(input, result);
}

std::string::const_iterator parse_group(const std::string& input, types::MailboxGroup& result) {
    return detail::parse_template<Group>(input, result);
}

} // namespace rcpt_parser
