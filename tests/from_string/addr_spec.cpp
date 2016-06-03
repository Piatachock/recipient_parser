#include <recipient_parser/rules/addr_spec.hpp>

#include "addr_spec.hpp"
#include "detail/parse_template.hpp"

namespace rcpt_parser {

std::string::const_iterator parse_domain(const std::string& input, std::string& result) {
    return detail::parse_template<Domain>(input, result);
}

std::string::const_iterator parse_addr_spec(const std::string& input, LoginDomain& result) {
    return detail::parse_template<AddrSpec>(input, result);
}

} // namespace rcpt_parser
